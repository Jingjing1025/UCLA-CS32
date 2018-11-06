//
//  eval.cpp
//  Homework 2
//
//  Created by Jingjing on 03/02/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

void infixToPostfix (string infix, string& postfix, bool &syntax);
bool infixSyntaxValid (string postfix);
bool postfixEvaluation (string postfix, Map m, int& result);
int precedence(const char a);
bool isOperand(char a);
bool isOperator(char a);
bool operationResult(int operand1, int operand2, char operate, int& result);
bool mapContains (string infix, Map m);

int evaluate(string infix, const Map& values, string& postfix, int& result)   //Evaluate an integer arithmetic expression
{
    int a;
    if (infixSyntaxValid(infix))
    {
        bool syntax = true;
        infixToPostfix(infix, postfix, syntax);
        if (syntax == false)
            return 1;       //if infix syntax is not valid, return 1
        if (mapContains(infix, values))
        {
                if (!postfixEvaluation(postfix, values, a))    //if evaluation is trying to divide a number by 0, return 3
                    return 3;
                else        //if syntax is valid, Map contains all operands, and there's no dividing a number by 0, change result and return 0
                {
                    result = a;
                    return 0;
                }
        }
        else
            return 2;   //if syntax is valid but the Map does not contain the operands, return 2
            
    }
    return 1;   //if infix syntax is not valid, return 1
}


void infixToPostfix (string infix, string& postfix, bool& syntax)
{
    postfix = "";       //Initialize postfix to empty
    stack <char> operatorStack;    //Initialize the operator stack to empty
    for (int i = 0; i<infix.length(); i++)    //For each character ch in the infix string
    {
        switch (infix[i])
        {
            case ' ':
                break;
            case '(':
                operatorStack.push(infix[i]);
                break;
            case ')':
                if (i==0) syntax = false;           //syntax is false if ')' appears at the first place
                for (int k =i; k > 0; k--)          //syntax is false if "()..."
                {
                    if (isOperand(infix [k-1]))
                        break;
                    if (isOperator(infix[k-1]))
                    {
                        syntax = false;
                        break;
                    }
                    if (infix[k-1] != ' ' && infix[k-1] == '(')
                        syntax = false;
                }
                while (!operatorStack.empty() && operatorStack.top() != '(')   // pop stack until matching '('
                {
                    postfix.append(1, operatorStack.top());  //    append the stack top to postfix
                    operatorStack.pop();   // pop the stack
                }
                if (operatorStack.empty() || operatorStack.top()!='(')         //syntax is false if there is no matching '(' for each ')'
                    syntax = false;
                else
                    operatorStack.pop();    // remove the '('
                break;
            case '+':   //case operator
            case '-':
            case '*':
            case '/':
                if (i==0 || i==infix.length()-1)   //syntax is fals if operator appears on the first place or last place
                    syntax = false;
                for (int k =i; k > 0; k--)
                {
                    if (isOperand(infix [k-1]))
                        break;
                    if (infix[k-1] != ' ' && infix[k-1] != ')' && !isOperand(infix[k-1]))    //syntax is false if two operators are next to each other
                        syntax = false;
                }
                while (!operatorStack.empty() && operatorStack.top() != '(' && precedence(infix[i]) <= precedence(operatorStack.top()))
                    //    While the stack is not empty and the stack top is not '('
                    //    and precedence of ch <= precedence of stack top
                {
                    postfix.append(1,operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(infix[i]);
                break;
            default:
                postfix.append(1,infix[i]);
                break;
        }
    }
    while (!operatorStack.empty())
    {
        postfix.append(1,operatorStack.top());    // append the stack top to postfix
        operatorStack.pop();        // pop the stack
    }
}

bool postfixEvaluation (string postfix, Map m, int& result)
{
    stack <int> operandStack;
    int value, operand1, operand2;
    for (int i = 0; i<postfix.length(); i++)
    {
        if (isOperand(postfix[i]))  //is an operand
        {
            m.get(postfix[i], value);
            operandStack.push(value);
        }
        else                   //is a binary operator
        {
            operand2 = operandStack.top();   //set operand2 to the top of the operand stack
            operandStack.pop();
            operand1 = operandStack.top();   //set operand1 to the top of the operand stack
            operandStack.pop();
            if (!operationResult(operand1, operand2, postfix[i], result))
                return false;    //apply the operation that ch represents to operand1 and operand2
            operandStack.push(result);    //push the result onto the stack
        }
    }
    result = operandStack.top();
    return true;
}

bool infixSyntaxValid (string infix)
{
    int openBr = 0, closeBr = 0;
    bool result = true;
    if (infix.length()==0)
        return false;
    stack <int> operandStack;
    stack <char> operatorStack;
    
    for (int i = 0; i<infix.length(); i++)
    {
        if (isOperand(infix[i]))      //for operands
        {
            if (isupper(infix[i]))    //syntax is false if there exists capital letter
                result = false;
            else
                operandStack.push(infix[i]);
        }
        else if (isOperator(infix[i]))
            operatorStack.push(infix[i]);
        else if (infix[i] == '(')      //keep track of the numbers of open and close brackets in infix
            openBr ++;
        else if (infix[i] == ')')
            closeBr ++;
        else if  (infix[i] != ' ')     //syntax is false if there are meaningless characters
            result = false;
    }
    if (operandStack.size()!=operatorStack.size()+1 || openBr != closeBr)   //syntax is false if the numbers of open and close brackets don't match
        result = false;
    return result;
}

bool mapContains (string infix, Map m)   //return true if map contains all the operands
{
    bool result = true;
    for (int i = 0; i<infix.length(); i++)
    {
        if (isOperand(infix[i]) && !m.contains(infix[i]))
            result = false;
    }
    return result;
}

int precedence(const char a)    //'*' and '/' have higher precedence than '+' and '-'
{
    int result = 0;
    switch (a) {
        case '+':
        case '-':
            result = 1;
            break;
        case '*':
        case '/':
            result = 2;
            break;
    }
    return result;
}

bool isOperand(char a)      //return true if the char is an operand
{
    if (a>='a' && a<='z')
        return true;
    return false;
}

bool isOperator(char a)     //return true if the char is an operator
{
    if (a=='+' || a=='-' || a=='*' || a=='/')
        return true;
    return false;
}

bool operationResult(int operand1, int operand2, char operate, int& result)     //convert operation expressions into mathematic calculations
{
    if (operate == '+')
        result = operand1 + operand2;
    if (operate == '-')
        result = operand1 - operand2;
    if (operate == '*')
        result = operand1 * operand2;
    if (operate == '/')
    {
        if (operand2 == 0)
            return false;
        else
            result = operand1 / operand2;
    }
    return true;
}

