//
//  Map.cpp
//  Project 2
//
//  Created by Jingjing on 24/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <stdio.h>
#include "Map.h"

Map::Map(){
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

Map::Map(const Map& other){
    head = nullptr;
    tail = nullptr;
    m_size = 0;
    
    int s = other.m_size;
    
    Pair* o = other.head;
    if (o == nullptr){                   //if other is empty, my Map is also empty
        head = tail = nullptr;
        return;
    }
    
    for (int i = 0; i < s; i++){
        if (head == nullptr){            //if my Map is empty
            Pair* p = new Pair;
            p->m_key = o->m_key;         //assign other's key to the new Map
            p->m_value = o->m_value;     //assign other's value to the new Map
            p->next = nullptr;
            p->previous = nullptr;
            head = p;
            tail = p;
            o = o->next;
        }
        else {
            Pair* n = new Pair;
            
            n->m_key = o->m_key;              //assign other's key to the new Map
            n->m_value = o->m_value;          //assign other's value to the new Map
            n->previous = tail;               //link new "previous" to old pair
            tail->next = n;                   //link old "next" to new pair
            n->next = nullptr;                //link new "next" to nullptr (end)
            tail = n;                         //"tail" to new pair
            o = o->next;                      //move other pointer down to the next pair
        }
    }
    
    m_size = s;
}


Map& Map::operator=(const Map& rhs){   //use swap function for assignment operator
    if (this != &rhs)
    {
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}


Map::~Map(){      //Destructing linked list
    Pair *p;
    p = head;
    while(p != nullptr){
        Pair* m = p->next;
        delete p;
        p = m;
    }
    
}


int Map::size() const
{
    return m_size;
}


bool Map::empty() const
{
    return size() == 0;
}


bool Map::contains(const KeyType& key) const
{
    return find(key) != nullptr;
}


bool Map::insert(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, true /* insert */, false /* no update */);
}


bool Map::update(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, false /* no insert */, true /* update */);
}


bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, true /* insert */, true /* update */);
}


bool Map::erase(const KeyType& key)
{
    Pair* pos = find(key);
    if (pos == nullptr)  // not found
        return false;
    
    // if found, delete the node
    if (pos == head && pos == tail){      //the node to be deleted is the only node
        head = nullptr;
        tail = nullptr;
    }
    
    else if (pos == head && pos != tail){            //the node to be deleted is the first node
        head = pos->next;
        head->previous = nullptr;
    }
    
    else if (pos != head && pos == tail){       //the node to be deleted is the last node
        tail = pos->previous;
        tail->next = nullptr;
    }
    
    else{                 //the node to be deleted is in the middle
        pos->previous->next = pos->next;
        pos->next->previous = pos->previous;
    }
    delete pos;
    m_size--;
    return true;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    Pair* pos = find(key);
    if (pos == nullptr)  // not found
        return false;
    value = pos->m_value;
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;
    Pair* p = head;
    for (int k = 0; k<i; k++){      //go to the i the node in the linked list
        p=p->next;
    }
    key = p->m_key;
    value = p->m_value;
    return true;
}

void Map::swap(Map& other)
{
    if (&other == this)     //do nothing if it is swaping with itself
        return;
    
    // Swap the head and tail pointers
    Pair* tempHeader = head;
    Pair* tempTail = tail;
    head = other.head;
    tail = other.tail;
    other.head = tempHeader;
    other.tail = tempTail;
    
    // Swap sizes
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
    
}

Map::Pair* Map::find(const KeyType& key) const
{
    Pair* p = head;

    // Do a linear search through the linked list.
    while (p != nullptr){
        if (p->m_key==key)
            return p;
        p=p->next;
    }
    
    return nullptr;
}

bool Map::doInsertOrUpdate(const KeyType& key, const ValueType& value,
                           bool mayInsert, bool mayUpdate)
{
    Pair* pos = find(key);
    if (pos != nullptr)  // found
    {
        if (mayUpdate)
            pos->m_value = value;
        return mayUpdate;
    }
    
    if (!mayInsert)  // not found, and not allowed to insert
        return false;

    if (head==nullptr){   //if empty linked list
        Pair* p = new Pair;
        p->m_key = key;
        p->m_value = value;
        p->next = nullptr;
        p->previous = nullptr;
        head = p;
        tail = p;
    }
    
    //insert at the end of the linked list
    else{
        Pair* n = new Pair;
        n->m_key = key;
        n->m_value = value;
        n->previous = tail;
        n->next = nullptr;
        tail->next = n;
        tail = n;
    }

    m_size++;
    return true;
}


bool combine(const Map& m1, const Map& m2, Map& result){
   
    Map tempResult;       //Use a temporary Map tempResult

    bool b = true;
    Map* r = &tempResult;
    const Map* p1 = &m1;
    const Map* p2 = &m2;
    int m1Size = p1->size();
    int m2Size = p2->size();
    KeyType key1,key2;
    ValueType value1,value2;
    
    if (&m1 == &m2 && &m1 == &result){
        //Does nothing if all the three Maps are the one
    }
    
    else {
        for (int i = 0; i<m1Size; i++){      //traverse through m1 and check each value
            p1->get(i, key1, value1);
            if (p2->contains(key1)){         //if the value is also found in m2, check their values
                p2->get(key1, value2);
                if (value1!=value2){         //return false and do not insert if two values are not the same
                    b = false;
                }
                else                         //insert if values are the same
                  r->insert(key1, value1);
            }
            else {                           //insert if not found in m2
                r->insert(key1, value1);
            }
            
        }
        
        for (int i = 0; i<m2Size; i++){     //traverse through m2 and insert the ones that are not found in m1
            p2->get(i, key2, value2);
            if (!p1->contains(key2)){
                r->insert(key2, value2);
            }
        }
        result = tempResult;   //assign tempResult to result
    }
    return b;
}


void subtract(const Map& m1, const Map& m2, Map& result){
    Map tempResult;                   //use a temporary Map tempResult
    Map* r = &tempResult;
    const Map* p2 = &m2;
    int m2Size = p2->size();
    KeyType key2;
    ValueType value2;
    
    tempResult = m1;                  //assign m1 to temporary Map tempResult
    for (int i = 0; i<m2Size; i++){   //traverse through m2 and remove duplicates from tempResult
        p2->get(i, key2, value2);
        if (r->contains(key2)){
            r->erase(key2);
        }
    }
    
    result = tempResult;             //assign tempResult to result
    
}

