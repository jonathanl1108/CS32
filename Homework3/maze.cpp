//
//  maze.cpp
//  Homework3
//
//  Created by Jonathan on 5/9/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    //base case
    int row=sr;
    int col=sc;
    //If the start location is equal to the ending location, then we've
    //solved the maze, so return true.
    if(sr==er && sc==ec)
        return true;
    maze[sr][sc]= '@';
    /*
     Mark the start location as visted.
     For each of the four directions,
     If the location one step in that direction (from the start
     location) is unvisited,
     then call pathExists starting from that location (and
     ending at the same ending location as in the
     current call).
     If that returned true,
     then return true.
     Return false.
     */
    
    //SOUTH
    if( maze[row+1][col] != 'X' &&  maze[row+1][col] != '@' && row != 9)
    {
        if(pathExists( maze, row+1, col , er, ec))
            return true;
    }
    //WEST
    if( maze[row][col-1] != 'X' &&  maze[row][col-1] != '@' && col != 0)
    {
        if(pathExists( maze,row,col-1 , er, ec))
            return true;
    }
    //NORTH
    if( maze[row-1][col] != 'X' &&  maze[row-1][col] != '@' && row != 0)
    {
        if(pathExists( maze, row-1, col , er, ec))
            return true;
    }
    //EAST
    if( maze[row][col+1] != 'X' &&  maze[row][col+1] != '@' && col != 9)
    {
        if(pathExists( maze,row, col+1 , er, ec))
            return true;
    }
    return false;
}


