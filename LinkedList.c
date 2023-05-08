#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE
{
    char szData[64];
    struct NODE* next;
}NODE;

NODE* g_pHead = NULL;

void PrintList(void)
{
    NODE* pHead = g_pHead;

    while (pHead != NULL)
    {
        printf("[%p] %s, next[%p]\n", pHead, pHead->szData, pHead->next);
        pHead = pHead->next;
    }
    putchar('\n');
}

void ReleaseList(void)
{
    NODE* pTmp = g_pHead;
    while (pTmp != NULL)
    {
        NODE* pDelete = pTmp;
        pTmp = pTmp->next;
        printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
        free(pDelete);
    }
}

int FindData(char* pszData)
{
    NODE* pTmp = g_pHead;
    while (pTmp != NULL)
    {
        if (strcmp(pTmp->szData, pszData) == 0)
            return 1;
        pTmp = pTmp->next;
    }
}

int DeleteData(char* pszData)
{
    NODE* pTmp = g_pHead;
    NODE* pPrev = NULL;
    while (pTmp != NULL)
    {
        if (strcmp(pTmp->szData, pszData) == 0)
        {
            printf("DeleteData(): %s\n", pTmp->szData);
            if (pPrev != NULL)
                pPrev->next = pTmp->next;
            else {
                g_pHead = pTmp->next;
            }
            free(pTmp);
            return 1;
        }
        pPrev = pTmp;
        pTmp = pTmp->next;
    }
}

int InsertNewNode(char* pszData)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));

    strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

    if (g_pHead == NULL)
        g_pHead = pNode;
    else {
        pNode->next = g_pHead;
        g_pHead = pNode;
    }

    return 1;
}

int main()
{
    InsertNewNode("TEST01");
    PrintList();
    InsertNewNode("TEST02");
    PrintList();
    InsertNewNode("TEST03");
    PrintList();

    if (FindData("TEST01") == 1)
        printf("FindData(): Test01 found\n");

    if (FindData("TEST02") == 1)
        printf("FindData(): Test02 found\n");

    if (FindData("TEST03") == 1)
        printf("FindData(): Test03 found\n");

    DeleteData("Test01");
    DeleteData("Test02");
    DeleteData("Test03");

    ReleaseList();
    return 0;
}