#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sequentialSearchNotSorted(int values[], int size, int key)
{
    int ret = -1;
    int i = 0;

    for (i = 0; i < size && values[i] != key; i++)
    {
        // data를 찾을때 까지 반복한 후 반복 종료
    }
    if (i < size)
    {
        ret = i;
    }
    return ret;
}

int sequentialSearchSorted(int values[], int size, int key)
{
    int ret = -1;
    int i = 0;

    for (i = 0; i < size && values[i] < key; i++)
    {
    }
    if (i < size && values[i] == key)
    {
        ret = i;
    }
    return ret;
}

void showArray(int values[], int size)
{
    int i = 0;

    printf("position, key\n");
    printf("-------------\n");
    for (i = 0; i < size; i++)
    {
        printf("%d,%d\n", i, values[i]);
    }
}

void showSearchResult(int key, int index)
{
    if (index >= 0)
    {
        printf("키-%d, 위치-%d\n", key, index);
    }
    else
    {
        printf("키-%d, 검색실패\n", key);
    }
}

int main(int argc, char *argv[])
{
    int index = 0, count = 0;
    int notSortedArray[] = {80, 20, 70, 50};
    int ascSortedArray[] = {20, 50, 70, 80};

    count = sizeof(notSortedArray) / sizeof(int);
    showArray(notSortedArray, count);
    index = sequentialSearchNotSorted(notSortedArray, count, 70);
    showSearchResult(70, index);
    index = sequentialSearchNotSorted(notSortedArray, 6, 25);
    showSearchResult(25, index);

    count = sizeof(notSortedArray) / sizeof(int);
    showArray(ascSortedArray, count);
    index = sequentialSearchSorted(ascSortedArray, count, 70);
    showSearchResult(70, index);
    index = sequentialSearchSorted(ascSortedArray, count, 25);
    showSearchResult(25, index);

    return 0;
}