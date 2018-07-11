#include <stdio.h>
#include <stdlib.h>
#include "StackUtilization/linkedstack.h"

int checkBracketMatching(char *pSource)
{
    int i = 0, ret = 0;
    char symbol = '\0', checkSymbol = '\0';
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    pStack = createLinkedStack();
    if (pStack != NULL)
    {
        while (pSource[i] != 0)
        {
            symbol = pSource[i];
            switch (symbol)
            {
            case '(':
            case '{':
            case '[':
                push(pStack, symbol);
                break;
            case ')':
            case '}':
            case ']':
                pNode = pop(pStack);
                if (pNode == NULL)
                {
                    ret = 1; // 닫는 괄호와 짝이 맞지 않음
                }
                else
                {
                    checkSymbol = pNode->data;
                    if ((checkSymbol == '(' && symbol == ')') || (checkSymbol == '{' && symbol == '}') || (checkSymbol == '[' && symbol == ']'))
                    {
                        // 정상
                    }
                    else
                    {
                        ret = 2; // 괄호와 짝이 맞지 않음
                    }
                    free(pNode);
                }
                break;
            }
            i++;
        }

        if(ret == 0 && isLinkedStackEmpty(pStack) == 0)
    }
}