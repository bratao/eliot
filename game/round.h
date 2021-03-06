/*****************************************************************************
 * Eliot
 * Copyright (C) 1999-2012 Antoine Fraboulet & Olivier Teulière
 * Authors: Antoine Fraboulet <antoine.fraboulet @@ free.fr>
 *          Olivier Teulière <ipkiss @@ gmail.com>
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *****************************************************************************/

#ifndef ROUND_H_
#define ROUND_H_

#include <vector>
#include "tile.h"
#include "coord.h"
#include "logging.h"

using namespace std;


/**
 * A Round is the representation of a played word (or going to be played).
 * It contains the word itself, of course, but also information of position
 * on the board, origin of letters (board for a letter already placed, rack
 * for a letter just being played), points, etc...
 */
class Round
{
    DEFINE_LOGGER();
public:

    Round();

    /*************************
     *
     *************************/
    void addRightFromBoard(const Tile &iTile);
    void addRightFromRack(const Tile &iTile, bool iJoker);
    void removeRight();

    /*************************
     * General setters
     *************************/
    void setPoints(int iPoints)    { m_points = iPoints; }
    void setBonus(bool iBonus)     { m_bonus = iBonus; }
    void setTile(unsigned int iIndex, const Tile &iTile);
    void setWord(const vector<Tile> &iTiles);
    void setFromRack(unsigned int iIndex);
    void setFromBoard(unsigned int iIndex);

    /*************************
     * General getters
     *************************/
    bool isJoker         (unsigned int iIndex) const;
    bool isPlayedFromRack(unsigned int iIndex) const;
    const Tile& getTile  (unsigned int iIndex) const;

    wstring getWord() const;
    unsigned int getWordLen() const { return m_word.size(); }
    int getPoints() const           { return m_points; }
    bool getBonus() const           { return m_bonus; }
    const vector<Tile> &getTiles() const { return m_word; }

    unsigned countJokersFromRack() const;

    /*************************
     * Coordinates
     *************************/
    const Coord& getCoord() const { return m_coord; }
    Coord& accessCoord()          { return m_coord; }


    wstring toString() const;

    /// Equality operator
    bool operator==(const Round &iOther) const;

private:
    vector<Tile> m_word;
    vector<bool> m_rackOrigin;
    Coord m_coord;
    int m_points;
    bool m_bonus;
};

#endif

