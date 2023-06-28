/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-04
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_DOUBLY_LINKED_LIST_H
#define OPENFMT_DOUBLY_LINKED_LIST_H

#include <stdbool.h>

struct Node;
typedef struct Node *DoublyLinkedList;
typedef struct Node *Position;

DoublyLinkedList create_doubly_linked_list();

bool init_doubly_linked_list(DoublyLinkedList list);

void empty_doubly_linked_list(DoublyLinkedList list);

bool is_empty_doubly_linked_list(DoublyLinkedList list);

bool is_last_doubly_linked_list(Position position, DoublyLinkedList list);

void insert_doubly_linked_list(void *data, Position position, DoublyLinkedList list);

void append_doubly_linked_list(void *data, DoublyLinkedList list);

void dispose_doubly_linked_list(DoublyLinkedList list, void (*free_data_callback)(void *data));

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
