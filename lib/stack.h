/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Generic stack definition and operate methods.
**    Created Date:    2022-10-03
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_STACK_H
#define OPENFMT_STACK_H

#include <stdbool.h>

struct StackNode;
typedef struct StackNode* PtrToStackNode;
typedef PtrToStackNode Stack;

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   generic stack ADT definition, the field data is used to store the pointer of any type of data,
**                     the field data_type is used to identify the data type, can be used to convert the generic data
**                     to correct data object.
**    Created Date:    2023-06-21
**    Updated Date:    2023-12-07
***********************************************************************************************************************/
struct StackNode
{
	void* data;
	char* data_type;
	struct StackNode* next;
};

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   create a stack ADT.
**    Parameters:      None.
**                     return: new created stack header pointer.
**    Created Date:    2023-06-21
**    Updated Date:    2023-12-07
***********************************************************************************************************************/
Stack create_stack();

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   dispose a stack.
**    Parameters:      stack: target stack to be disposed.
**                     free_data_callback: the free callback function of the stack data field.
**                     return: none.
**    Created Date:    2023-06-21
**    Updated Date:    2023-12-07
***********************************************************************************************************************/
void dispose_stack(Stack stack, void (* free_data_callback)(PtrToStackNode ptr_node));

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   check is a stack is empty or not.
**    Parameters:      stack: target stack to be checked.
**                     return: true: empty stack, false: empty stack with data node.
**    Created Date:    2023-06-21
**    Updated Date:    2023-12-07
***********************************************************************************************************************/
bool is_empty_stack(Stack stack);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   push a generic data to a stack, there is another parameter data_type to identify the data type,
**                     it will be used when convert the generic data to correct data object.
**    Parameters:      data: a data to be stored to the stack.
**                     data_type: the type of stored data, it will be used when convert the data to correct object.
**                     stack: target stack used to hold the data.
**                     return: none
**    Created Date:    2023-06-21
**    Updated Date:    2023-12-07
***********************************************************************************************************************/
void push_stack(void* data, char* data_type, Stack stack);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   get the first node of the stack.
**    Parameters:      stack: target stack.
**                     return: the stack node pointer of the top node.
**    Created Date:    2023-06-21
**    Updated Date:    2023-12-07
***********************************************************************************************************************/
PtrToStackNode top_stack(Stack stack);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   pop the first node of the stack, the data in the stack node is freed by the callback method
**                     free_data_callback.
**    Parameters:      stack: stack which .
**                     free_data_callback: the free callback function of the stack data field.
**                     return: none
**    Created Date:    2023-06-21
**    Updated Date:    2023-12-07
***********************************************************************************************************************/
void pop_stack(Stack stack, void (* free_data_callback)(PtrToStackNode ptr_node));

#endif //OPENFMT_STACK_H
