/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-01
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include "linked_list.h"
#include "str.h"
#include "memory.h"
#include <string.h>

List CreateList()
{
    List list = (struct Node *) g_malloc(sizeof(struct Node));
    list->next = NULL;
    return list;
}

bool IsLast(Position position, List list)
{
    return position->next == NULL;
}

bool IsEmptyList(List list)
{
    return list->next == NULL;
}

void InsertList(void *data, Position position, List list)
{
    Position TempCell;

    TempCell = g_malloc(sizeof(struct Node));
    TempCell->data = data;
    TempCell->next = position->next;
    position->next = TempCell;
}

void AppendList(void *data, const char *dataType, List list)
{
    PtrToNode tempCell = (struct Node *) g_malloc(sizeof(struct Node));
    Position CurrentPosition = list;
    while (CurrentPosition->next != NULL)
    {
        CurrentPosition = CurrentPosition->next;
    }

    tempCell->data = data;
    tempCell->data_type = str_copy(dataType);
    tempCell->next = CurrentPosition->next;
    CurrentPosition->next = tempCell;
}

void DisposeList(List list, void (*FreeDataCallBack)(PtrToNode pNode))
{
    List head = list;

    list = list->next; // 跳过list head;
    while (list != NULL)
    {
        PtrToNode tempNode = list;
        list = list->next;
        FreeDataCallBack(tempNode->data);
        g_free(&(tempNode->data_type));
        g_free(&tempNode);
    }

    g_free(&head);
}
