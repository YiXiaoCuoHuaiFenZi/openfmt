/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-03
**    更新日期：    2022-10-03
***********************************************************************************************************************/
#ifndef OPENFMT_STACK_H
#define OPENFMT_STACK_H

#include <stdbool.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node
{
    void *data;
    struct Node *next;
};

Stack CreateStack();

void DisposeStack(Stack stack, void (*FreeDataCallBack)(PtrToNode pNode));

Stack EmptyStack(Stack stack);

bool IsEmptyStack(Stack stack);

void PushStack(void *data, Stack stack);

void *TopStack(Stack stack, void (*FreeDataCallBack)(PtrToNode pNode));

void PopStack(Stack stack, void (*FreeDataCallBack)(PtrToNode pNode));


#endif //OPENFMT_STACK_H
