/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Pick up comments.
**    创建日期：    2022-10-03
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "comment_parser.h"
#include "lib/str.h"
#include "proto.h"
#include "lib/memory.h"

PbCommentList* make_comments(GCharList* commentLines, PbPosition position)
{
	PbCommentList* top_comments = create_list(PbCommentList);
	GCharNode* ptr_node = commentLines->next;   // jump over the head node
	while (ptr_node)
	{
		PbComment* pb_comment = (PbComment*)g_malloc(sizeof(PbComment));
		pb_comment->text = str_copy((char*)ptr_node->data);
		pb_comment->pos = position;
		ptr_node = ptr_node->next;
		append_list(PbCommentNode, top_comments, pb_comment);
	}
	return top_comments;
}

void free_PbComment(PbCommentNode* ptr)
{
	PbComment* pb_comment = (PbComment*)ptr->data;
	g_free(&pb_comment->text);
	g_free(&pb_comment);
}

void free_GChar(GCharNode* ptr)
{
	char* t = ptr->data;
	g_free(&t);
}
