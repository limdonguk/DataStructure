#include <stdio.h>
#include <stdlib.h>
#include "exprlinkedstack.h"

void calcExpr(ExprToken *pExprTokens, int tokenCount) {
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode1 = NULL, *pNode2 = NULL;
    Precedence tokenType;
    int i=0;

    if(pExprTokens == NULL) { // 전달된 수식 배열이 NULL인지 아닌지 점검
        return;
    }

    pStack = createLinkedStack();
    if(pStack != NULL) { // 스택 생성 점검
        for(i = 0;i <tokenCount; i++) { // 토큰 배열의 크기만큼 반복문 실행
            tokenType = pExprTokens[i].type; 
            
            if(tokenType == operand) { // 피연산자를 만나면 토큰에 Push                
                pushLS(pStack, pExprTokens[i]);
            }                  
            else { // 연산자를 만났을 때의 처리
                pNode2 = popLS(pStack); // 피연산자 1개를 pop
                if(pNode2 != NULL) {
                    pNode1 = popLS(pStack); // 피연산자 1개를 pop
                    if(pNode1 != NULL ){
                        double op1 = pNode1->data.value; // op1에 pop한 데이터 저장
                        double op2 = pNode2->data.value; // op2에 pop한 데이터 저장

                        ExprToken newToken;
                        newToken.type = operand;
                        switch(tokenType) {
                            case plus:
                                newToken.value = op1 + op2;
                                break;
                            case minus:
                                newToken.value = op1 - op2;
                                break;
                            case multifly:
                                newToken.value = op1 * op2;
                                break;
                            case divide:
                                newToken.value = op1 / op2;
                                break;
                        }
                        pushLS(pStack, newToken); // 연산 결과를 다시 pStack에 Push
                        free(pNode1);
                    }
                    free(pNode2);
                }
            }
        }

        pNode1 = popLS(pStack); // 수식의 최종 처리 결과를 스택에서 Pop
        if(pNode1 != NULL) {
            printf("수식 계산 결과는 %f 입니다. \n", pNode1->data.value);
            free(pNode1);
        }
        else {
            printf("오류, 수식에 오류가 있습니다.\n");
        }
        deleteLinkedStack(pStack);
    }
}

int main(int argc, char* argv[]) {
    int i=0;

    ExprToken *pExprTokens = (ExprToken *)malloc(sizeof(ExprToken)*7);
    pExprTokens[0].type = operand;
    pExprTokens[0].value = 2;
    pExprTokens[1].type = operand;
    pExprTokens[1].value = 3;
    pExprTokens[2].type = operand;
    pExprTokens[2].value = 4;
    pExprTokens[3].type = plus;
    pExprTokens[3].value = 0;
    pExprTokens[4].type = operand;
    pExprTokens[4].value = 5;
    pExprTokens[5].type = multifly;
    pExprTokens[5].value = 0;
    pExprTokens[6].type = minus;
    pExprTokens[6].value = 0;

    printf("Expression : 2 3 4 + 5 * - \n");
    calcExpr(pExprTokens, 7);

    free(pExprTokens);

    return 0;

}