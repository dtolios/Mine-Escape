/*
 /////////////////////////////////////////////////
         "***** M I N E  E S C A P E *****"
             Author: Dimitri Tolios
 
 This file provides the main application for the
 "Mine Mine Mine" project. This
 project reads in maps of the mine, and determines
 the best escape route using the least amount of
 dynamite.
 /////////////////////////////////////////////////
*/

#include <iostream>
#include <getopt.h>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include "eecs281heap.h"
#include "heapalg.h"
#include "binary_heap.h"

using namespace std;

int main(int argc, char * argv[])
{
    //check for program arguments
    if(argc == 1)
    {
        cerr << "No arguments found. Run the application with -h or --help for instructions.\n" << endl;
        return 1;
    }
    
    /*this program takes in at least one argument
     
     --container or -c: Changes the type of priority
     queue  that the implementation usues at runtine.
     Must be one of BINARY, POOR_MAN, SORTED, or PAIRING
     
     --verbose N or -v: An optional flag that indicates
     the program should print additional output statistics.
     This option takes a required argument, N, which is an
     integer of value greater than 0.
     
     --help or -h: print the help message and exit
     */
    
    int opt = 0;
    
    static struct option longOpts[] =
    {
        {"verbose", required_argument, 0, 'v'},
        {"container", required_argument, 0, 'c'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
    
    int index = 0;
    int cflag = 0, vflag = 0, hflag = 0;
    char *impType = nullptr;
    char *outStats = nullptr;
    
    while((opt = getopt_long(argc, argv, "c:v:h", longOpts, &index)) != -1)
    {
        switch(opt)
        {
            case 'c':
                cflag = 1;
                impType = optarg;
                break;
            case 'v':
                vflag = 1;
                outStats = optarg;
                break;
            case 'h':
                hflag = 1;
                break;
            case '?':
                break;
            default:
                abort();
        }
    }
    
    //check for help flag
    if(hflag == 1)
    {
        cout << "*****MINE ESCAPE*****\n" <<
        "A program developed by Dimitri Tolios\n" <<
        "This program will read in a valid minefile, \n" <<
        "and calculate the escape route if it exists.\n" <<
        "The calculation will print to a file of your choice.\n\n" <<
        "Command line arguments are required to run the program.\n" <<
        "These include:\n\n" <<
        "--container, -c: changes the type of priority queue\n" <<
        "options include BINARY, POOR_MAN, SORTED, and PAIRING.\n\n" <<
        "--verbose N, -v N: indicates that the program will print" <<
        " additional output statistics.\nThis option takes a required" <<
        " argument, N, which is an integer value greater than 0.\n\n" <<
        "Lastly, specify the input file and the output file.\nGood Luck!" << endl;
        
        return 0;
    }
    
    /* Check for specified input file */
    char *inFileName = nullptr;
    if (optind < argc)
    {
        while (optind < argc)
            inFileName = argv[optind++];
    }
    else
    {
        cerr << "Required input file missing. Closing..." << endl;
    }
    
    //::READ IN THE MAP:://
    string inputMode;
    unsigned int dynamite = 0;
    unsigned int mapSize = 0;
    ifstream mapFile(inFileName);
    
    if(mapFile.good())
    {
        mapFile >> inputMode;
        mapFile.ignore(10, ' '); //ignore until space
        mapFile >> dynamite;
        mapFile.ignore(11, ' '); //ignore until space
        mapFile >> mapSize;
    }
    else
    {
        cerr << "Something went wrong with input file...\n" << endl;
        
        return 1;
    }
    
    
    const unsigned int GRID_SIZE = mapSize;
    
    //create 2-D vector of Tiles
    vector<vector<Tile>> floor;
    
    // set up sizes
    // NOTE: I read that this actually is worse on performance for vectors
    // But I'm doing it so that I can access by (row, col) indexing
    floor.resize(GRID_SIZE);
    for(int i = 0; i < GRID_SIZE; i++)
        floor[i].resize(GRID_SIZE);
    
    
    Tile startTile;
    
    // ******************************
    // ******* MAP INPUT MODE *******
    // ******************************
    if(inputMode == "M")
    {
        int tileValue = 0;
        char whiteSpace;
        char peekVal;
        for(int row = GRID_SIZE - 1; row >= 0; row--)
        {
            for(int col = 0; col < GRID_SIZE; col++)
            {
                floor[row][col].row = row;
                floor[row][col].col = col;
                mapFile.get(whiteSpace);
                peekVal = mapFile.peek();
                
                // Check for start location indicator
                if(peekVal != 'S')
                {
                    mapFile >> tileValue;
                    floor[row][col].isStart = false;
                    floor[row][col].visited = false;
                    floor[row][col].tileValue = tileValue;
                }
                // throw away SL characters and mark location as startTile
                else
                {
                    mapFile >> whiteSpace;
                    mapFile >> whiteSpace;
                    floor[row][col].isStart = true;
                    floor[row][col].visited = true;
                    floor[row][col].tileValue = 0;
                    startTile = floor[row][col];
                }
            }
        }
    }
    // ******************************
    // ** PSEUDO RANDOM INPUT MODE **
    // ******************************
    else if(inputMode == "PR")
    {
        int randomSeed = 0;
        int maxRubble = 0;
        int startX = 0;
        int startY = 0;
        mapFile.ignore(13);
        mapFile>>randomSeed;
        mapFile.ignore(12);
        mapFile >> maxRubble;
        mapFile.ignore(9);
        mapFile >> startX;
        mapFile.ignore(9);
        mapFile >> startY;
        
        // seed the random number generator
        mt19937 gen(randomSeed);
        // initialize a uniform integer dist. with the desired range
        uniform_int_distribution<> dis(0,maxRubble);
        
        //for(int row = GRID_SIZE-1; row>=0; row--)
        for(int row = 0; row<GRID_SIZE; row++)
        {
            for(int col = 0; col<GRID_SIZE; col++)
            {
                floor[row][col].row = row;
                floor[row][col].col = col;
                floor[row][col].visited = false;
                floor[row][col].isStart = false;
                //generate the rubble value
                floor[row][col].tileValue = dis(gen);
            }
        }
        //initialize start tile
        floor[startY][startX].isStart = true;
        floor[startY][startX].visited = true;
        floor[startY][startX].tileValue = 0;
        startTile = floor[startY][startX];
    }
    else
    {
        cerr<<"Invalid input mode declared...\n";
        cerr.flush();
        exit(1);
    }
    
    //close the infile
    mapFile.close();
    
    //check for container flag
    char containerType;
    if(cflag == 1)
    {
        if(strcmp(impType,"BINARY")==0)
            containerType = 'b';
        else if(strcmp(impType,"POOR_MAN")==0)
            containerType = 'm';
        else if(strcmp(impType,"SORTED")==0)
            containerType = 's';
        else if(strcmp(impType,"PAIRING")==0)
            containerType = 'p';
        else
        {
            cerr << "Improper implementation type declared..." << endl;
            return 1;
        }
    }
    else
    {
        cerr << "Container flag missing..." << endl;
        return 1;
    }
    
    // COMPLETE THE ALGORITHM //
    vector<Tile> order;
    bool escapeFound = false;
    order = escape(floor, GRID_SIZE, dynamite, startTile, containerType, escapeFound);
    // BEGIN OUTPUT //
    Tile escapeTile;
    if(escapeFound)
    {
        if(!order.empty())
        {
            escapeTile = order.back();
            cout<<"You escaped through tile "<<escapeTile.col<<","<<
            escapeTile.row<<"! You have "<<dynamite<<
            " sticks of dynamite left.\n";
            cout.flush();
        }
        else
        {
            cout<<"You escaped through tile "<<startTile.col<<","<<
            startTile.row<<"! You have "<<dynamite<<
            " sticks of dynamite left.\n";
            cout.flush();
        }
    }
    else
    {
        if(!order.empty())
        {
            escapeTile = order.back();
            cout<<"You couldn't escape! You used your last dynamite sticks on tile "<<
            escapeTile.col<<","<<escapeTile.row<<".\n";
            cout.flush();
        }
        else
        {
            cout<<"You couldn't escape!\n";
            cout.flush();
            return 0;
        }
    }
    
    // VERBOSE OUTPUT //
    if(vflag == 1)
    {
        const char *verbNchars = outStats;
        unsigned int verbN = atoi(verbNchars);
        if(order.empty())
        {
            cout<<"First tiles blown up:\n";
            cout<<"Last tiles blown up:\n";
            cout<<"Hardest tiles to blow up:\n";
            cout<<"Easiest tiles to blow up:\n";
            cout.flush();
        }
        else
        {
            cout<<"First tiles blown up:\n";
            for(unsigned int i = 0; i < verbN && i < order.size(); i++)
            {
                cout<<i+1<<" ("<<order[i].col<<","<<order[i].row<<"): "<<
                order[i].tileValue<<"\n";
            }
            cout<<"Last tiles blown up:\n";
            if(verbN < order.size())
            {
                for(unsigned long i = order.size(); i > order.size()-verbN; i--)
                {
                    cout<<i<<" ("<<order[i-1].col<<","<<order[i-1].row<<"): "<<
                    order[i-1].tileValue<<"\n";
                }
            }
            if(verbN >= order.size())
            {
                for(unsigned long i = order.size(); i > 0; i--)
                {
                    cout<<i<<" ("<<order[i-1].col<<","<<order[i-1].row<<"): "<<
                    order[i-1].tileValue<<"\n";
                }
            }
            cout<<"Hardest tiles to blow up:\n";
            binary_heap<Tile, greater<Tile>> maxHeap(order.begin(),order.end());
            unsigned int heapSize = maxHeap.size();
            for(unsigned int i = 0; i < verbN && i < heapSize; i++)
            {
                escapeTile = maxHeap.top();
                maxHeap.pop();
                cout<<i+1<<" ("<<escapeTile.col<<","<<escapeTile.row<<"): "<<
                escapeTile.tileValue<<"\n";
            }
            cout<<"Easiest tiles to blow up:\n";
            binary_heap<Tile, less<Tile>> minHeap(order.begin(),order.end());
            heapSize = minHeap.size();
            for(unsigned int i = 0; i < verbN && i < heapSize; i++)
            {
                escapeTile = minHeap.top();
                minHeap.pop();
                cout<<i+1<<" ("<<escapeTile.col<<","<<escapeTile.row<<"): "<<
                escapeTile.tileValue<<"\n";
            }
            cout.flush();
        }
    }
    
    
    return 0;
}
