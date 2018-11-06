//
//  main.cpp
//  Project 2-1
//
//  Created by Jingjing on 20/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <iostream>
#include "CarMap.h"
#include <cassert>
using namespace std;


void test() {
    
    CarMap m;
    assert(m.addCar("xyz"));            //Add a car with initial gas 0
    assert(m.gas("xyz") == 0);
    KeyType k = "hello";
    assert(!m.addGas("car", 10) && !m.addGas("xyz", -10));   //Cannot add gas if car is not present or gas value is negative
    assert(m.addGas("xyz", 10));      //add gas of 10
    m.addGas("xyz", 10);     //add another 10 gas
    assert(m.gas("xyz")==20);     //current gas amount is 20
    m.addCar("CAR");
    m.addGas("CAR", 5);
    assert(!m.useGas("CAR", 10)  && m.useGas("xyz", 10));     //Cannot use gas if gas usage > gas present
    assert(m.gas("xyz")==10);
    assert(m.fleetSize()==2);
    
    //print out the car and gas amount
    m.print();

}


int main()
{
    test();
    cout << "Passed all tests" << endl;
}
