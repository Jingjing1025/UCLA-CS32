//
//  Game.h
//  Project 1
//
//  Created by Jingjing on 10/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#ifndef Game_h
#define Game_h

class City;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};

#endif /* Game_h */
