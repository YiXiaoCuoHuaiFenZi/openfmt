/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-03
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "memory.h"

Stack CreateStack()
{
    Stack stack = (struct Node *) g_malloc(sizeof(struct Node));
    stack->next = NULL;
    return stack;
}

bool IsEmptyStack(Stack stack)
{
    return stack->next == NULL;
}

void PopStack(Stack stack, void (*FreeDataCallBack)(PtrToNode pNode))
{
    if (IsEmptyStack(stack))
    {
        printf("%s", "Empty stack!");
    } else
    {
        PtrToNode firstCell = stack->next;
        stack->next = stack->next->next;
        FreeDataCallBack(firstCell->data);
        g_free(&firstCell);
    }
}

void PushStack(void *data, Stack stack)
{
    PtrToNode tempCell = (struct Node *) g_malloc(sizeof(struct Node));
    tempCell->data = data;
    tempCell->next = stack->next;
    stack->next = tempCell;
}

void *TopStack(Stack stack, void (*FreeDataCallBack)(PtrToNode pNode))
{
    if (!IsEmptyStack(stack))
    {
        return stack->next->data;
    }
    printf("%s", "Empty stack!");
    exit(-1);
}
