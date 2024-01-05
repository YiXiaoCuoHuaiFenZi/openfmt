/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse Message, Enum, Service, Extend.
**    Created Date:    2022-11-14
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "package_parser.h"
#include "import_parser.h"
#include "message_parser.h"
#include "object_parser.h"
#include "../lib/memory.h"

void append_as_bottom_comments(PbCommentList* comments, PbCommentList* bottom_comments)
{
	PbCommentNode* curr = bottom_comments->next;
	while (curr)
	{
		PbComment* pb_comment = curr->data;
		pb_comment->pos = BOTTOM;
		/*
		** create a total new comment data, and append it to the target comments list, so we can release bottom_comments
		** by calling dispose_linked_list.
		*/
		PbComment* new_comment = (PbComment*)malloc(sizeof(PbComment));
		memcpy(new_comment, pb_comment, sizeof(PbComment));
		new_comment->text = str_copy(pb_comment->text);
		// append the new comment data to the comments list.
		append_list(PbCommentNode, comments, new_comment);
		curr = curr->next;
	}
}

void append_bottom_comments(PtrToStackNode node, PbCommentList* bottom_comments)
{
	if (strcmp(node->data_type, "PbMessage") == 0)
	{
		PbMessage* current_obj = (PbMessage*)(node->data);
		append_as_bottom_comments(current_obj->comments, bottom_comments);
		return;
	}
	if (strcmp(node->data_type, "PbEnum") == 0)
	{
		PbEnum* current_obj = (PbEnum*)(node->data);
		append_as_bottom_comments(current_obj->comments, bottom_comments);
		return;
	}
	if (strcmp(node->data_type, "PbOneOf") == 0)
	{
		PbOneOf* current_obj = (PbOneOf*)(node->data);
		append_as_bottom_comments(current_obj->comments, bottom_comments);
		return;
	}
	if (strcmp(node->data_type, "PbExtend") == 0)
	{
		PbExtend* current_obj = (PbExtend*)(node->data);
		append_as_bottom_comments(current_obj->comments, bottom_comments);
		return;
	}
}

List get_parent_elements(Stack object_stack)
{
	PtrToStackNode node = (PtrToStackNode)top_stack(object_stack);

	if (strcmp(node->data_type, "PbMessage") == 0)
	{
		PbMessage* parent = (PbMessage*)(node->data);
		return parent->elements;
	}
	if (strcmp(node->data_type, "PbEnum") == 0)
	{
		PbEnum* parent = (PbEnum*)(node->data);
		return parent->elements;
	}
	if (strcmp(node->data_type, "PbOneOf") == 0)
	{
		PbOneOf* parent = (PbOneOf*)(node->data);
		return parent->elements;
	}
	if (strcmp(node->data_type, "PbExtend") == 0)
	{
		PbExtend* parent = (PbExtend*)(node->data);
		return parent->elements;
	}

	return NULL;
}