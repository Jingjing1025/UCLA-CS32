//
//  list.cpp
//  Homework 4-2
//
//  Created by Jingjing on 01/03/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <stdio.h>

#include "Class.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


void listAll(const Class* c, string path)  // two-parameter overload
{
    if (c == nullptr)
        return;
    if (path == "")
        path = c->name();
    else
        path = path + "=>" + c->name();
    cout << path << endl;
    
    for (vector<Class*>::const_iterator it = c->subclasses().begin(); it != c->subclasses().end(); it++)
        listAll(*it, path);
}
