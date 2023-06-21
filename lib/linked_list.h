/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-01
**    更新日期：    2022-10-01
***********************************************************************************************************************/
#ifndef OPENFMT_LINKED_LIST_H
#define OPENFMT_LINKED_LIST_H

#include <stdbool.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List CreateList();

bool InitList(List list);

List EmptyList(List list);

bool IsEmptyList(List list);

bool IsLastList(Position position, List list);

void InsertList(void *data, Position position, List list);

void AppendList(void *data, const char *dataType, List list);

void DisposeList(List list, void (*FreeDataCallBack)(PtrToNode pNode));

struct Node
{
    /*
    ** 万能指针，以便存储任何类型的数据，实现泛型。
    */
    void *data;
    /*
    ** data的类型名，可依据对应的类型对data进行转换。
    */
    char *data_type;
    /*
    **  下一个节点的指针
    */
    struct Node *next;
};
#endif //OPENFMT_LINKED_LIST_H
