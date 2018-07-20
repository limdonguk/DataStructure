#include <stdio.h>
#include <stdlib.h>
#include "exprlinkedstack.h"

int inStackPrecedence(Precedence oper) {
    switch(oper){
        case lparen:
            return 0;
        case rparen:
            return 4;
        case multifly:
        case divide:
            return 2;
        case plus:
        case minus:
            return 1;
    }
    return -1;
}

int outStackPrecedence(Precedence oper) {
    switch(oper) {
        case lparen:
            return 5;
        case rparen:
            return 4;
        case multifly:
        case divide:
            return 2;
        case plus:
        case minus:
            return 1;
    }
    return -1;
}

void printToken(ExprToken element) {
    switch(element.type) {
        case lparen:
            printf("( ");
            break;
        case rparen:
            printf(") ");
            break;
        case plus:
            printf("+ ");
            break;
        case minus:
            printf("- ");
            break;
        case multifly:
            printf("* ");
            break;
        case divide:
            printf("/ ");
            break;
        case operand:
            printf("%4.1f ", element.value);
            break;
    }
}

void converInfixToPostfix(ExprToken *pExprTokens, int tokenCount) {
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    Precedence tokenType, inStackTokenType;
    int i=0;

    pStack = createLinkedStack();
    if(pStack != NULL) {
        for(i = 0; i < tokenCount; i++) {
            tokenType = pExprTokens[i].type;
            switch(tokenType) {
                case operand:
                    printf("%4.1f\t", pExprTokens[i].value);
                    break;
                case rparen:
                    pNode = popLS(pStack);
                    while(pNode != NULL && pNode->data.type != lparen) {
                        printToken(pNode->data);
                        free(pNode);

                        pNode = popLS(pStack);
                    } 
                    if(pNode != NULL) free(pNode);
                    break;
                default:
                    while(isLinkedStackEmpty(pStack) == 0) {
                        inStackTokenType = peekLS(pStack)->data.type;
                        if(outStackPrecedence(tokenType) <= inStackPrecedence(inStackTokenType)) {
                            pNode = popLS(pStack);
                            if(pNode != NULL) {
                                printToken(pNode->data);
                                free(pNode);
                            }
                        }
                        else {
                            break;
                        }
                    }
                    pushLS(pStack, pExprTokens[i]);
                    break;
            }
        }

        while(isLinkedStackEmpty(pStack) == 0) {
            pNode = popLS(pStack);
            if(pNode != NULL) {
                printToken(pNode->data);
                free(pNode);
            }
        }

        deleteLinkedStack(pStack);
    }
} 


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

    ExprToken *pExprTokens = (ExprToken *)malloc(sizeof(ExprToken)*9);
    pExprTokens[0].type = operand;
    pExprTokens[0].value = 2;
    pExprTokens[1].type = minus;
    pExprTokens[1].value = 0;
    pExprTokens[2].type = lparen;
    pExprTokens[2].value = 0;
    pExprTokens[3].type = operand;
    pExprTokens[3].value = 3;
    pExprTokens[4].type = plus;
    pExprTokens[4].value = 0;
    pExprTokens[5].type = operand;
    pExprTokens[5].value = 4;
    pExprTokens[6].type = rparen;
    pExprTokens[6].value = 0;
    pExprTokens[7].type = multifly;
    pExprTokens[7].value = 0;
    pExprTokens[8].type = operand;
    pExprTokens[8].value = 5;
    
    printf("Infix Expression : 2.0 - (3.0 + 4.0) * 5.0 \n");
    printf("Postfix Expression : \n");

    converInfixToPostfix(pExprTokens, 9);

    free(pExprTokens);

    return 0;

}