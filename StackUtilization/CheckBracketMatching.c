#include <stdio.h>
#include <stdlib.h>
#include "linkedstack.h"

int checkBracketMatching(char *pSource)
{
    int ret = 0, i = 0;
    char symbol = '\0', checkSymbol = '\0';
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    pStack = createLinkedStack();
    if (pStack != NULL)
    {
        while (pSource[i] != 0 && ret == 0)
        {
            symbol = pSource[i];
            switch (symbol)
            {
            case '(':
            case '[':
            case '{':
                pushLS(pStack, symbol);
                break;
            case ')':
            case ']':
            case '}':
                pNode = popLS(pStack);
                if (pNode == NULL)
                {
                    ret = 1;
                }
                else
                {
                    checkSymbol = pNode->data;
                    if ((symbol == ')' && checkSymbol == '(') || (symbol == '}' && checkSymbol == '{') || (symbol == ']' && checkSymbol == '['))
                    {
                    }
                    else
                    {
                        ret = 2;
                    }
                    free(pNode);
                }
                break;
            }
            i++;
        }

        if (ret == 0 && isLinkedStackEmpty(pStack) == 0)
        {
            ret = 3;
        }
        deleteLinkedStack(pStack);
    }
    return ret;
}

int main(int argc, char *argv[])
{
    int checkResult = 0, i = 0;
    char szExpressionStr[][50] = {
        "( A + B ) * C",
        "{ ( A + B ) * C } * D",
        "( A + B ) * C )",
        "( ( A + B ) * C",
        "{ ( A + B } ) * C * D"};

    for (i = 0; i < sizeof(szExpressionStr) / sizeof(szExpressionStr[0]); i++)
    {
        checkResult = checkBracketMatching(szExpressionStr[i]);
        if (checkResult == 0)
        {
            printf("SUCCESS, %s\n", szExpressionStr[i]);
        }
        else
        {
            printf("FAIL-[%d], %s\n", checkResult, szExpressionStr[i]);
        }
    }

    return 0;
}