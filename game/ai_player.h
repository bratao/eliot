/*****************************************************************************
 * Copyright (C) 2005 Eliot
 * Authors: Olivier Teuliere  <ipkiss@via.ecp.fr>
 *
 * $Id: ai_player.h,v 1.1 2005/02/17 20:01:59 ipkiss Exp $
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

#ifndef _AI_PLAYER_H_
#define _AI_PLAYER_H_

#include "player.h"

class Round;
class Board;
class Tile;
typedef struct _Dictionary * Dictionary;

/**************************
 * AI (Artificial Intelligence) handling
 * The int argument of Player_ai_search() is the 'turn' number
 * (starting from 0)
 * Note: we could implement various strategies:
 *   - best: play the word with the best score (current implementation)
 *   - second: play the word with the second best score (strictly lower than
 *        the best one)
 *   - random: randomly choose one of the possible words
 *   - handicap(p): in the array of the n possible words (sorted by
 *        decreasing scores), play the word number i, where i/n is nearest
 *        from a predefined percentage p.
 *        So 'handicap(0)' should be equivalent to 'best'.
 *        This strategy makes an interesting opponent, because you can adapt
 *        it to your level, with a careful choice of the p value.
 *
 * In fact, instead of working on the score of the words, these strategies
 * could work on any other value. In particular, some heuristics could
 * modulate the score with a value indicating the openings offered by the
 * word (if a word makes accessible a "word counts triple" square, it is
 * less interesting than another word with the same score or even with a
 * slightly lower score, but which does not offer such a square).
 *
 * More evolved heuristics could even take into account the remaining
 * letters in the bag to guess the 'statistical rack' of the opponent, and
 * play a word both maximizing the score and minimizing the opponent's
 * score...
 * Hmmm... i don't think this one will be implemented in a near future :)
 **************************/

class AIPlayer: public Player
{
public:
    virtual ~AIPlayer() {}

    // No human here. Trespassers will be shot!
    virtual bool isHuman() const { return false; }

    // This method does the actual computation, you need to call it before
    // using any of the other methods
    virtual void compute(const Dictionary &iDic, Board &iBoard, int turn) = 0;
    // Return true when the AI wants to change letters instead of playing a word
    virtual bool changesLetters() const = 0;
    // Return the round played by the AI (if changesLetters() returns false)
    virtual const Round & getChosenRound() const = 0;
    // Get the letters to change (if changesLetters() returns true)
    virtual vector<Tile> getChangedLetters() const = 0;

protected:
    // This class is a pure interface, forbid any instanciation
    AIPlayer() {}
};

#endif
