#include "provided.h"
#include <string>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    ~TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    class Pair
    {
    public:
        Pair(){};
        Pair(char cipher, char plain){ m_cipher = cipher; m_plain = plain; }
        char m_cipher;
        char m_plain;
    };
    Pair* currTranslator;
    vector<Pair*> m_stack;
    int m_size;
};

//initialize the mapping by setting all plain letters to '?'
TranslatorImpl::TranslatorImpl()
{
    m_size = 0;
    currTranslator = new Pair[26];
    for (int i = 65; i < 91; i++)
    {
        char cipher = i;
        currTranslator[i-65] = Pair(cipher, '?');
    }
    m_stack.push_back(currTranslator);
}

TranslatorImpl::~TranslatorImpl()
{
    while (m_stack.begin() != m_stack.end())
    {
        delete []m_stack.back();
        m_stack.pop_back();
    }
}

// takes a collection of new mappings from ciphertext letters to plaintext letters
// Since all word lengths are constants, the big O is O(1)
bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    currTranslator = new Pair[26];
    Pair* topTranslator = m_stack[m_size];
    for (int i = 0; i < 26; i++)
    {
        currTranslator[i] = topTranslator[i];
    }
    if (ciphertext.length() != plaintext.length())
    {
        delete []currTranslator;
        return false;
    }
    for (int i = 0; i < ciphertext.length(); i++)
    {
        if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
        {
            delete []currTranslator;
            return false;
        }
        int index = toupper(ciphertext[i])-'A';
        if (currTranslator[index].m_plain != '?' && currTranslator[index].m_plain != toupper(plaintext[i]))
        {
            delete []currTranslator;
            return false;
        }
        else
            currTranslator[index].m_plain = toupper(plaintext[i]);
    }
    
    //check if different words will map to same word
    char arr[26] = {};
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(currTranslator[i].m_plain))
        {
            int plainPos = toupper(currTranslator[i].m_plain)-'A';
            if (arr[plainPos] == currTranslator[i].m_plain)
            {
                delete []currTranslator;
                return false;
            }
            else
                arr[plainPos] = currTranslator[i].m_plain;
        }
    }
    m_size++;
    m_stack.push_back (currTranslator);
    return true;
}

//pop the most-recently pushed mapping table from the stack, make it the current mapping table, and return true, if possible
bool TranslatorImpl::popMapping()
{
    if (m_size==0)
        return false;
    else
    {
        delete [] m_stack.back();
        m_stack.pop_back();
        m_size--;
    }
    return true;
}

//translates its argument string according to the current mapping table and returns the resulting string of the same length
string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string s;
    for (int i = 0; i < ciphertext.length(); i++)
    {
        if (isalpha(ciphertext[i]))
        {
            int index = (toupper(ciphertext[i])-'A');
            if (m_stack[m_size][index].m_plain == '?')
                s += '?';
            else if (islower(ciphertext[i]))
                s += (tolower(m_stack[m_size][index].m_plain));
            else if (isupper(ciphertext[i]))
                s += (m_stack[m_size][index].m_plain);
        }
        else
            s += ciphertext[i];
    }
    return s;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
