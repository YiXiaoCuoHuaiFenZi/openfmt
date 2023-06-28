/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-01
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_LINKED_LIST_H
#define OPENFMT_LINKED_LIST_H

#include <stdbool.h>

struct Node;
typedef struct Node *PtrToNode;
typedef struct Node *List;
typedef struct Node *Position;

List create_linked_list();

bool init_linked_list(List list);

List empty_linked_list(List list);

bool is_empty_linked_list(List list);

bool is_linked_list_last(Position position, List list);

void insert_linked_list(void *data, Position position, List list);

void append_linked_list(void *data, const char *data_type, List list);

void dispose_linked_list(List list, void (*free_data_callback)(void *data));

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
