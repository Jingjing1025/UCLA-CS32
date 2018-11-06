//
//  City.h
//  Project 1
//
//  Created by Jingjing on 10/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#ifndef City_h
#define City_h

#include "globals.h"
#include "History.h"

class History;
class Flatulan;
class Player;

class City
{
public:
    // Constructor/destructor
    City(int nRows, int nCols);
    ~City();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     flatulanCount() const;
    int     nFlatulansAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    
    // Mutators
    bool  addFlatulan(int r, int c);
    bool  addPlayer(int r, int c);
    void  preachToFlatulansAroundPlayer();
    void  moveFlatulans();
    
    History& history();
    
private:
    int       m_rows;
    int       m_cols;
    Player*   m_player;
    Flatulan* m_flatulans[MAXFLATULANS];
    int       m_nFlatulans;
    
    History   m_history;
    
    // Helper functions
    bool isInBounds(int r, int c) const;
};

#endif /* City_h */
