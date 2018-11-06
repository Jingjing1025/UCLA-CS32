//
//  newMap.cpp
//  Project 2
//
//  Created by Jingjing on 20/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <stdio.h>
#include <iostream>

//
//  Map.cpp
//  Project 2
//
//  Created by Jingjing on 19/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include "newMap.h"

Map::Map(){
    m_nPairs = DEFAULT_MAX_ITEMS;
    m_Size = 0;
    m_Arr = new m_Map[m_nPairs];
}


Map::Map(int nPairs) {
    if (nPairs < 0){
        std::cout << "The number of maximum pairs cannot be negative" << std::endl;
        exit(0);
    }
    m_nPairs = nPairs;
    m_Size = 0;
    m_Arr = new m_Map[m_nPairs];
}

Map::Map(const Map& other)
{
    m_nPairs = other.m_nPairs;
    m_Size = other.m_Size;
    m_Arr = new m_Map[m_nPairs];
    for (int i = 0; i < m_Size; i++)
    {
        m_Arr[i] = other.m_Arr[i];
    }
}

Map& Map::operator=(const Map& other)
{
    if(&other == this)
        return *this;
    delete []m_Arr;
    m_nPairs = other.m_nPairs;
    m_Size = other.m_Size;
    m_Arr = new m_Map[m_nPairs];
    for (int i = 0; i < m_Size; i++){
        m_Arr[i] = other.m_Arr[i];
    }
    return *this;
}


bool Map::empty() const{
    if (size() == 0)
        return true;
    return false;
}

int Map::size() const{
    return m_Size;
}


bool Map::insert(const KeyType& key, const ValueType& value){
    if (!contains(key) && m_Size < m_nPairs){
        m_Arr[m_Size].m_Key = key;
        m_Arr[m_Size].m_Value = value;
        m_Size ++;
        
        return true;
    }
    return false;
}


bool Map::update(const KeyType& key, const ValueType& value)
{
    for (int i = 0; i < m_Size; i++)
    {
        if (key == m_Arr[i].m_Key){
            m_Arr[i].m_Value = value;
            return true;
        }
    }
    return false;
}


bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    if (contains(key)){
        update(key, value);
        return true;
    }
    else if (!contains(key) && m_Size < m_nPairs){
        insert(key, value);
        return true;
    }
    return false;
}


bool Map::erase(const KeyType& key){
    for (int i = 0; i < m_Size; i++)
    {
        if (key == m_Arr[i].m_Key){
            for (int j = i; j < m_Size-1; j++){
                m_Arr[j] = m_Arr[j+1];
            }
            m_Size --;
            return true;
        }
    }
    return false;
}


bool Map::contains(const KeyType& key) const{
    for (int i = 0; i < m_Size; i++)
    {
        if (key == m_Arr[i].m_Key){
            return true;
        }
    }
    return false;
}


bool Map::get(const KeyType& key, ValueType& value) const {
    for (int i = 0; i < m_Size; i++)
    {
        if (key == m_Arr[i].m_Key){
            value = m_Arr[i].m_Value;
            return true;
        }
    }
    return false;
}


bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (i >= 0 && i < m_Size){
        key = m_Arr[i].m_Key;
        value = m_Arr[i].m_Value;
        return true;
    }
    return false;
}

void Map::swap(Map& other) {
    Map temp(other);
    other = *this;
    *this = temp;
}

Map::~Map(){
    delete [] m_Arr;
}

