/*****************************************************************************
 * Copyright (C) 1999-2005 Eliot
 * Authors: Antoine Fraboulet <antoine.fraboulet@free.fr>
 *          Olivier Teuliere  <ipkiss@via.ecp.fr>
 *
 * $Id: results.h,v 1.2 2005/02/05 11:14:56 ipkiss Exp $
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

#ifndef _RESULTS_H_
#define _RESULTS_H_

#include <vector>

using namespace std;

/*************************
 * Results is a container. The structure
 * stores the rounds that have been found
 * during a search on the board
 *************************/

class Results
{
public:
    Results() {}
    virtual ~Results() {}

    /*************************
     * 
     * 
     *************************/
    int in() const  { return m_rounds.size(); }
    const Round & get(int) const;

    void add(const Round &iRound)   { m_rounds.push_back(iRound); }
    void sort();

    void deleteLast();
    void clear()    { m_rounds.clear(); }

private:
    vector<Round> m_rounds;
};

#endif