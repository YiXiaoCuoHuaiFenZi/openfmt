/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-22
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include <string.h>
#include "str_list.h"
#include "memory.h"

SList CreateStrList()
{
    SList list = (struct Node *) g_malloc(sizeof(struct Node));
    list->next = NULL;
    return list;
}

bool IsLastStrList(Position position, SList list)
{
    return position->next == NULL;
}

bool IsEmptyStrList(SList list)
{
    return list->next == NULL;
}

void InsertStrList(char *str, Position position, SList list)
{
    Position tempCell = g_malloc(sizeof(struct Node));
    tempCell->str = str;
    tempCell->next = position->next;
    position->next = tempCell;
}

void AppendStrList(char *str, SList list)
{
    PtrToNode tempCell = (struct Node *) g_malloc(sizeof(struct Node));
    Position CurrentPosition = list;
    while (CurrentPosition->next != NULL)
    {
        CurrentPosition = CurrentPosition->next;
    }

    tempCell->str = str;
    tempCell->next = CurrentPosition->next;
    CurrentPosition->next = tempCell;
}

void DisposeStrList(SList list)
{
    list = list->next; // 跳过list head;
    if (IsEmptyStrList(list))
    {
        return;
    }

    PtrToNode tempNode;
    while (list != NULL)
    {
        tempNode = list;
        list = list->next;
        g_free(&(tempNode->str));
        g_free(&tempNode);
    }
}
