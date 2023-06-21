/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-04
**    更新日期：    2022-10-04
***********************************************************************************************************************/
#ifndef OPENFMT_DOUBLY_LINKED_LIST_H
#define OPENFMT_DOUBLY_LINKED_LIST_H

#include <stdbool.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode DoublyLinkedList;
typedef PtrToNode Position;

DoublyLinkedList CreateDoublyLinkedList();

bool InitDoublyLinkedList(DoublyLinkedList list);

void EmptyDoublyLinkedList(DoublyLinkedList list);

bool IsEmptyDoublyLinkedList(DoublyLinkedList list);

bool IsLastDoublyLinkedList(Position position, DoublyLinkedList list);

void InsertDoublyLinkedList(void *data, Position position, DoublyLinkedList list);

void AppendDoublyLinkedList(void *data, DoublyLinkedList list);

void DisposeDoublyLinkedList(DoublyLinkedList list, void (*FreeDataCallBack)(PtrToNode pNode));

struct Node
{
    /*
    ** 万能指针，以便存储任何类型的数据，实现泛型。
    */
    void *data;
    /*
    **  上一个节点的指针
    */
    struct Node *previous;
    /*
    **  下一个节点的指针
    */
    struct Node *next;
};
#endif //OPENFMT_DOUBLY_LINKED_LIST_H
