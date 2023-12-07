/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Pick up comments.
**    创建日期：    2022-10-03
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "comment_parser.h"
#include "../lib/str.h"
#include "proto.h"
#include "../lib/memory.h"

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
	g_free(to_void_ptr(&pb_comment->text));
	g_free(to_void_ptr(&pb_comment));
}

void free_GChar(GCharNode* ptr)
{
	char* t = ptr->data;
	g_free(to_void_ptr(&t));
}

char* clean_comment_str(const char* comment)
{
	char* trimmed_comment = trim(comment);

	if (starts_with("**", trimmed_comment))
	{
		char* s_1 = trim_prefix(trimmed_comment, "**");
		char* s_2 = trim(s_1);
		g_free(to_void_ptr(&s_1));
		g_free(to_void_ptr(&trimmed_comment));
		return s_2;
	}

	bool is_line_comment = starts_with("//", trimmed_comment);
	if (is_line_comment)
	{
		char* s_1 = trim_prefix(trimmed_comment, "//");
		char* s_2 = trim(s_1);
		g_free(to_void_ptr(&s_1));
		g_free(to_void_ptr(&trimmed_comment));
		return s_2;
	}

	bool is_block_comment = starts_with("/*", trimmed_comment) && ends_with("*/", trimmed_comment);
	if (is_block_comment)
	{
		char* s_1 = trim_prefix(trimmed_comment, "/*");
		char* s_2 = trim_suffix(s_1, "*/");
		char* s_3 = trim(s_2);
		g_free(to_void_ptr(&s_1));
		g_free(to_void_ptr(&s_2));
		g_free(to_void_ptr(&trimmed_comment));
		return s_3;
	}

	return trimmed_comment;
}

PbComment* pick_up_single_line_comment(const char* proto_str, unsigned long* index)
{
	char* s = pick_str_until(proto_str, index, '\n', true);
	unsigned long* index_ptr = NULL;
	unsigned long tmp_index = 0;
	index_ptr = &tmp_index;
	char* line_comment = pick_up_comment_str(s, index_ptr);
	if (line_comment != NULL)
	{
		char* line_comment_processed = clean_comment_str(line_comment);
		g_free(to_void_ptr(&line_comment));
		PbComment* pb_comment = (PbComment*)g_malloc(sizeof(PbComment));
		pb_comment->text = line_comment_processed;
		pb_comment->pos = RIGHT;

		*index = *index + strlen(s);
		return pb_comment;
	}

	return NULL;
}

char* pick_up_comment_str(const char* proto_str, unsigned long* index)
{
	char* comment_str = NULL;
	char* tokens[] = { "//", "/*", "*/" };
	unsigned long target_str_start_index = 0;
	unsigned long target_str_end_index = 0;
	Status status = start;
	unsigned long str_len = strlen(proto_str);
	while (*index <= str_len)
	{
		if (str_len - *index > 2)
		{
			if (tokens[0][0] == proto_str[*index] &&
				tokens[0][1] == proto_str[*index + 1])
			{
				// example single line comment: // The price sdfgfhg API request message //asd /*asdfghj*/ AS
				if (status != block_comment_start && status != line_comment)
				{
					target_str_start_index = *index;
					*index = *index + 2;
					status = line_comment;
				}
			}
			else if (tokens[1][0] == proto_str[*index] &&
					 tokens[1][1] == proto_str[*index + 1])
			{
				if (status != line_comment)
				{
					target_str_start_index = *index;
					*index = *index + 2;
					status = block_comment_start;
				}
			}
			else if (tokens[2][0] == proto_str[*index] &&
					 tokens[2][1] == proto_str[*index + 1])
			{
				if (status == block_comment_start)
				{
					target_str_end_index = *index + 1;
					unsigned long len = target_str_end_index - target_str_start_index + 1;
					comment_str = (char*)malloc(len + 1);
					strncpy(comment_str, proto_str + target_str_start_index, len);
					comment_str[len] = '\0';
					*index = *index + 2;
					return comment_str;
				}
			}
		}
		char c = proto_str[*index];
		if (is_new_line(c))
		{
			switch (status)
			{
			case start:
				status = start;
				break;
			case line_comment:
				target_str_end_index = *index;
				unsigned long len = target_str_end_index - target_str_start_index + 1;
				comment_str = (char*)malloc(len + 1);
				strncpy(comment_str, proto_str + target_str_start_index, len);
				comment_str[len] = '\0';
				return comment_str;
			default:
				break;
			}
		}
		// not new line, space, it should be first letter of protobuf key word
		if (!isspace(c) && status == start)
		{
			return NULL;
		}

		if (*index == str_len)
		{
			switch (status)
			{
			case line_comment:
			case block_comment_start:
				target_str_end_index = *index;
				unsigned long len = target_str_end_index - target_str_start_index + 1;
				comment_str = (char*)malloc(len + 1);
				strncpy(comment_str, proto_str + target_str_start_index, len);
				comment_str[len] = '\0';
				return comment_str;
			default:
				break;
			}
		}
		*index = *index + 1;
	}

	return comment_str;
}

GCharList* pick_up_all_comments(const char* proto_str, unsigned long* index)
{
	GCharList* comments = create_list(GCharNode);
	unsigned long str_len = strlen(proto_str);
	while (*index <= str_len)
	{
		skip_spaces(proto_str, index);
		char* comment_str = pick_up_comment_str(proto_str, index);
		if (comment_str != NULL)
		{
			char* cleaned_comment = clean_comment_str(comment_str);
			g_free(to_void_ptr(&comment_str));
			//  TODO: find a elegant method to split the string to lines.
			//   The strtok discard multiple empty lines if use it directly: strtok(cleaned_comment, "\n");
			char* replaced_comment = replace("\n", "\n~~", cleaned_comment);
			char* token = strtok(replaced_comment, "~~");

			// loop through the string to extract all other tokens
			while (token != NULL)
			{
				char* s = clean_comment_str(token);
				append_list(GCharNode, comments, trim(s));
				g_free(to_void_ptr(&s));
				token = strtok(NULL, "~~");
			}
		}
		else
		{
			break;
		}
	}
	return comments;
}
