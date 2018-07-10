#include <stdio.h>
#include <stdlib.h>
#include "linkedstack.h"

char* reverseString(char *pSource) {
    char* pReturn = NULL;
    int i = 0, stackSize = 0;
    LinkedStack *pStack;
    LinkedStackNode *pNode = NULL;

    pStack = createLinkedStack();                                // 입력받은 문자를 push할 스택 생성 
    if(pStack != NULL) {
        while(pSource[stackSize] != '0') {                       // 입력받은 문자열의 끝까지 반복
            pushLS(pStack, pSource[stackSize]);                  // 문자열을 하나씩 생성한 스택에 push
            stackSize++;                                         // 입력받은 문자의 개수를 1씩 증가
        }

        pReturn = (char *)malloc(sizeof(char)*(stackSize+1));      
        memset(pReturn, 0, sizeof(char)*(stackSize+1));
        while(i < stackSize) {                                   // 입력받은 수만큼 반복
            pNode = popLS(pStack);                               // 입력받은 문자열을 push한 스택에서 하나씩 pop
            if(pNode != NULL) {                                  
                pReturn[i] = pNode->data;                        // pReturn[0] = pNode->data(스택의 top) 역순저장
                free(pNode);
            }
            i++;
        }
        deleteLinkedStack(pStack);
    }

    return pReturn;
}

 int main(int argc, char* argv[]) {
     char szSource[] = "ABCD";
     char pszReverse = reverseStrung(szSource);
     if(pszReverse != NULL) {
         printf("[%s] => [%s]\n", szSource, pszReverse);
         free(pszReverse);
     }
     return 0;
 }