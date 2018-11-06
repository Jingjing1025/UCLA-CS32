//
//  CarMap.cpp
//  Project 2
//
//  Created by Jingjing on 19/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "CarMap.h"

CarMap::CarMap(){
    
}

bool CarMap::addCar(KeyType license) {
    if (!mMap.contains(license) && mMap.size() < DEFAULT_MAX_ITEMS) {
        mMap.insert(license, 0);
        return true;
    }
    return false;
}


double CarMap::gas(KeyType license) const {
    ValueType v;
    if (mMap.contains(license)) {
        mMap.get(license, v);
        return v;
    }
    return -1;
}

bool CarMap::addGas(KeyType license, ValueType gallons) {
    ValueType v;
    if (!mMap.contains(license) || gallons < 0) {
        return false;
    }
    mMap.get(license, v);
    mMap.update(license, gallons+v);
    return true;
}


bool CarMap::useGas(KeyType license, ValueType gallons) {
    if (!mMap.contains(license) || gallons < 0 || gallons > gas(license)) {
        return false;
    }
    mMap.update(license, gas(license)-gallons);
    return true;
}


int CarMap::fleetSize() const {
    return mMap.size();
}


void CarMap::print() const {
    KeyType k;
    ValueType v;
    for (int i = 0; i < mMap.size(); i++){
        mMap.get(i, k, v);
        std::cout << k << " " << v << std::endl;
    }
}

