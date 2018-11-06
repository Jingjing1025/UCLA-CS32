//
//  maze.cpp
//  Homework 3 - 3
//
//  Created by Jingjing on 09/02/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = 'o';
    if (maze[sr][sc+1] != 'X' && maze[sr][sc+1] != 'o')    //If you can move EAST and haven't encountered that cell
    {
        if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }
    if (maze[sr+1][sc] != 'X' && maze[sr+1][sc] != 'o')    //check SOUTH
    {
        if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    if (maze[sr][sc-1] != 'X' && maze[sr][sc-1] != 'o')    //check WEST
    {
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    if (maze[sr-1][sc] != 'X' && maze[sr-1][sc] != 'o')    //check NORTH
    {
        if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    return false;
}
