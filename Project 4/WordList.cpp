#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "MyHash.h"

using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<string, vector<string>> wordHash;
    string Patternize (string s) const
    {
        string newString;
        char max = 'A';
        
        for (int m = 0; m < s.size(); m++)
        {
            bool same = false;
            for (int n = 0; n < m; n++)
            {
                if (s[m] == tolower(s[n]) || s[m] == toupper(s[n]))
                {
                    newString += newString[n];
                    same = true;
                    break;
                }
            }
            if (!same)
            {
                newString += max;
                max ++;
            }
        }
        return newString;
    }
};

//load the contents of the indicated word list text file into the wordlist hash table
bool WordListImpl::loadWordList(string filename)
{
    wordHash.reset();
    ifstream infile(filename);    // infile is a name of our choosing
    if ( ! infile )                // Did opening the file fail?
        return false;
    else
    {
        string s;
        while (getline(infile, s))
        {

            vector<string> v;
            string Patterned = Patternize(s);
            const vector<string>* ptr = wordHash.find(Patterned);
            if (ptr == nullptr)
            {
                v.push_back(s);
                wordHash.associate(Patterned, v);
            }
            else
            {
                vector<string> v1 = *ptr;
                v1.push_back(s);
                wordHash.associate(Patterned, v1);
            }
        }
    }
    return true;
}

//determine if the specified word is in the word list
bool WordListImpl::contains(string word) const
{
    string Patterned = Patternize(word);
    const vector<string>* ptr = wordHash.find(Patterned);
    if (ptr == nullptr)
        return false;
    else
    {
        //under assumptions of uniform distribution and a finite constant word length, big O is O(1)
        for (int i = 0; i < (*ptr).size(); i++)
        {
            string d =(*ptr)[i];

            bool match = true;
            if (word.length() == (*ptr)[i].length())
            {
                for (int k = 0; k < word.length(); k++)
                {
                    if (tolower(word[k]) != (*ptr)[i][k] && toupper(word[k]) != (*ptr)[i][k])
                    {
                        match = false;
                        break;
                    }
                }
            }
            else
                match = false;
            if (match)
                return true;
        }
    }
    return false;
}

//  returns a vector of those words in the loaded word list that have the same letter pattern as the cipherWord and are consistent with currTranslation, the current plaintext translation of the cipherWord
vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    string Patterned = Patternize(cipherWord);
    const vector<string>* ptr = wordHash.find(Patterned);
    vector<string> s;
    if (ptr == nullptr)
        return vector<string>();
    else
    {
        //traverse through the words in wordlist that match the pattern to see if it qualifies as a candidate
        for (int i = 0; i < (*ptr).size(); i++)
        {
            bool match = true;
            for (int k = 0; k < currTranslation.length(); k++)
            {
                if (isalpha(currTranslation[k]))
                {
                    if (tolower(((*ptr)[i])[k]) != tolower(currTranslation[k]))
                    {
                        match = false;
                        break;
                    }
                }
                else if (currTranslation[k] == '?')
                {
                    if (!isalpha(((*ptr)[i])[k]))
                    {
                        match = false;
                        break;
                    }
                }
                else if (currTranslation[k] == '\'')
                {
                    if (((*ptr)[i])[k] != '\'')
                    {
                        match = false;
                        break;
                    }
                }
            }
            if (match)
            {
                string tem =(*ptr)[i];
                s.push_back((*ptr)[i]);
            }
        }
    }
    
    return s;
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}


