//
//  testnewMap.cpp
//  Project 2
//
//  Created by Jingjing on 20/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;


///// VALUE = DOUBLE; KEY = STRING ///////

void test()
{
    Map a(1000);   // a can hold at most 1000 key/value pairs
    Map b(5);      // b can hold at most 5 key/value pairs
    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
    KeyType k[6] = { "andy","beta","ciara","diana","emily","fiona" };
    KeyType j[5] = {"greg","howard","inga","jenny","kelly" };
    ValueType v  = 100;
    
    // No failures inserting pairs with 5 distinct keys into b
    for (int n = 0; n < 5; n++)
        assert(b.insert(k[n], v));
    
    for (int n = 0; n < 5; n++){
        b.insert(j[n], v);
    }
    for (int n = 0; n < 6; n++){
        a.insert(k[n], v);
    }
    
    // Failure if we try to insert a pair with a sixth distinct key into b
    assert(!b.insert(k[5], v));
    
    // When two Maps' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(k[5], v));
    assert(!b.insert(k[5], v));  //cannot insert with the same key present
    assert(b.insert(j[4], v));
    assert(a.size()==5 && b.size()==7);
    
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
    m1.insert("Greg", 5.98);
    m1.insert("Fred", 0.9);
    m1.insert("Howard", 3.3);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  && m2.size() == 3  &&  m2.contains("Fred"));
    assert(!m1.contains("Fred") && !m1.contains("Greg")&&!m1.contains("Howard") && !m2.contains("Ethel")&& !m2.contains("Lucy"));
    
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
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}


////// VALUE = STRING; KEY = INT /////
//#include "newMap.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Map m;
//    assert(m.insert(10, "diez"));
//    assert(m.insert(20, "veinte"));
//    assert(m.size() == 2);
//    ValueType v = "cuarenta y dos";
//    assert(!m.get(30, v)  &&  v == "cuarenta y dos");
//    assert(m.get(10, v)  &&  v == "diez");
//    v = "cuarenta y dos";
//    KeyType x = 30;
//    assert(m.get(0, x, v)  &&
//           ((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
//    KeyType x2 = 40;
//    assert(m.get(1, x2, v)  &&
//           ((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
//           x != x2);
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}

