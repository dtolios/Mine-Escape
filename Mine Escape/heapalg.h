//
//  heapalg.h
//  Mine Escape
//
//  Created by Dimitri Tolios on 10/26/16.
//  Copyright © 2016 Dimitri Tolios. All rights reserved.
//

#ifndef heapalg_h
#define heapalg_h
/*
 This file includes the different heap-based priority-queue container
 algorithms in order to escape the mine.
 */
#include <vector>
using namespace std;

struct Tile
{
    int row;
    int col;
    int tileValue;
    bool isStart;
    bool visited;
    bool operator<(Tile const& a) const
    {
        if(tileValue < a.tileValue)
            return true;
        else if(tileValue == a.tileValue)
        {
            if(col < a.col)
                return true;
            else if(col == a.col)
            {
                if(row < a.row)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    bool operator>(Tile const& a) const
    {
        if(tileValue > a.tileValue)
            return true;
        else if(tileValue == a.tileValue)
        {
            if(col > a.col)
                return true;
            else if(col == a.col)
            {
                if(row > a.row)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    bool operator() (Tile const& a, Tile const& b) const
    {
        if(a.tileValue < b.tileValue)
            return true;
        else if(a.tileValue == b.tileValue)
        {
            if(a.col < b.col)
                return true;
            else if(a.col == b.col)
            {
                if(a.row < b.row)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
};

vector<Tile> escape(vector<vector<Tile>> &floor, const unsigned GRID_SIZE, unsigned &dynamite,
                    const Tile &startLocation, char containerType, bool &escapeFound);
//REQUIRES: floor must be populated, grid__size must be > 0,
//          start location must be valid.
//MODIFIES: The FLOOR of the mine and the amount of dynamite
//EFFECTS: Finds the escape route by utilizing a heap
//         It modifies the 2-D vector of the map by blowing up
//         the rubble using the dynamite of the traveler.
//      

#endif /* heapalg_h */
