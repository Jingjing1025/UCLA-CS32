//
//  History.cpp
//  Project 1
//
//  Created by Jingjing on 11/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "History.h"

using namespace std;

History::History(int nRows, int nCols)
: m_rows(nRows), m_cols(nCols)
{
    // Fill the grid with dots
    for (int r = 0; r < m_rows; r++){
        for (int c = 0; c < m_cols; c++){
            m_grid[r][c] = '.';
        }
    }
}

bool History::record(int r, int c)
{
    if (r <= 0 || c <= 0 || r > m_rows || r > m_cols)
        return false;
    //record
    else if (m_grid[r-1][c-1] == '.')
        m_grid[r-1][c-1]='A';
    else if (m_grid[r-1][c-1] != 'Z'){
        m_grid[r-1][c-1]++;}
        return true;
}

void History::display() const
{
    clearScreen();
    for (int r = 0; r < m_rows; r++){
        for (int c = 0; c < m_cols; c++)
            cout << m_grid[r][c];
        cout << endl;
    }
    cout << endl;
}


