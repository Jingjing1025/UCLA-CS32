//
//  History.h
//  Project 1
//
//  Created by Jingjing on 11/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    char m_grid[MAXROWS][MAXCOLS];
};

#endif /* History_h */

