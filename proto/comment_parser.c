/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Pick up comments.
**    Created Date:    2022-10-03
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "comment_parser.h"
#include "proto.h"
#include "../lib/memory.h"
#include "../lib/os.h"

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
	char* cleaned_comment = NULL;
	char* trimed_comment = trim(comment);

	if (starts_with("//", trimed_comment))
	{
		cleaned_comment = trim_prefix(trimed_comment, "//");
		g_free(to_void_ptr(&trimed_comment));
	}
	else if (starts_with("/*", trimed_comment) && ends_with("*/", trimed_comment))
	{
		char* s0 = trim_prefix(trimed_comment, "/*");
		cleaned_comment = trim_suffix(s0, "*/");
		g_free(to_void_ptr(&s0));
		g_free(to_void_ptr(&trimed_comment));
	}
	else
	{
		cleaned_comment = trimed_comment;
	}

	char* r0 = trim(cleaned_comment);
	char* r1 = trim_pre_suf(r0, " ");
	char* r2 = trim_pre_suf(r1, "*");
	char* r3 = trim_pre_suf(r2, "/");
	char* r4 = trim(r3);
	g_free(to_void_ptr(&r0));
	g_free(to_void_ptr(&r1));
	g_free(to_void_ptr(&r2));
	g_free(to_void_ptr(&r3));

	return r4;
}

PbComment* pick_up_line_comment(const char* proto_str, unsigned long* index)
{
	char* s = pick_str_until(proto_str + *index, '\n', true);
	if (s == NULL)
		fail("target char not found.");

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
		g_free(to_void_ptr(&s));
		return pb_comment;
	}
	g_free(to_void_ptr(&s));
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
			if (token == NULL)
			{
				append_list(GCharNode, comments, trim(replaced_comment));
			}
			else
			{
				// loop through the string to extract all other tokens
				while (token != NULL)
				{
					char* s = clean_comment_str(token);
					append_list(GCharNode, comments, trim(s));
					g_free(to_void_ptr(&s));
					token = strtok(NULL, "~~");
				}
			}
			g_free(to_void_ptr(&replaced_comment));
			g_free(to_void_ptr(&cleaned_comment));
		}
		else
		{
			break;
		}
	}
	return comments;
}
