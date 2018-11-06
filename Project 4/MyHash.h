// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.


#ifndef MyHash_INCLUDED
#define MyHash_INCLUDED

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    // initialize your hash table by setting the size of its initial dynamic array to 100 buckets
    MyHash(double maxLoadFactor = 0.5)
    {
        m_bucket = 100;
        m_items = 0;
        m_Hash = new item*[m_bucket];
        
        if (maxLoadFactor <= 0)
            maxLoad = 0.5;
        else if (maxLoadFactor > 2)
            maxLoad = 2.0;
        maxLoad  = maxLoadFactor;
        
        for (int i = 0; i < m_bucket; i++)
            m_Hash[i] = nullptr;
    }
    
    // free all memory associated with hash table
    ~MyHash()
    {
        for (int i = 0; i < m_bucket; i++)
        {
            item* p = m_Hash[i];
            while (p != nullptr)
            {
                item* kill = p;
                p = p->next;
                delete kill;
            }
        }
        delete []m_Hash;
    }
    
    //free all of the memory associated with the current hash table, then allocate a new empty hash table of the default size of 100 buckets
    void reset()
    {
        for (int i = 0; i < m_bucket; i++)
        {
            item* p = m_Hash[i];
            while (p != nullptr)
            {
                item* kill = p;
                p = p->next;
                delete kill;
            }
        }
        delete []m_Hash;
        m_bucket = 100;
        m_items = 0;
        m_Hash = new item*[m_bucket];
        
        for (int i = 0; i < m_bucket; i++)
            m_Hash[i] = nullptr;
    }
    
    //adds a new association to the hash table associating the specified key
    void associate(const KeyType& key, const ValueType& value)
    {
        ValueType* keyFound = find(key);
        if (keyFound != nullptr)
            *keyFound = value;        //discard the old value and update the new one
        else
        {
            unsigned int hash(const KeyType& k);
            unsigned int h = hash(key);
            int index = h % m_bucket;
            if (m_Hash[index] == nullptr)
            {
                m_Hash[index] = new item;
                m_Hash[index]->m_key =  key;
                m_Hash[index]->m_value = value;
                m_Hash[index]->next = nullptr;
                m_items++;
            }

            else
            {
                item* p = m_Hash[index];
                while (p->next != nullptr)
                {    p = p->next;   }
                p->next = new item;
                p->next->m_key = key;
                p->next->m_value = value;
                p->next->next = nullptr;
                m_items ++;
            }
        }
        
        //allocate a new dynamic array that has double the number of buckets the current dynamic array has if the maxLoad is reached
        if (getLoadFactor() > maxLoad)
        {
            int newBucket = m_bucket*2;
            item** newHash = new item*[newBucket];
            for (int i = 0; i < newBucket; i++)
                newHash[i] = nullptr;
            for (int i = 0; i < m_bucket; i++)
            {
                item* p = m_Hash[i];
                while (p != nullptr)
                {
                    unsigned int hash(const KeyType& k);
                    unsigned int h = hash(p->m_key);
                    int index = h % (newBucket);
                    if (newHash[index] == nullptr)
                    {
                        newHash[index] = new item;
                        newHash[index]->m_key = p->m_key;
                        newHash[index]->m_value = p->m_value;
                        newHash[index]->next = nullptr;
                    }
                    else
                    {
                        item* temp = newHash[index];
                        while (temp->next != nullptr)
                        {
                            temp = temp->next;
                        }
                        temp->next = new item;
                        temp->next->m_key = p->m_key;
                        temp->next->m_value = p->m_value;
                        temp->next->next = nullptr;
                    }
                    p = p->next;
                }
            }

            //delete the old hash table
            for (int i = 0; i < m_bucket; i++)
            {
                item* p = m_Hash[i];
                while (p != nullptr)
                {
                    item* kill = p;
                    p = p->next;
                    delete kill;
                }
            }
            delete []m_Hash;
            m_Hash = newHash;
            m_bucket = newBucket;
        }

    }
    
    int getNumItems() const { return m_items; }
    
    double getLoadFactor() const { return m_items/m_bucket; }

    // for a map that can't be modified, return a pointer to const ValueType
    //locate the item with a key equal to key in the hash table, and if successful, returns a pointer to the value associated with that key
    const ValueType* find(const KeyType& key) const
    {
        unsigned int hash(const KeyType& k);
        unsigned int h = hash(key);
        int index = h % m_bucket;
        item* p = m_Hash[index];
        while (p != nullptr)
        {
            if (p->m_key==key)
            {
                ValueType* val = &(p->m_value);
                return val;
            }
            p = p->next;
        }
        return nullptr;
    }

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
    struct item
    {
        KeyType m_key;
        ValueType m_value;
        item* next;
    };
    
    double maxLoad;
    int m_bucket;
    double m_items;
    item** m_Hash;
};

#endif // MyHash_INCLUDED


/*
#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED

#include <unordered_map>  // YOU MUST NOT USE THIS HEADER IN CODE YOU TURN IN
#include <algorithm>

// In accordance with the spec, YOU MUST NOT TURN IN THIS CLASS TEMPLATE,
// since you are not allowed to use any STL containers, and this
// implementation uses std::unordered_map.

// This code is deliberately obfuscated.

// If you can not get your own MyHash class template working, you may use
// this one during development in order to let you proceed with implementing
// the other classes for this project; you can then go back to working on
// fixing your own MyHash class template.

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
    using O=KeyType;using maxloadfactor=float;using O10=int;void reset(){
        maxloadfactor max_1oad_factor=l01.max_load_factor();l01.clear();l01.
        max_load_factor(max_1oad_factor);l01.rehash(doub1e+doub1e);}using String=
    double;using l0=ValueType;using l1O=O10 const;MyHash(String d0uble=doub1e/10):
    l01(doub1e+doub1e){l01.max_load_factor(std::min<maxloadfactor>(doub1e/5/5,
                                                                   std::max<maxloadfactor>((double)doub1e/(doub1e+doub1e),d0uble)));}using l10=O
    const;using Const=MyHash<O,l0>;String getLoadFactor()const{return l01.
        load_factor();}using ll0=l0 const;O10 getNumItems()const{return l01.size(
            );}using l00=Const const;void associate(l10&Using,ll0&first){l01[Using]=
                first;}using l1=std::unordered_map<O,l0>;ll0*find(l10&l11)const{auto first(l01.
                                                                                           find(l11));return(first!=l01.end()?&first->second:0);}l0*find(l10&l01){return(
                                                                                                                                                                         l0*)(*(l00*)(this)).find(l01);}private:static l1O doub1e{50};l1 l01;
};

#endif // MYHASH_INCLUDED

*/


