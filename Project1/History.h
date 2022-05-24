//
//  History.hpp
//  project1
//
//  Created by Jonathan on 4/3/19.
//  Copyright © 2019 Jonathan. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"
class Arena;
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_row;
    int m_col;
    char m_grid[MAXROWS][MAXCOLS];
};

#endif /* History_hpp */
//
