#include <iostream>
using namespace std;

#include "calc.h"
#include <cstring>


Calc::Calc(char* argvIn)
{
    // dynamically allocate private variables
    stk = new Stack();
    inFix = new char[strlen(argvIn) + 1];

    // copy command line argument into inFix
    strcpy(inFix, argvIn);
    
    // check expression for validity, otherwise quit program
    if (CheckTokens() && CheckParens())
    {
        MakeValueTbl();
        Parse();
    }
    else
    {
        cout << "ERROR: INVALID INPUT" << endl;
        exit(EXIT_FAILURE);
    }
}

Calc::~Calc()
{
    delete inFix;
    delete valueTbl;

    // delete extra nodes in stack if expression is unbalanced
    while (stk->GetLength() > 0)
        stk->Pop();
    delete stk;
}

bool Calc::CheckTokens()
{
    // counter variables to compare if each inFix char is valid
    int count = 0;
    int arrLen = 0;

    char checkElement[42] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                            'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                            'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            '(', ')', '+', '-', '*', '/'};
    
    // for loop checks each inFix element with checkElement array
    for (int i = 0; inFix[i] != '\0'; i++)
    {
        for (int j = 0; j < 42; j++)
        {
            if (inFix[i] == checkElement[j])
                count++;
        }
        arrLen++;
    }

    // if check is equal to the length, all chars valid
    if (count == arrLen)
        return true;
    else
        return false;  
}

void Calc::MakeValueTbl()
{
    // dynamically allocate valueTbl and put zeroes in
    valueTbl = new int[26];
    for (int i = 0; i < 26; i++)
        valueTbl[i] = 0;

    // set index to 0
    valueIdx = 0;
}

void Calc::Parse()
{
    // create expression with alphabet variables
    string parseExp = "";
    int curIdx = 0;

    // for loop checks for digits to convert to alphabet
    for (int i = 0; inFix[i] != '\0'; i++)
    {
        // if current index is a digit, change to letter
        if (isdigit(inFix[curIdx]))
        {
            // accumulate digit string
            string valueStr = "";

            // use last index to fill digit string
            int lastIdx = FindLast(curIdx);
            for (int j = curIdx; j <= lastIdx; j++)
                valueStr += inFix[j];

            // convert digit string to int, add letter from valueIdx
            valueTbl[valueIdx] = stoi(valueStr);
            parseExp += valueIdx + 65;
            valueIdx++;

            curIdx = lastIdx + 1;
        }
        else
        {
            // add other characters to alphabet expression
            parseExp += inFix[curIdx];
            curIdx++;
        }
    }

    // reset inFix to hold the alphabet expression
    inFix = new char[parseExp.length()];
    for (int k = 0; k < parseExp.length(); k++)
        inFix[k] = parseExp[k];
}

int Calc::FindLast(int cur)
{
    int lastIdx = cur;

    // check chars after current index; if digit, increment last index
    for (int i = 1; isdigit(inFix[cur + i]); i++)
        lastIdx++;

    return lastIdx;
}

bool Calc::CheckParens()
{
    // variables to peruse while loop
    bool bal = true;
    int i = 0;

    // while loop continues until expression is unbalanced
    // or expression rerachs end
    while (bal && inFix[i] != '\0')
    {
        // check current char for type and use stack to determine balance
        char ch = inFix[i];

        if (ch == '(')
            stk->Push('(');
    
        if (ch == ')')
        {
            if (!stk->IsEmpty())
                stk->Pop();
            else
                bal = false;
        }
        i++;
    }

    // based on while loop results, return true or false
    if (bal && stk->IsEmpty())
        return true;
    else
        return false;
}

void Calc::DisplayInFix()
{
    // print out character by character inFix
    for (int i = 0; inFix[i] != '\0'; i++)
        cout << inFix[i];
    cout << endl;
}