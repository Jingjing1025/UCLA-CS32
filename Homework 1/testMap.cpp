//
//  main.cpp
//  Project 2
//
//  Created by Jingjing on 19/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//


// maps strings to doubles

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map f;
    assert(f.empty());
    ValueType v = -1234.5;
    assert( !f.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    f.insert("xyz", 9876.5);
    assert(f.size() == 1);
    KeyType k = "hello";
    assert(f.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);

    Map n;
    n.insert("amy", 5);
    n.insert("brandon", 1);
    assert(n.size()==2);
    assert(n.contains("amy") && n.insert("qq", 30));
    n.insert("qq", 30);
    assert(!n.update("eddy", 9));

    Map gpas;
    gpas.insert("Fred", 2.956);
    gpas.insert("Ethel", 3.538);
    double v1;
    string k1;
    assert(gpas.get(1,k1,v1)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
    string k2;
    assert(gpas.get(1,k2,v1)  &&  k2 == k1);

    Map gpas1;
    gpas1.insert("Fred", 2.956);
    assert(!gpas1.contains(""));
    gpas1.insert("Ethel", 3.538);
    gpas1.insert("", 4.000);
    gpas1.insert("Lucy", 2.956);
    assert(gpas1.contains(""));
    gpas1.erase("Fred");
    assert(gpas1.size() == 3);
    assert(gpas1.contains("Lucy"));
    assert(gpas1.contains("Ethel")  && gpas1.contains(""));

    Map m1;
    m1.insert("Fred", 2.956);
    m1.insertOrUpdate("Greg", 2.22);
    m1.insert("Howard", 3.333);
    m1.insertOrUpdate("Greg", 100.35);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  && m2.size() == 3  &&  m2.contains("Fred"));
    assert(!m1.contains("Fred") && !m2.contains("Ethel") && !m2.contains("Lucy"));

    Map m;
    assert(m.insert("Fred", 2.956));
    assert(m.insert("Ethel", 3.538));
    assert(m.size() == 2);
    ValueType v2 = 42;
    assert(!m.get("Lucy", v2)  &&  v2 == 42);
    assert(m.get("Fred", v2)  &&  v2 == 2.956);
    v2 = 42;
    KeyType x = "Lucy";
    assert(m.get(0, x, v2)  &&
           ((x == "Fred"  &&  v2 == 2.956)  ||  (x == "Ethel"  &&  v2 == 3.538)));
    KeyType x2 = "Ricky";
    assert(m.get(1, x2, v2)  &&
           ((x2 == "Fred"  &&  v2 == 2.956)  ||  (x2 == "Ethel"  &&  v2 == 3.538))  &&
           x != x2);

    cout << "Passed all test" << endl;
}



/*
// maps ints to strings

#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m;
    assert(m.insert(10, "diez"));
    assert(m.insert(20, "veinte"));
    assert(m.size() == 2);
    ValueType v = "cuarenta y dos";
    assert(!m.get(30, v)  &&  v == "cuarenta y dos");
    assert(m.get(10, v)  &&  v == "diez");
    v = "cuarenta y dos";
    KeyType x = 30;
    assert(m.get(0, x, v)  &&
           ((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
    KeyType x2 = 40;
    assert(m.get(1, x2, v)  &&
           ((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
           x != x2);

    Map m1;
    assert(m1.empty());
    ValueType v1 = "Ouch";
    assert( !m1.get(42, v1)  &&  v1 == "Ouch"); // v unchanged by get failure
    m1.insert(123456789, "Wow!");
    assert(m1.size() == 1);
    KeyType k = 9876543;
    assert(m1.get(0, k, v1)  &&  k == 123456789  &&  v1 == "Wow!");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
*/
