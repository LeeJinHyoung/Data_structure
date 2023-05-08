#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct USERDATA
{
	char szName[64];
	char szPhone[64];
}USERDATA;


typedef struct NODE
{	
	USERDATA* pData;

	struct NODE* prev;
	struct NODE* next;
}NODE;

NODE* g_pHead;
NODE* g_pTail;
int g_nSize;

void InitList()
{
	//더미헤드 테일
	g_pHead = (NODE*)malloc(sizeof(NODE));
	g_pTail = (NODE*)malloc(sizeof(NODE));
	g_nSize = 0;

	memset(g_pHead, 0, sizeof(NODE));
	memset(g_pTail, 0, sizeof(NODE));

	/*strcpy_s(g_pHead->szData, sizeof(g_pHead->szData), "DUMMY HEAD");
	strcpy_s(g_pTail->szData, sizeof(g_pTail->szData), "DUMMY Tail");*/

	g_pHead->next = g_pTail;
	g_pTail->prev = g_pHead;

}

void PrintList()
{
	int i = 0;
	printf("g_sSize: %d,g_pHead [%p], g_Tail[%p]\n", g_nSize, g_pHead, g_pTail);
	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
	{
		if (pTmp == g_pHead || pTmp == g_pTail)
			printf("[%p],DUMMY[%p]\n", pTmp->prev,
				 pTmp->next);
		else
		{
			printf("Index: %d [%p] %s, %s [%p]\n", i, pTmp->prev, pTmp->pData->szName,pTmp->pData->szPhone, pTmp->next);
			++i;
		}
		pTmp = pTmp->next;
	}
}
//pParam 호출자가 메모리를 동적 할당 + 값 설정까지 해서 전달
int InsertAtHead(USERDATA* pParam)
{
	NODE* pNewNODE = (NODE*)malloc(sizeof(NODE));
	memset(pNewNODE, 0, sizeof(NODE));

	pNewNODE->pData = pParam;
	//strcpy_s(pNewNODE->szData, sizeof(pNewNODE->szData), pszData);

	pNewNODE->next = g_pHead->next;
	pNewNODE->prev = g_pHead;

	g_pHead->next = pNewNODE;
	pNewNODE->next->prev = pNewNODE;

	g_nSize++;
	return g_nSize;
}

int InsertAtTail(USERDATA* pParam)
{
	InsertBefore(g_pTail, pParam);
	/*NODE* pNewNODE = (NODE*)malloc(sizeof(NODE));
	memset(pNewNODE, 0, sizeof(NODE));
	strcpy_s(pNewNODE->szData, sizeof(pNewNODE->szData), pszData);


	pNewNODE->next = g_pTail;
	pNewNODE->prev = g_pTail->prev;

	g_pTail->prev = pNewNODE;
	pNewNODE->prev->next = pNewNODE;

	g_nSize++;*/
	return g_nSize;
}

int InsertBefore(NODE* pDstNode, USERDATA* pParam)
{
	NODE* pPrev = pDstNode->prev;

	NODE* pNewNODE = (NODE*)malloc(sizeof(NODE));
	memset(pNewNODE, 0, sizeof(NODE));
	//strcpy_s(pNewNODE->szData, sizeof(pNewNODE->szData), pszData);

	pNewNODE->pData = pParam;

	pNewNODE->next = pDstNode->prev;
	pNewNODE->prev = pDstNode;

	pDstNode->prev = pNewNODE;
	pNewNODE->prev->next = pNewNODE;

	g_nSize++;

}
int InsertAt(int index, USERDATA* pParam)
{
	int i = 0;
	NODE* pTmp = g_pHead->next;
	while (pTmp != g_pTail)
	{
		if (i == index)
		{
			InsertBefore(pTmp, pParam);
			return i;
		}
		pTmp = pTmp->next;
		++i;
	}
	InsertAtTail(pParam);
	return 1;
}

NODE* GetAt(int index)
{
	int i = 0;
	NODE* pTmp = g_pHead->next;
	while (pTmp != g_pTail)
	{
		if (i == index)
			return pTmp;
		pTmp - pTmp->next;
		++i;
	}
	return NULL;
	
}


NODE* FindNode(const char* pszName)
{
	NODE* pTmp = g_pHead->next;
	while (pTmp != g_pTail)
	{
		if (strcmp(pTmp->pData->szName, pszName) == 0)
			return pTmp;
		pTmp = pTmp->next;
	}
	return NULL;
}

int DeleteNode(const char* pszName)
{
	NODE* pNode = FindNode(pszName);

	pNode->prev->next = pNode->next;

	pNode->next->prev = pNode->prev;

	free(pNode->pData);
	free(pNode);

	printf("DeleteNode(): %p\n", pNode);

	g_nSize--;

	return 0;
}
void ReleaseList()
{
	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
	{
		NODE* pDelete = pTmp;
		pTmp = pTmp->next;

		printf("free(%p)\n", pDelete);
		free(pDelete->pData);
		free(pDelete);
	}
	g_pHead = NULL;
	g_pTail = NULL;
	g_nSize = 0;
	puts("ReleaseList()");
}

//스택용 함수.
//void PushData(char* pszData)
//{
//	InsertAtHead(pszData);
//}
//
//int PopData(NODE* popNode)
//{
//	NODE* sp = g_pHead->next;
//
//	memcpy(popNode, sp, sizeof(NODE));
//	g_pHead->next= sp->next;
//
//	free(sp);
//
//	return 0;
//}

int GetSize()
{
	return g_nSize;
}
int GetLength()
{
	return GetSize();
}

int IsEmpty()
{

	return GetSize();
}

int main(void)
{
	InitList();

	USERDATA* pNewData = (USERDATA*)malloc(sizeof(USERDATA));
	memset(pNewData, 0, sizeof(USERDATA));
	strcpy_s(pNewData->szName, sizeof(pNewData->szName), "LJH");
	strcpy_s(pNewData->szPhone, sizeof(pNewData->szPhone), "010");
	InsertAtTail(pNewData);
	


	PrintList();
	ReleaseList();
	return 0;
}