/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Provide methods to deserialize proto file to Protobuf
*object.
**    创建日期：    2022-09-30
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "proto_parser.h"
#include "comment_parser.h"
#include "detector.h"
#include "import_parser.h"
#include "lib/memory.h"
#include "lib/str.h"
#include "lib/str_queue.h"
#include "lib/os.h"
#include "object_parser.h"
#include "option_parser.h"
#include "package_parser.h"
#include "syntax_parser.h"
#include "util/file_helper.h"
#include "message_ele_parser.h"
#include "message_parser.h"
#include "enum_ele_parser.h"
#include "enum_parser.h"
#include "service_ele_parser.h"
#include "service_parser.h"
#include "oneof_parser.h"
#include "extend_parser.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Protobuf* parse(const char* file_path)
{
	Protobuf* protobuf = (Protobuf*)g_malloc(sizeof(Protobuf));
	protobuf->syntax = NULL;
	protobuf->package = NULL;
	protobuf->options = NULL;
	protobuf->imports = NULL;
	protobuf->objects = create_linked_list();
	protobuf->colorful_text_list = NULL;
	PbTextColorConfig text_color_config;
	text_color_config.default_color = 0;
	text_color_config.default_key_word = 93;
	text_color_config.syntax_key = 93;
	text_color_config.syntax_value = 92;
	text_color_config.package_key = 93;
	text_color_config.package_value = 92;
	text_color_config.option_key = 93;
	text_color_config.option_name = 97;
	text_color_config.option_value = 92;
	text_color_config.import_key = 93;
	text_color_config.import_value = 92;
	text_color_config.obj_key = 93;
	text_color_config.obj_name = 97;
	text_color_config.message_element_key = 196;
	text_color_config.message_element_label = 93;
	text_color_config.message_element_type = 32;
	text_color_config.message_element_name = 95;
	text_color_config.message_element_number = 94;
	text_color_config.message_element_annotation = 97;
	text_color_config.enum_element_name = 95;
	text_color_config.enum_element_number = 94;
	text_color_config.enum_element_annotation = 97;
	text_color_config.service_element_label = 93;
	text_color_config.service_element_name = 95;
	text_color_config.service_element_request = 97;
	text_color_config.service_element_response = 97;
	text_color_config.comment = 90;

	PbConfig config;
	config.indents_unit = 4;
	config.align_by_equal_sign = true;
	config.top_comment = false;
	config.max_comment_len = 10000;
	config.preview = false;
	config.text_color_config = text_color_config;

	protobuf->config = config;
	protobuf->comments = NULL;

	char* content = read_file(file_path);
	parse_proto_string(protobuf, content);
	return protobuf;
}

bool is_new_line(const char c)
{
	return (c == '\r' || c == '\n');
}

char* clean_comment_str(const char* comment)
{
	char* trimmed_comment = trim(comment);

	if (starts_with("**", trimmed_comment))
	{
		char* s_1 = trim_prefix(trimmed_comment, "**");
		char* s_2 = trim(s_1);
		g_free(&s_1);
		g_free(&trimmed_comment);
		return s_2;
	}

	bool is_line_comment = starts_with("//", trimmed_comment);
	if (is_line_comment)
	{
		char* s_1 = trim_prefix(trimmed_comment, "//");
		char* s_2 = trim(s_1);
		g_free(&s_1);
		g_free(&trimmed_comment);
		return s_2;
	}

	bool is_block_comment = starts_with("/*", trimmed_comment) && ends_with("*/", trimmed_comment);
	if (is_block_comment)
	{
		char* s_1 = trim_prefix(trimmed_comment, "/*");
		char* s_2 = trim_suffix(s_1, "*/");
		char* s_3 = trim(s_2);
		g_free(&s_1);
		g_free(&s_2);
		g_free(&trimmed_comment);
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
		g_free(&line_comment);
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
			g_free(&comment_str);
			//  TODO: find a elegant method to split the string to lines.
			//   The strtok discard multiple empty lines if use it directly: strtok(cleaned_comment, "\n");
			char* replaced_comment = replace("\n", "\n====", cleaned_comment);
			char* token = strtok(replaced_comment, "====");

			// loop through the string to extract all other tokens
			while (token != NULL)
			{
				char* s = clean_comment_str(token);
				append_list(GCharNode, comments, trim(s));
				g_free(&s);
				token = strtok(NULL, "====");
			}
		}
		else
		{
			break;
		}
	}
	return comments;
}

Status get_status_from_key_word(const char* key_word)
{
	if (strcmp(key_word, "syntax") == 0)
	{
		return syntax;
	}
	if (strcmp(key_word, "package") == 0)
	{
		return package;
	}
	if (strcmp(key_word, "option") == 0)
	{
		return option;
	}
	if (strcmp(key_word, "import") == 0)
	{
		return import;
	}
	if (strcmp(key_word, "extend") == 0)
	{
		return extend;
	}
	if (strcmp(key_word, "message") == 0)
	{
		return message;
	}
	if (strcmp(key_word, "oneof") == 0)
	{
		return one_of;
	}
	if (strcmp(key_word, "enum") == 0)
	{
		return proto_enum;
	}
	if (strcmp(key_word, "service") == 0)
	{
		return service;
	}
	return invalid_key_word;
}

void skip_spaces(const char* str, unsigned long* index)
{
	char ch = str[*index];
	while (ch != '\0')
	{
		if (!isspace(ch))
		{
			break;
		}
		*index = *index + 1;
		ch = str[*index];
	}
}

char* get_str_until(const char* str, unsigned long* index, char ch, bool include)
{
	char cur_ch = str[*index];
	int len = 0;
	bool found = false;
	while (cur_ch != '\0')
	{
		if (cur_ch == ch)
		{
			found = true;
			break;
		}
		cur_ch = str[*index + len];
		len++;
	}
	if (found)
	{

		char* r = (char*)g_malloc(len + 1);
		if (include)
		{
			memcpy(r, str + *index, len);
			r[len] = '\0';
		}
		else
		{
			memcpy(r, str + *index, len - 1);
			r[len - 1] = '\0';
		}
		*index = *index + len;
		return r;
	}
	fail("target char not found.");
	return NULL;
}

char* pick_str_until(const char* str, unsigned long* index, char ch, bool include)
{
	char cur_ch = str[*index];
	int len = 1;
	bool found = false;
	while (cur_ch != '\0')
	{
		if (cur_ch == ch)
		{
			found = true;
			break;
		}
		cur_ch = str[*index + len];
		len++;
	}
	if (found)
	{

		char* r = (char*)g_malloc(len + 1);
		if (include)
		{
			memcpy(r, str + *index, len);
			r[len] = '\0';
		}
		else
		{
			memcpy(r, str + *index, len - 1);
			r[len - 1] = '\0';
		}
//		*index = *index + len;
		return r;
	}
	fail("target char not found.");
	return NULL;
}

void parse_obj(const char* proto_str, unsigned long* index, Status* status, State* state, Protobuf* protobuf,
		PbCommentList* top_comments)
{
	skip_spaces(proto_str, index);
	switch (*status)
	{
	case syntax:
		if (proto_str[*index] != '=')
		{
			char message[100];
			char num_str[15];
			sprintf(num_str, "%d", *index);
			strcat(message, "invalid symbol at ");
			strcat(message, num_str);
			strcat(message, " when parse syntax.\n");
			fail(message);
		}
		*index = *index + 1;
		char* s = get_str_until(proto_str, index, ';', false);
		if (s != NULL)
		{
			char* value = trim(s);
			g_free(&s);

			PbSyntax* pb_syntax = (PbSyntax*)g_malloc(sizeof(PbSyntax));
			pb_syntax->value = value;
			pb_syntax->comments = top_comments;

			// 解析单行注释
			PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
			if (single_line_comment != NULL)
			{
				append_list(PbCommentNode, pb_syntax->comments, single_line_comment);
			}
			protobuf->syntax = pb_syntax;
		}
		break;
	case package:
	{
		char* ss = get_str_until(proto_str, index, ';', false);
		if (ss != NULL)
		{
			char* value = trim(ss);
			g_free(&ss);

			PbPackage* pb_package = (PbPackage*)g_malloc(sizeof(PbPackage));
			pb_package->value = value;
			pb_package->comments = top_comments;

			// 解析单行注释
			PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
			if (single_line_comment != NULL)
			{
				append_list(PbCommentNode, pb_package->comments, single_line_comment);
			}
			protobuf->package = pb_package;
		}
	}
		break;
	case option:
	{
		PbOption* pb_option = (PbOption*)g_malloc(sizeof(PbOption));
		char* sss = get_str_until(proto_str, index, '=', false);
		if (sss != NULL)
		{
			char* name = trim(sss);
			g_free(&sss);
			pb_option->name = name;
		}
		char* ssss = get_str_until(proto_str, index, ';', false);
		if (ssss != NULL)
		{
			char* value = trim(ssss);
			g_free(&ssss);
			pb_option->value = value;
		}

		pb_option->comments = top_comments;
		// 解析单行注释
		PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
		if (single_line_comment != NULL)
		{
			append_list(PbCommentNode, pb_option->comments, single_line_comment);
		}

		if (protobuf->options == NULL)
		{
			protobuf->options = create_list(PbOptionNode);
		}
		append_list(PbOptionNode, protobuf->options, pb_option);
	}

		break;
	case import:
	{
		char* import_str = get_str_until(proto_str, index, ';', false);
		if (import_str != NULL)
		{
			char* value = trim(import_str);
			g_free(&import_str);

			PbImport* pb_import = (PbImport*)g_malloc(sizeof(PbImport));
			pb_import->value = value;
			pb_import->comments = top_comments;
			// 解析单行注释
			PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
			if (single_line_comment != NULL)
			{
				append_list(PbCommentNode, pb_import->comments, single_line_comment);
			}

			if (protobuf->imports == NULL)
			{
				protobuf->imports = create_list(PbImportNode);
			}
			append_list(PbImportNode, protobuf->imports, pb_import);
		}
	}
		break;
	case message:
	{
		char* message_str = get_str_until(proto_str, index, '{', false);
		if (message_str != NULL)
		{
			char* name = trim(message_str);
			g_free(&message_str);

			PbMessage* pb_message = make_pb_message(name, top_comments);
			g_free(&name);
			if (state->current_obj != NULL)
			{
				pb_message->parent_id = get_parent_id(state);
				pb_message->parent_type = state->current_obj_type;
				append_linked_list(pb_message, "PbMessage", get_parent_elements(state));
				current_obj_to_parent_obj(state);
			}
			else
			{
				append_linked_list(pb_message, "PbMessage", protobuf->objects);
			}

			// 解析单行注释
			PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
			if (line_comment != NULL)
			{
				append_list(PbCommentNode, pb_message->comments, line_comment);
			}

			state->l_brace++;
			state->current_obj = pb_message;
			state->current_obj_type = "PbMessage";
			g_hashtable_put(pb_message->id, state->current_obj_type, pb_message, NULL, state->obj_dic);
		}
		break;
	}
	case service:
	{
		char* str = get_str_until(proto_str, index, '{', false);
		if (str != NULL)
		{
			char* name = trim(str);
			g_free(&str);

			PbService* pb_service = make_pb_service(name, top_comments);
			g_free(&name);
			if (state->current_obj != NULL)
			{
				pb_service->parent_id = get_parent_id(state);
				pb_service->parent_type = state->current_obj_type;
				append_linked_list(pb_service, "PbService", get_parent_elements(state));
				current_obj_to_parent_obj(state);
			}
			else
			{
				append_linked_list(pb_service, "PbService", protobuf->objects);
			}

			// 解析单行注释
			PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
			if (line_comment != NULL)
			{
				append_list(PbCommentNode, pb_service->comments, line_comment);
			}

			state->l_brace++;
			state->current_obj = pb_service;
			state->current_obj_type = "PbService";
			g_hashtable_put(pb_service->id, state->current_obj_type, pb_service, NULL, state->obj_dic);
		}
		break;
	}
	case extend:
	{
		char* extend_str = get_str_until(proto_str, index, '{', false);
		if (extend_str != NULL)
		{
			char* name = trim(extend_str);
			g_free(&extend_str);

			PbExtend* pb_extend = make_pb_extend(name, top_comments);
			g_free(&name);
			if (state->current_obj != NULL)
			{
				pb_extend->parent_id = get_parent_id(state);
				pb_extend->parent_type = state->current_obj_type;
				append_linked_list(pb_extend, "PbExtend", get_parent_elements(state));
				current_obj_to_parent_obj(state);
			}
			else
			{
				append_linked_list(pb_extend, "PbExtend", protobuf->objects);
			}

			// 解析单行注释
			PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
			if (line_comment != NULL)
			{
				append_list(PbCommentNode, pb_extend->comments, line_comment);
			}

			state->l_brace++;
			state->current_obj = pb_extend;
			state->current_obj_type = "PbExtend";
			g_hashtable_put(pb_extend->id, state->current_obj_type, pb_extend, NULL, state->obj_dic);
		}
		break;
	}
	case one_of:
	{
		char* str = get_str_until(proto_str, index, '{', false);
		if (str != NULL)
		{
			char* name = trim(str);
			g_free(&str);

			PbOneOf* pb_one_of = make_pb_oneof(name, top_comments);
			g_free(&name);
			if (state->current_obj != NULL)
			{
				pb_one_of->parent_id = get_parent_id(state);
				pb_one_of->parent_type = state->current_obj_type;
				append_linked_list(pb_one_of, "PbOneOf", get_parent_elements(state));
				current_obj_to_parent_obj(state);
			}
			else
			{
				append_linked_list(pb_one_of, "PbOneOf", protobuf->objects);
			}

			// 解析单行注释
			PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
			if (line_comment != NULL)
			{
				append_list(PbCommentNode, pb_one_of->comments, line_comment);
			}

			state->l_brace++;
			state->current_obj = pb_one_of;
			state->current_obj_type = "PbOneOf";
			g_hashtable_put(pb_one_of->id, state->current_obj_type, pb_one_of, NULL, state->obj_dic);
		}
		break;
	}
	case proto_enum:
	{
		char* str = get_str_until(proto_str, index, '{', false);
		if (str != NULL)
		{
			char* name = trim(str);
			g_free(&str);

			PbEnum* pb_enum = new_parse_pb_enum(name, top_comments);
			g_free(&name);
			if (state->current_obj != NULL)
			{
				pb_enum->parent_id = get_parent_id(state);
				pb_enum->parent_type = state->current_obj_type;
				append_linked_list(pb_enum, "PbEnum", get_parent_elements(state));
				current_obj_to_parent_obj(state);
			}
			else
			{
				append_linked_list(pb_enum, "PbEnum", protobuf->objects);
			}

			// 解析单行注释
			PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
			if (line_comment != NULL)
			{
				append_list(PbCommentNode, pb_enum->comments, line_comment);
			}

			state->l_brace++;
			state->current_obj = pb_enum;
			state->current_obj_type = "PbEnum";
			g_hashtable_put(pb_enum->id, state->current_obj_type, pb_enum, NULL, state->obj_dic);
		}
		break;
	}
	case message_element:
	case extend_element:
	{
		char* text = get_str_until(proto_str, index, ';', true);
		PbMessageElement* pb_message_element = make_pb_message_element(text, top_comments);
		// 解析单行注释
		PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
		if (single_line_comment != NULL)
		{
			append_list(PbCommentNode, pb_message_element->comments, single_line_comment);
		}
		PbMessage* obj = (PbMessage*)(state->current_obj);
		append_linked_list(pb_message_element, "PbMessageElement", obj->elements);

		g_free(&text);
		break;
	}
	case enum_element:
	{
		char* text = get_str_until(proto_str, index, ';', true);
		PbEnumElement* pb_enum_element = make_pb_enum_element(text, top_comments);

		// 解析单行注释
		PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
		if (single_line_comment != NULL)
		{
			append_list(PbCommentNode, pb_enum_element->comments, single_line_comment);
		}
		PbEnum* obj = (PbEnum*)(state->current_obj);
		append_linked_list(pb_enum_element, "PbEnumElement", obj->elements);

		g_free(&text);
		break;
	}
	case service_element:
	{
		char* text = get_str_until(proto_str, index, ';', true);
		PbServiceElement* pb_service_element = make_pb_service_element(text, top_comments);

		// 解析单行注释
		PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
		if (single_line_comment != NULL)
		{
			append_list(PbCommentNode, pb_service_element->comments, single_line_comment);
		}
		PbService* obj = (PbService*)(state->current_obj);
		append_linked_list(pb_service_element, "PbServiceElement", obj->elements);

		g_free(&text);
		break;
	}
	}
}

void parse_proto_string(Protobuf* protobuf, const char* proto_str)
{
	char* key_word_tokens[] = { "syntax", "package", "option", "import", "extend", "message",
								"enum", "service", "oneof" };
	unsigned int keywords_amount = 9;
	Status status = start;
	unsigned long* index_ptr = NULL;
	unsigned long index = 0;
	index_ptr = &index;
	unsigned long str_len = strlen(proto_str);

	State* state = NULL; // used to store current object and parent object basic information.
	state = (State*)g_malloc(sizeof(State));
	state->l_brace = 0;
	state->r_brace = 0;
	state->current_obj = NULL;
	state->current_obj_type = NULL;
	state->parent_obj = NULL;
	state->parent_obj_type = NULL;
	state->obj_dic = g_create_hashtable(G_CAPACITY);

	while (index < str_len)
	{
		GCharList* comment_text_list = pick_up_all_comments(proto_str, index_ptr);
		PbCommentList* top_comments = make_comments(comment_text_list, TOP);
		dispose_list(GCharNode, comment_text_list, free_GChar);

		skip_spaces(proto_str, index_ptr);

		if (index == str_len)
		{
			if (top_comments->next != NULL)
			{
				// convert all comments as bottom comments
				PbCommentNode* cur = top_comments->next;
				while (cur)
				{
					cur->data->pos = BOTTOM;
					cur = cur->next;
				}
				protobuf->comments = top_comments;
			}
			else
			{
				dispose_list(PbCommentNode, top_comments, free_PbComment);
			}
			break;
		}

		if (proto_str[index] == '}')
		{
			state->r_brace++;
			/*
            ** There are comments exist at bottom of the message:
            ** message Test {
            **     string header = 1;// header
            **     // message inner bottom
            **     //message inner bottom bottombottombottombottom
            ** }
            **/
			if (top_comments != NULL)
			{
				update_current_obj_comments(state, top_comments);
				/*
				** the top_comments is bottom comments actually, and the comment value data will be added to the object,
				** so we must release this extra list data.
				*/
				free_comment_list(&top_comments);
			}

			if (state->parent_obj != NULL)
			{
				parent_obj_to_current_obj(state);
			}

			// top object, reset the state.
			if (state->l_brace == state->r_brace)
			{
				state->current_obj_type = NULL;
				state->current_obj = NULL;
				state->l_brace = state->r_brace = 0;
			}
			index = index + 1;
			continue; // continue to parse
		}

		bool is_obj = false;
		for (int i = 0; i < keywords_amount; i++)
		{
			char* key_word = key_word_tokens[i];
			size_t len = strlen(key_word);
			bool match = true;
			for (int j = 0; j < len; j++)
			{
				if (key_word[j] != proto_str[index + j])
				{
					match = false;
					break;
				}
			}
			// the keyword must be followed by a space.
			if (match && !isspace(proto_str[index + len]))
			{
				match = false;
			}

			if (match)
			{
				index = index + len + 1;
				status = get_status_from_key_word(key_word);
				parse_obj(proto_str, index_ptr, &status, state, protobuf, top_comments);
				is_obj = true;
				break;
			}
		}
		if (is_obj)
		{
			continue;
		}

		if (status == message || status == one_of || status == proto_enum || status == service || status == extend ||
			status == message_element || status == enum_element || status == service_element)
		{

			char* text = pick_str_until(proto_str, index_ptr, ';', true);
			if (is_message_element(text))
			{
				status = message_element;
				parse_obj(proto_str, index_ptr, &status, state, protobuf, top_comments);
			}

			if (is_enum_element(text))
			{
				status = enum_element;
				parse_obj(proto_str, index_ptr, &status, state, protobuf, top_comments);
			}

			if (is_service_element(text))
			{
				status = service_element;
				parse_obj(proto_str, index_ptr, &status, state, protobuf, top_comments);
			}
		}
	}
}
