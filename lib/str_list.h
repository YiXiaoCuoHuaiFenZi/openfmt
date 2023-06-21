/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-22
**    更新日期：    2022-10-22
***********************************************************************************************************************/
#ifndef OPENFMT_STR_LIST_H
#define OPENFMT_STR_LIST_H

#include <stdbool.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode SList;
typedef PtrToNode Position;

SList CreateStrList();

bool InitStrList(SList list);

SList EmptyStrList(SList list);

bool IsEmptyStrList(SList list);

bool IsLastStrList(Position position, SList list);

void InsertStrList(char *str, Position position, SList list);

void AppendStrList(char *str, SList list);

void DisposeStrList(SList list);

struct Node
{
    /*
    ** 指向字符串的指针。
    */
    char *str;
    /*
    **  下一个节点的指针
    */
    struct Node *next;
};
#endif //OPENFMT_STR_LIST_H
