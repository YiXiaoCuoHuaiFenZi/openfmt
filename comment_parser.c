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

GCharList* pickup_comments(SQueue line_queue)
{
	GCharList* comments = create_list(GCharNode);

	bool isComment = false;
	while (!is_empty_str_queue(line_queue))
	{
		char* data = str_queue_front(line_queue);
		char* line = str_copy((char*)data);
		char* trimmedSpaceLine = trim(line);

		if (!isComment && !starts_with("/*", trimmedSpaceLine)
			&& !starts_with("*", trimmedSpaceLine)
			&& !starts_with("//", trimmedSpaceLine)
			&& (strcmp("\n", line) != 0))
		{
			g_free(&line);
			g_free(&trimmedSpaceLine);
			break;
		}
		else
		{
			de_str_queue(line_queue);
		}

		// comment case: /* I'am a comment */
		if (starts_with("/*", trimmedSpaceLine) && ends_with("*/", trimmedSpaceLine))
		{
			char* trimmedLine1 = trim_prefix(trimmedSpaceLine, "/*");
			char* trimmedLine2 = trim_suffix(trimmedLine1, "*/");
			char* trimmedLine3 = trim(trimmedLine2);
			if (strlen(trimmedLine3) != 0)
			{
				append_list(GCharNode, comments, trimmedLine3);
				de_str_queue(line_queue);
			}
			else
			{
				g_free(&trimmedLine3);
			}

			g_free(&line);
			g_free(&trimmedSpaceLine);
			g_free(&trimmedLine1);
			g_free(&trimmedLine2);
			continue;
		}

		// comment case: // I'am a comment
		if (starts_with("//", trimmedSpaceLine))
		{
			char* trimmedLine1 = trim_prefix(trimmedSpaceLine, "//");
			char* trimmedLine2 = trim(trimmedLine1);
			if (strlen(trimmedLine2) != 0)
			{
				append_list(GCharNode, comments, trimmedLine2);
			}
			else
			{
				g_free(&trimmedLine2);
			}

			g_free(&line);
			g_free(&trimmedSpaceLine);
			g_free(&trimmedLine1);
			continue;
		}

		if (starts_with("/*", trimmedSpaceLine))
		{
			// comment case: /* I'am a comment
			char* trimmedLine1 = trim_prefix(trimmedSpaceLine, "/*");
			char* trimmedLine2 = trim(trimmedLine1);
			if (strlen(trimmedLine2) != 0)
			{
				append_list(GCharNode, comments, trimmedLine2);
			}
			else
			{
				g_free(&trimmedLine2);
			}

			g_free(&line);
			g_free(&trimmedSpaceLine);
			g_free(&trimmedLine1);
			isComment = true;
			continue;
		}

		if (ends_with("*/", trimmedSpaceLine))
		{
			// comment case: I'am a comment */
			char* trimmedLine1 = trim_suffix(trimmedSpaceLine, "*/");
			char* trimmedLine2 = trim(trimmedLine1);
			if (strlen(trimmedLine2) != 0)
			{
				append_list(GCharNode, comments, trimmedLine2);
			}
			else
			{
				g_free(&trimmedLine2);
			}

			g_free(&line);
			g_free(&trimmedSpaceLine);
			g_free(&trimmedLine1);
			isComment = false;
			continue;
		}

		if (isComment)
		{
			char* line_trim_prefix = trim_prefix(trimmedSpaceLine, "**");
			char* line_trim_space = trim(line_trim_prefix);
			append_list(GCharNode, comments, line_trim_space);
			g_free(&line_trim_prefix);
		}
		g_free(&line);
		g_free(&trimmedSpaceLine);
	}

	return comments;
}

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

PbComment* parse_comment(char* line)
{
	char* s1 = trim(line);
	char* s2 = strstr(s1, "//");
	if (s2)
	{
		char* s3 = trim_prefix(s2, "//");
		char* s4 = trim(s3);
		PbComment* pb_comment = (PbComment*)g_malloc(sizeof(PbComment));
		pb_comment->text = s4;
		pb_comment->pos = RIGHT;
		g_free(&s3);
		return pb_comment;
	}
	g_free(&s1);
	return NULL;
}
