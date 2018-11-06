//
//  Investment.cpp
//  Homework 3
//
//  Created by Jingjing on 07/02/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

class Investment
{
public:
    Investment(string name, int purchasePrice)
    :m_name(name), m_purchasePrice(purchasePrice)
    {};
    
    string name() const {return m_name;}
    int purchasePrice() const  {return m_purchasePrice;}
    virtual bool fungible() const {return false; }
    virtual string description() const = 0;

    virtual ~Investment() {};
    
private:
    string m_name;
    int m_purchasePrice;
    string m_description;
};


class Painting: public Investment
{
public:
    Painting (string name, int purchasePrice)
    :Investment(name, purchasePrice)
    {};
    
    virtual string description() const
    {
        return "painting";
    }
    
    virtual ~Painting()
    {
        cout << "Destroying " << name() << ", a painting" <<endl;
    }
};


class Stock: public Investment
{
public:
    Stock (std::string name, int purchasePrice, std::string tickerSymbol)
    :Investment (name, purchasePrice), m_tickerSymbol(tickerSymbol)
    {
    };
    
    virtual bool fungible() const
    {
        return true;
    }
    
    virtual string description() const
    {
        string s = "stock trading as ";
        return s + m_tickerSymbol;
    }
    
    virtual ~Stock()
    {
        cout << "Destroying " << name() << ", a stock holding" <<endl;
    }
    
private:
    string m_tickerSymbol;
};

class House : public Investment
{
public:
    House (string name, int purchasePrice)
    :Investment(name, purchasePrice)
    {};
   
    virtual string description() const
    {
        return "house";
    }
    
    virtual ~House ()
    {
        cout << "Destroying the house " << name() <<endl;
    }
};

