#include "provided.h"
#include <string>
#include <vector>
using namespace std;

#include <iostream>

class DecrypterImpl
{
public:
    DecrypterImpl();
    ~DecrypterImpl();
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    void insertion_sort(vector<string>& s)
    {
        for (size_t k = 1; k < s.size(); k++)
        {
            string currentString(s[k]);
            size_t m = k;
            for ( ; m > 0  &&  currentString < s[m-1]; m--)
                s[m] = s[m-1];
            s[m] = currentString;
        }
    }
    bool fullTrans(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '?')
                return false;
        }
        return true;
    }
    WordList* word;
    Tokenizer token;
    Translator trans;
};

DecrypterImpl::DecrypterImpl()
:token(",;:.!()[]{}-\"#$%^& 0123456789")
{
    word = new WordList;
}

DecrypterImpl::~DecrypterImpl()
{
    delete word;
}

//load the contents of the indicated word list text file, to be used during the decrypting process
bool DecrypterImpl::load(string filename)
{
    if (word->loadWordList(filename))
        return true;
    return false;
}

//responsible for taking in an encrypted message and then finding all valid decryptions for this message, returning them in sorted order in the result vector
vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    vector<string> finalResults;
    //Tokenize the ciphertext
    vector<string> s = token.tokenize(ciphertext);
    
    //Find the word that has the most untranslated letters
    vector<string> sTrans;
    for (int i = 0; i < s.size(); i++)
        sTrans.push_back(trans.getTranslation(s[i]));
    int numMax = 0;
    int pos = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int num = 0;
        for (int k = 0; k < sTrans[i].length(); k++)
        {
            if (sTrans[i][k] == '?')
                num++;
        }
        if (numMax < num)
        {
            numMax = num;
            pos = i;
        }
    }
    string cipher = s[pos];
    string translatePart;
    translatePart = trans.getTranslation(cipher);
    
    //Using the English word list
    vector<string> possiblePlainWord = word->findCandidates(cipher, translatePart);

    //If cannot find matched candidates in wordist, return to previous call;
    if (possiblePlainWord.empty())
    {
        trans.popMapping();
        return vector<string>();
    }
    
    for (int i = 0; i < possiblePlainWord.size(); i++)
    {
        if (!trans.pushMapping(cipher, possiblePlainWord[i]))
            continue;
        else
        {
            vector<string> partTrans;
            bool fullyTransvValid = true;
            bool allTranslated = true;
            for (int i = 0; i < s.size(); i++)
            {
                string translated = trans.getTranslation(s[i]);
                partTrans.push_back (translated);
                if (fullTrans(translated))
                {
                    if (!word->contains(translated))
                        {
                            trans.popMapping();
                            fullyTransvValid = false;
                            break;
                        }
                }
                else
                {
                    allTranslated = false;
                }
            }
            //case in which all fully translated words are valid but the whole string is incomplete
            if (fullyTransvValid == true && allTranslated == false)
            {
                for (const auto& s : crack(ciphertext))
                {
                    finalResults.push_back(s);
                }
            }
            //case in which all fully translated words are valid but the whole string is fully translated
            //a valid solution is found
            else if (fullyTransvValid == true && allTranslated == true)
            {
                string validSolution = trans.getTranslation(ciphertext);
                finalResults.push_back(validSolution);
                trans.popMapping();
            }
            
        }
        
    }
    trans.popMapping();
    insertion_sort(finalResults);
    return finalResults;
}


//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
