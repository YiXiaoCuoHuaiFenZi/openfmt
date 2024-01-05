/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse Message, Enum, Service, Extend.
**    Created Date:    2022-11-14
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_OBJECT_PARSER_H
#define OPENFMT_OBJECT_PARSER_H

#include "../lib/stack.h"

void append_as_bottom_comments(PbCommentList* comments, PbCommentList* bottom_comments);

void append_bottom_comments(PtrToStackNode node, PbCommentList* bottom_comments);

List get_parent_elements(Stack object_stack);

#endif //OPENFMT_OBJECT_PARSER_H
