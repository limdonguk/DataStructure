#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayListNodeType
{
    int data;
} ArrayListNode;

typedef struct ArrayListType
{
    int maxCount;     // 최대 크기
    int currentCount; // 현재 크기
    ArrayListNode *pData;
} ArrayList;

ArrayList createArrayList(int count)
{
    ArrayList *pReturn = NULL;
    if (count > 0)
    {
        pReturn = (ArrayList *)malloc(sizeof(ArrayList));
        if (pReturn != NULL)
        {
            if (pReturn->currentCount < pReturn->maxCount)
            {
                pReturn->maxCount = count;
                pReturn->currentCount = 0;
                pReturn->pData = NULL;
            }
            else
            {
                printf("인덱스 범위 초과");
            }
        }
        else
        {
            printf("비어있는 리스트");
        }
    }
    else
    {
        printf("최대 배열 크기는 0 이상");
    }

    pReturn->pData = (ArrayListNode *)malloc(sizeof(ArrayListNode) * count);
    if (pReturn->pData != NULL)
    {
        memset(pReturn->pData, 0, sizeof(ArrayListNode) * count);
    }
    else
    {
        printf("메모리 할당 실패");
        free(pReturn);
    }
}

int addArrayListData(ArrayList *pList, int position, int data)
{
    int i = 0;
    if (pList != NULL)
    {
        if (pList->currentCount < pList->maxCount)
        {
            if (position >= 0 && position <= pList->currentCount)
            {
                for (i = pList->currentCount - 1; i >= position; i--)
                {
                    pList->pData[i + 1] = pList->pData[i];
                }
                pList->pData[position].data = data;
                pList->currentCount++;
            }
            else
            {
                printf("위치 인덱스 범위 초과");
            }
        }
        else
        {
            printf("최대 크기 초과");
        }
    }
    else
    {
        printf("비어있는 List");
    }

    return 0;
}

int removeArrayListData(ArrayList *pList, int position)
{
    if (pList != NULL)
    {
        if (position >= 0 && position <= pList->currentCount)
        {
            for (int i = position; i < pList->currentCount - 1; i++)
            {
                pList->pData[i] = pList->pData[i + 1];
            }
            pList->currentCount--;
        }
    }
}

int getArrayListData(ArrayList *pList, int position)
{
    if (pList != NULL)
    {
        if (position >= 0 && position < pList->currentCount)
        {
            return pList->pData[position].data;
        }
    }
}

void deleteArrayList(ArrayList *pList)
{
    if (pList != NULL)
    {
        if (pList->pData != NULL)
        {
            free(pList->pData);
        }
        free(pList);
    }
}

int getArrayListLength(ArrayList *pList)
{
    if (pList != NULL)
    {
        return pList->currentCount;
    }
    return 0;
}
