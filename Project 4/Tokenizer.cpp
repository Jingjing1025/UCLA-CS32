#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    string m_separators;
    vector<char> sep;
};

//initialize a new Tokenizer object and store all seperators
TokenizerImpl::TokenizerImpl(string separators)
{
    m_separators = separators;
    for (int i = 0; i < separators.length(); i++)
    {
        sep.push_back(separators[i]);
    }
}

//breaking the input string s into a set of non-empty token strings based on the separators provided in the constructor
vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    vector<string> str;
    string temp;

    for (int i = 0; i < s.length(); i++)
    {
        bool isSeparator = false;
        for (int k = 0; k < sep.size(); k++)
        {
            if (s[i] == sep[k])
            {
                isSeparator = true;
                break;
            }
        }
        if (!isSeparator)
        {
            temp += s[i];
            if (i == s.length()-1 && temp != "")
                str.push_back(temp);
        }
        else if (temp != "")
        {
            str.push_back(temp);
            temp = "";
        }
    }
    return str;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
