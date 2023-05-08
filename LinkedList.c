#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE
{
    char szData[64];
    struct NODE* next;
}NODE;

NODE* g_head = NULL;

int IsEmpty()
{
    if (g_head->next == NULL)
        return 1;
    return 0;
}
void PrintList()
{
    while (g_head != NULL)
    {
        printf("[%p] %s, next[%p]\n", g_head, g_head->szData, g_head->next);

        g_head = g_head->next;
    }
}
int InsertAtHead(char* pszData)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));

    strcpy_s(pNode->szData, sizeof(pNode->szData), pszData); //pNode의 Data에 pszData를 넣어준다.

    if (IsEmpty())
        g_head = pNode;
    else {
        pNode->next = g_head;
        g_head = pNode;
    }

    return 1;
}

int InsertAtTail(char* pszData)
{
    NODE* pTmp = &g_head;
    while (pTmp->next != 0)
        pTmp = pTmp->next;

    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));

    strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

    pTmp->next = pNode;
}


NODE* FindData(char* pszData)
{
    NODE* pCur = g_head->next;
    NODE* pPrev = &g_head;
    while (pCur != NULL)
    {
        if (strcmp(pCur->szData, pszData) == 0)
            return pPrev;
        pCur = pCur->next;
        pPrev = pPrev->next;
    }

    return 0;
}

int DeleteData(char* pszData)
{
    NODE* pPrev = FindData(pszData);
    if (pPrev != 0)
    {
        NODE* pDelete = pPrev->next;
        pPrev->next = pDelete->next;

        printf("DeleteData(): %s\n", pDelete->szData);
        free(pDelete);
        return 1;
    }
}

void ReleaseList(void)
{
    printf("\nReleaseList()");
    NODE* pTmp = g_head->next;
    while (pTmp != NULL)
    {
        NODE* pDelete = pTmp;
        pTmp = pTmp->next;
        printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
        free(pDelete);
    }
    g_head->next = 0;
}

void PushData(char* pszData)
{
    InsertAtHead(pszData);
}

int PopData(NODE* pPopNode) {
    NODE* sp = g_head->next;
    if (IsEmpty())
        return 0;

    memcpy(pPopNode, sp, sizeof(NODE));

    g_head->next = sp->next;
    free(sp);

    return 1;
}

int EnQueue(char* pszData)
{
    return InsertAtTail(pszData);
}

int Dequeue(NODE* pGetNode)
{
    return PopData(pGetNode);
}

int main()
{
    EnQueue("TEST01");
    EnQueue("TEST02");
    EnQueue("TEST03");

    PrintList();

    NODE node = { 0 };
    Dequeue(&node);
    printf("Dequeq: %s\n", node.szData);
    PrintList();

    Dequeue(&node);
    printf("Dequeq: %s\n", node.szData);
    PrintList();

    Dequeue(&node);
    printf("Dequeq: %s\n", node.szData);
    PrintList();

    ReleaseList();

    return 0;
}