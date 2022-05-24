//
//  mazestack.cpp
//  Homework2
//
//  Created by Jonathan on 4/30/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#include <stdio.h>
#include <stack>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    //Push the starting coordinate (sr,sc) onto the coordinate stack and
    //update maze[sr][sc] to indicate that the algorithm has encountered
    //it (i.e., set maze[sr][sc] to have a value other than '.').
    stack<Coord> mazeStack;
    Coord start( sr,sc);
    mazeStack.push(start);
    maze[sr][sc]= '@';
    //int counter = 1;
    while( !mazeStack.empty())
    {
        //Pop the top coordinate off the stack.
        Coord curr = mazeStack.top();
        mazeStack.pop();
        int cRow = curr.r();
        int cCol = curr.c();
        //cout<< counter++ <<". ( "<<cRow<<" , "<<cCol<<" )"<<endl;
        if( cRow == er && cCol == ec )
            return true;
        
        // SOUTH
        char visit = maze[cRow+1][cCol] ;
        if(visit != 'X' && visit != '@' && cCol != 10 )
        {
            Coord south( cRow+1, cCol);
            mazeStack.push(south);
            maze[cRow+1][cCol] = '@';
        }
        visit = maze[cRow][cCol-1];
        // move WEST
        if( visit != 'X' &&  visit != '@' && cCol != 0)
        {
            Coord west( cRow,cCol-1);
            mazeStack.push(west);
            maze[cRow][cCol-1] ='@';
        }
        // move NORTH
        visit =maze[cRow-1][cCol];
        if( visit != 'X' &&  visit != '@' && cRow !=0 )
        {
            Coord north( cRow-1,cCol);
            mazeStack.push(north);
            maze[cRow-1][cCol] ='@';
        }
        // move EAST
        visit = maze[cRow][cCol+1];
        if( visit != 'X' &&  visit != '@' && cCol !=10)
        {
            Coord east( cRow,cCol+1);
            mazeStack.push(east);
            maze[cRow][cCol+1] ='@';
        }
        
    }
    return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','.','X','X','.','X','X','X','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    if (pathExists(maze, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
