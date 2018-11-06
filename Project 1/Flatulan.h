//
//  Flatulan.h
//  Project 1
//
//  Created by Jingjing on 10/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//


#ifndef Flatulan_h
#define Flatulan_h

class City;

class Flatulan
{
public:
    // Constructor
    Flatulan(City* cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool possiblyGetConverted();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
};

#endif /* Flatulan_h */

