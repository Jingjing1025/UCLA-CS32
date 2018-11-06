//
//  Map.h
//  Project 2
//
//  Created by Jingjing on 24/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <iostream>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    Map();  //constructor
    ~Map();   //destructor
    Map(const Map& other);  //copy constructor
    Map& operator=(const Map& rhs);   //Assignment Operator
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    
private:
    struct Pair
    {
        KeyType   m_key;
        ValueType m_value;
        Pair* previous;
        Pair* next;
    };
        
    int  m_size;       // number of pairs in the map
    
    // At any time, the elements of m_data indexed from 0 to m_size-1
    // are in use.
    
    Pair* find(const KeyType& key) const;
    // Return index of the pair in m_data whose m_key == key if there is
    // one, else -1
    
    bool doInsertOrUpdate(const KeyType& key, const ValueType& value,
                          bool mayInsert, bool mayUpdate);
    // If the key is not present in the map and if mayInsert is true, insert
    // the pair if there is room.  If the key is present and mayUpdate is
    // true, update the pair with the given key.
    
    Pair* head;
    Pair* tail;
    
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);


#endif /* Map_h */
