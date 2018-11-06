//
//  Map.cpp
//  Project 2
//
//  Created by Jingjing on 19/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Map.h"

Map::Map(){
    m_Size = 0;
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
    if (!contains(key) && m_Size < DEFAULT_MAX_ITEMS){
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
    else if (!contains(key) && m_Size < DEFAULT_MAX_ITEMS){
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
    int tempSize = 0;
    tempSize = m_Size;
    m_Size = other.m_Size;
    other.m_Size = tempSize;
    
    if (m_Size > other.m_Size)
        tempSize = m_Size;
    else
        tempSize = other.m_Size;
    
    m_Map tempStruct;
    for (int i = 0; i < tempSize; i++){
        tempStruct = other.m_Arr[i];
        other.m_Arr[i] = m_Arr[i];
        m_Arr[i] = tempStruct;
    }
}

