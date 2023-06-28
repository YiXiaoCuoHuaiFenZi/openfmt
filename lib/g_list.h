/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Generic list implementations using macros.
**    创建日期：    2022-10-26
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_G_LIST_H
#define OPENFMT_G_LIST_H

#include <stdlib.h>
#include <stdio.h>

#define G_NodeTemplate(Type) struct G ##Type ##Node{ Type *data; struct G ##Type ##Node *next; }
typedef G_NodeTemplate(int) GIntNode, GIntList;
typedef G_NodeTemplate(float) GFloatNode, GFloatList;
typedef G_NodeTemplate(char) GCharNode, GCharList;

typedef unsigned long UnsignedLong;
typedef G_NodeTemplate(UnsignedLong) GUnsignedLongNode, GUnsignedLongList;

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    The generic macro method of creating type specified list.
**    创建日期：    2022-10-26
**    更新日期：    2022-10-26
***********************************************************************************************************************/
#define create_list(type) ({                                                   \
    type *head = (type *) malloc(sizeof(type));                                \
    if (head == NULL)                                                          \
    {                                                                          \
        printf("%s", "Out of space!");                                         \
        exit(-1);                                                              \
    }                                                                          \
    head->data = NULL;                                                         \
    head->next = NULL;                                                         \
    head;                                                                      \
 })

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    The generic macro method of appending element to the list.
**    创建日期：    2022-10-26
**    更新日期：    2022-10-26
***********************************************************************************************************************/
#define append_list(type, inst, element) ({                                    \
    type *temp_node  = (type *) malloc(sizeof(type));                          \
    if (temp_node == NULL)                                                     \
    {                                                                          \
        printf("%s", "Out of space!");                                         \
        exit(-1);                                                              \
    }                                                                          \
                                                                               \
    type *cur = inst;                                                          \
    while (cur->next != NULL)                                                  \
    {                                                                          \
        cur = cur->next;                                                       \
    }                                                                          \
                                                                               \
    temp_node->data = element;                                                 \
    temp_node->next = cur->next;                                               \
    cur->next = temp_node;                                                     \
 })

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Check if list is empty.
**    创建日期：    2022-10-26
**    更新日期：    2022-10-26
***********************************************************************************************************************/
#define is_empty_list(inst) ({                                                 \
    inst->next == NULL;                                                        \
 })

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Dispose list.
**    创建日期：    2022-10-26
**    更新日期：    2022-10-26
***********************************************************************************************************************/
#define dispose_list(type, inst, data_free_func) ({                            \
    if (is_empty_list(inst))                                                   \
    {                                                                          \
        free(inst);                                                            \
        inst = NULL;                                                           \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        type *head = inst;                                                     \
        type *cur = head->next;                                                \
        while (cur != NULL)                                                    \
        {                                                                      \
            type *temp_node = cur;                                             \
            cur = cur->next;                                                   \
            data_free_func(temp_node);                                         \
            free(temp_node);                                                   \
        }                                                                      \
        head->next = NULL;                                                     \
        free(inst);                                                            \
        inst = NULL;                                                           \
    }                                                                          \
})


#endif //OPENFMT_G_LIST_H
