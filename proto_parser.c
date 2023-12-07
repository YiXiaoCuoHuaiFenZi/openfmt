/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Provide methods to deserialize proto file to Protobuf
*object.
**    创建日期：    2022-09-30
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "proto_parser.h"
#include "common.h"
#include "comment_parser.h"
#include "detector.h"
#include "import_parser.h"
#include "lib/memory.h"
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

void parse_obj(
		const char* proto_str,
		unsigned long* index,
		Status* status,
		Protobuf* protobuf,
		PbCommentList* top_comments,
		Stack object_stack
)
{
	skip_spaces(proto_str, index);
	switch (*status)
	{
	case syntax:
		parse_syntax(proto_str, index, top_comments, protobuf);
		break;
	case package:
		parse_package(proto_str, index, top_comments, protobuf);
		break;
	case option:
		parse_option(proto_str, index, top_comments, protobuf);
		break;
	case import:
		parse_import(proto_str, index, top_comments, protobuf);
		break;
	case message:
		parse_message(proto_str, index, top_comments, protobuf, object_stack);
		break;
	case service:
		parse_service(proto_str, index, top_comments, protobuf, object_stack);
		break;
	case extend:
		parse_extend(proto_str, index, top_comments, protobuf, object_stack);
		break;
	case one_of:
		parse_oneof(proto_str, index, top_comments, protobuf, object_stack);
		break;
	case proto_enum:
		parse_pb_enum(proto_str, index, top_comments, protobuf, object_stack);
		break;
	case message_element:
	case extend_element:
		parse_message_element(proto_str, index, top_comments, object_stack);
		break;
	case enum_element:
		parse_pb_enum_element(proto_str, index, top_comments, object_stack);
		break;
	case service_element:
		parse_pb_service_element(proto_str, index, top_comments, object_stack);
		break;
	default:
		fail("unknown status.");
	}
}

void parse_proto_string(Protobuf* protobuf, const char* proto_str)
{
	Stack object_stack = create_stack();

	char* key_word_tokens[] = { "syntax", "package", "option", "import", "extend", "message",
								"enum", "service", "oneof" };
	unsigned int keywords_amount = 9;
	Status status = start;
	unsigned long* index_ptr = NULL;
	unsigned long index = 0;
	index_ptr = &index;
	unsigned long str_len = strlen(proto_str);

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
				PtrToStackNode stack_node = (PtrToStackNode)top_stack(object_stack, NULL);
				append_bottom_comments(stack_node, top_comments);
				/*
				** the top_comments is bottom comments actually, and the comment value data will be added to the object,
				** so we must release this extra list data.
				*/
				free_comment_list(&top_comments);
			}

			index = index + 1;
			pop_stack(object_stack, NULL);
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
				parse_obj(proto_str, index_ptr, &status, protobuf, top_comments, object_stack);
				is_obj = true;
				break;
			}
		}
		if (is_obj)
		{
			continue;
		}

		// parse object element
		if (status == message || status == one_of || status == proto_enum || status == service || status == extend ||
			status == message_element || status == enum_element || status == service_element)
		{

			char* text = pick_str_until(proto_str, index_ptr, ';', true);
			if (is_message_element(text))
			{
				status = message_element;
				parse_obj(proto_str, index_ptr, &status, protobuf, top_comments, object_stack);
			}

			if (is_enum_element(text))
			{
				status = enum_element;
				parse_obj(proto_str, index_ptr, &status, protobuf, top_comments, object_stack);
			}

			if (is_service_element(text))
			{
				status = service_element;
				parse_obj(proto_str, index_ptr, &status, protobuf, top_comments, object_stack);
			}
		}
	}
}
