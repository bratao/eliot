/*****************************************************************************
 * Copyright (C) 2005 Eliot
 * Authors: Olivier Teuliere  <ipkiss@via.ecp.fr>
 *
 * $Id: duplicate.cpp,v 1.1 2005/02/05 11:14:56 ipkiss Exp $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *****************************************************************************/

#include "dic.h"
#include "tile.h"
#include "rack.h"
#include "round.h"
#include "pldrack.h"
#include "results.h"
#include "player.h"
#include "duplicate.h"
#include "debug.h"


Duplicate::Duplicate(const Dictionary &iDic): Game(iDic)
{
}


Duplicate::~Duplicate()
{
}


int Duplicate::setRackRandom(int p, bool iCheck, set_rack_mode mode)
{
    int res;
    do
    {
        res = helperSetRackRandom(p, iCheck, mode);
    } while (res == 2);
    return res;
}


int Duplicate::play(const string &iCoord, const string &iWord)
{
    /* Perform all the validity checks, and fill a round */
    Round round;
    int res = checkPlayedWord(iCoord, iWord, round);
    if (res != 0)
    {
        return res;
    }

    /* Everything is OK, we can play the word */
    playRound(round, m_currPlayer);

    /* Next turn */
    // XXX: Should it be done by the interface instead?
    endTurn();

    return 0;
}


int Duplicate::duplicateAI(int n)
{
    PDEBUG(n < 0 || n >= getNPlayers(), "GAME: wrong player number\n");
    Player *player = m_players[n];

    PDEBUG(player->isHuman(), "GAME: AI requested for a human player!\n");

    player->aiSearch(*m_dic, m_board, getNRounds());
    const Results &results = player->aiGetResults();
    if (results.in() == 0)
    {
        /* The AI player has nothing to play.
         * XXX: Is it even possible? */
        PDEBUG(1, "GAME: Yes, this is possible...");
        return 1;
    }
    else
    {
        playRound(results.get(0), n);
    }

    return 0;
}


int Duplicate::start()
{
    int res, i;

    if (getNPlayers() == 0)
        return 1;

    m_currPlayer = 0;

    /* XXX: code similar with endturn() */
    /* Complete the rack for the player that just played */
    res = setRackRandom(0, 1, RACK_NEW);
    /* End of the game? */
    if (res == 1)
    {
        end();
        return 1;
    }

    PlayedRack &pld = m_players[m_currPlayer]->getPlayedRack();
    /* All the players have the same rack */
    for (i = 0; i < getNPlayers(); i++)
    {
        if (i != m_currPlayer)
        {
            m_players[i]->getPlayedRack() = pld;
        }
        /* Nobody has played yet in this round */
        m_players[i]->setStatus(Player::TO_PLAY);
    }

    /* Next turn */
    // XXX: Should it be done by the interface instead?
    endTurn();

    return 0;
}


/*
 * This function does not terminate the turn itself, but performs some
 * checks to know whether or not it should be terminated (with a call to
 * endTurnForReal()).
 *
 * For the turn to be terminated, all the players must have played.
 * Since the AI players play after the human players, we check whether
 * one of the human players has not played yet:
 *   - if so, we have nothing to do (we are waiting for him)
 *   - if not (all human players have played), the AI players can play,
 *     and we finish the turn.
 */
int Duplicate::endTurn()
{
    int i;
    for (i = 0; i < getNPlayers(); i++)
    {
        if (m_players[i]->isHuman() &&
            m_players[i]->getStatus() == Player::TO_PLAY)
        {
            /* A human player has not played... */
            m_currPlayer = i;
            // XXX: check return code meaning
            return 1;
        }
    }

    /* If all the human players have played */
    if (i == getNPlayers())
    {
        /* Make AI players play their turn */
        for (i = 0; i < getNPlayers(); i++)
        {
            if (! m_players[i]->isHuman())
            {
                // XXX: handle the return value?
                if (duplicateAI(i))
                {
                    // XXX: check return code meaning
                    return 2;
                }
            }
        }

        /* Next turn */
        endTurnForReal();
    }

    // XXX: check return code meaning
    return 0;
}


void Duplicate::playRound(const Round &iRound, int n)
{
    PDEBUG(n < 0 || n >= getNPlayers(), "GAME: wrong player number\n");
    Player *player = m_players[n];

    /* Update the rack and the score of the current player */
    player->addPoints(iRound.getPoints());
    player->endTurn(iRound, getNRounds());

    player->setStatus(Player::PLAYED);
}


/*
 * This function really changes the turn, i.e. the best word is played and
 * a new rack is given to the players.
 * We suppose that all the players have finished to play for this turn (this
 * should have been checked by endturn())
 */
int Duplicate::endTurnForReal()
{
    int res, i, imax;

    /* Play the best word on the board */
    imax = 0;
    for (i = 1; i < getNPlayers(); i++)
    {
        if (m_players[i]->getLastRound().getPoints() >
            m_players[imax]->getLastRound().getPoints())
        {
            imax = i;
        }
    }
    m_currPlayer = imax;
    helperPlayRound(m_players[imax]->getLastRound());

    /* Complete the rack for the player that just played */
    res = setRackRandom(imax, 1, RACK_NEW);
    /* End of the game? */
    if (res == 1)
    {
        end();
        return 1;
    }

    PlayedRack &pld = m_players[imax]->getPlayedRack();
    /* All the players have the same rack */
    for (i = 0; i < getNPlayers(); i++)
    {
        if (i != imax)
        {
            m_players[i]->getPlayedRack() = pld;
        }
        /* Nobody has played yet in this round */
        m_players[i]->setStatus(Player::TO_PLAY);
    }

    /* XXX: Little hack to handle the games with only AI players.
     * This will have no effect when there is at least one human player */
    endTurn();

    return 0;
}


void Duplicate::end()
{
    // TODO
}


int Duplicate::setPlayer(int n)
{
    if (n < 0 || n >= getNPlayers())
        return 1;
    /* Forbid switching to an AI player */
    if (! m_players[n]->isHuman())
        return 2;

    m_currPlayer = n;
    return 0;
}
