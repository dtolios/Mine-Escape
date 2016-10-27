//
//  heapalg.cpp
//  Mine Escape
//
//  Created by Dimitri Tolios on 10/26/16.
//  Copyright © 2016 Dimitri Tolios. All rights reserved.
//

#include "heapalg.h"
#include "binary_heap.h"

using namespace std;

vector<Tile> escape(vector<vector<Tile>> &floor, const unsigned GRID_SIZE, unsigned &dynamite,
                    const Tile &startLocation, char containerType, bool &escapeFound)
{
    Tile currTile;
    escapeFound = false;
    vector<Tile> order;
    //initialize the heap
    eecs281heap<Tile, less<Tile>> *theHeap = nullptr;
    binary_heap<Tile, less<Tile>> bHeap;
    // poorman_heap<Tile, less<Tile>> mHeap;
    // sorted_heap<Tile, less<Tile>> sHeap;
    // pairing_heap<Tile, less<Tile>> pHeap;
    switch(containerType)
    {
        case 'b':
            theHeap = &bHeap;
            break;
        case 'm':
            // theHeap = &mHeap;
            break;
        case 's':
            // theHeap = &sHeap;
            break;
        case 'p':
            // theHeap = &pHeap;
            break;
        default:
            theHeap = &bHeap;
    }
    
    //start algorithm by pushing the start onto the heap
    theHeap->push(startLocation);
    
    //continue the algorithm until the heap is empty
    //if this condition is reached, no escape was found
    while(!theHeap->empty())
    {
        //change current Tile to the top of the heap
        currTile = theHeap->top();
        /*
         check if dynamite is sufficient
         this loop only runs if the tileValue is greater than
         the amount of dynamite you have. The loop will stop if
         the heap is empty.
         */
        while(currTile.tileValue > dynamite)
        {
            theHeap->pop();
            if(theHeap->empty())
                break;
            else
                currTile = theHeap->top();
        }
        /*
         if the heap was emptied because there are no tiles with
         a value less than or equal to your dynamite, break loop
         early.
         */
        if(theHeap->empty())
            break;
        
        //pop the top of the heap,
        //you have blown up this tile and used your dynamite
        if(currTile.tileValue == 0)
            theHeap->pop();
        else
        {
            theHeap->pop();
            order.push_back(currTile);
            dynamite = dynamite-floor[currTile.row][currTile.col].tileValue;
        }
        
        //check if edge of map is north
        if(currTile.row+1 < GRID_SIZE)
        {
            //check if tile has been added to heap
            if(floor[currTile.row+1][currTile.col].visited == false)
            {
                floor[currTile.row+1][currTile.col].visited = true;
                theHeap->push(floor[currTile.row+1][currTile.col]);
            }
        }
        else
        {
            escapeFound = true;
            break;
        }
        //check if edge of map is south
        if(currTile.row-1 >= 0)
        {
            //check if tile has been added to heap
            if(floor[currTile.row-1][currTile.col].visited == false)
            {
                floor[currTile.row-1][currTile.col].visited = true;
                theHeap->push(floor[currTile.row-1][currTile.col]);
            }
        }
        else
        {
            escapeFound = true;
            break;
        }
        //check if edge of map is east
        if(currTile.col+1 < GRID_SIZE)
        {
            //check if tile has been added to heap
            if(floor[currTile.row][currTile.col+1].visited == false)
            {
                floor[currTile.row][currTile.col+1].visited = true;
                theHeap->push(floor[currTile.row][currTile.col+1]);
            }
        }
        else
        {
            escapeFound = true;
            break;
        }
        //check if edge of map is west
        if(currTile.col-1 >= 0)
        {
            //check if tile has been added to heap
            if(floor[currTile.row][currTile.col-1].visited == false)
            {
                floor[currTile.row][currTile.col-1].visited = true;
                theHeap->push(floor[currTile.row][currTile.col-1]);
            }
        }
        else
        {
            escapeFound = true;
            break;
        }
    }
    return order;
}

