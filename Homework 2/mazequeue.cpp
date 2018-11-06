//
//  mazequeue.cpp
//  Homework 2
//
//  Created by Jingjing on 03/02/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//


#include <queue>
#include <string>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


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


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    // enqueue the starting coordinate (sr,sc) onto the coordinate queue and
    // update maze[sr][sc] to indicate that the algorithm has encountered
    // it (i.e., set maze[sr][sc] to have a value other than '.').
    queue<Coord> coordQueue;
    Coord start = Coord(sr,sc);
    coordQueue.push(start);
    maze[sr][sc] = 'o';
    
    while (!coordQueue.empty())         //While the stack is not empty
    {
        Coord cur = coordQueue.front();
        int r = 0;
        int c = 0;
        r = cur.r();
        c = cur.c();
        coordQueue.pop();              //Pop the top coordinate off the stack.
        if (r == er && c == ec)        //If the current (r,c) coordinate is equal to the ending coordinate,
            return true;               //then we've solved the maze so return true!
        
        //check each place that can move
        if (maze[r][c+1] != 'X' && maze[r][c+1] != 'o')    //If you can move EAST and haven't encountered that cell
        {
            coordQueue.push(Coord(r,c+1));       //push the coordinate (r,c+1) onto the stack
            maze[r][c+1] = 'o';                  //update maze[r][c+1] to indicate the algorithm has encountered it.
        }
        if (maze[r+1][c] != 'X' && maze[r+1][c] != 'o')    //check SOUTH
        {
            coordQueue.push(Coord(r+1,c));
            maze[r+1][c] = 'o';
        }
        if (maze[r][c-1] != 'X' && maze[r][c-1] != 'o')    //check WEST
        {
            coordQueue.push(Coord(r,c-1));
            maze[r][c-1] = 'o';
        }
        if (maze[r-1][c] != 'X' && maze[r-1][c] != 'o')    //check NORTH
        {
            coordQueue.push(Coord(r-1,c));
            maze[r-1][c] = 'o';
        }
    }
    return false;     //There was no solution, so return false
}

