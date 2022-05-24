//
//  History.cpp
//  project1
//
//  Created by Jonathan on 4/3/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#include "History.h"
#include <iostream>
using namespace std;
History::History(int nRows, int nCols)
{
    // initlized the grid with just like the code provded
    m_row = nRows;
    m_col = nCols;
    for( int r =0 ; r < m_row ; r++)
        for( int c =0 ; c < m_col ; c++)
            m_grid[r][c]= '.';
}
bool History :: record(int r, int c)
{
    // Return false if r and c is out of bound
    if( r < 1 || c < 1 || c > m_col || r > m_row )
        return false;
    
    //set the grid with the wanted resulted
    char& gridChar = m_grid[r-1][c-1];
    switch( gridChar)
    {
        case '.':
            gridChar='A';
            break;
        case 'Z':
            break;
        default:  // from 2-25 char +1.....
            gridChar++;
            break;;
    }
    m_grid[r-1][c-1] = gridChar;
    return true;
}
void History :: display() const
{
    clearScreen();
    for( int r =0 ; r < m_row ; r++)
    {
        for (int c = 0; c < m_col; c++)
            cout << m_grid[r][c];
        cout << endl;
    }
    cout << endl;
}
