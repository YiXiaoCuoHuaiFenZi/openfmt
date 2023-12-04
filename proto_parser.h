/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse protobuf file to ADT(Abstract Data Type).
**    创建日期：    2022-09-30
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_PROTO_PARSER_H
#define OPENFMT_PROTO_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"
#include "object_parser.h"

typedef enum
{
	start,
	idle,
	line_comment,   // '/'
	block_comment_start,
	in_multiple_line_comment,
	multiple_line_comment_end,
	comment,
	multiple_line_comment,
	single_slash,
	star, // *
	object,
	word,
	symbol,
	space,
	syntax,
	package,
	option,
	import,
	message,
	message_element,
	proto_enum,
	enum_element,
	service,
	service_element,
	extend,
	one_of,
	invalid_key_word
} Status;

bool is_new_line(const char c);

char* clean_comment_str(const char* comment);

Protobuf* parse(const char* file_path);

void parse_proto_string(Protobuf* protobuf, const char* proto_str);

PbComment* pick_up_single_line_comment(const char* proto_str, unsigned long* index);

char* pick_up_comment_str(const char* proto_str, unsigned long* index);

GCharList* pick_up_all_comments(const char* proto_str, unsigned long* index);

Status get_status_from_key_word(const char* key_word);

char* get_str_until(const char* str, unsigned long* index, char ch, bool include);

char* pick_str_until(const char* str, unsigned long* index, char ch, bool include);

void skip_spaces(const char* str, unsigned long* index);

void parse_obj(const char* proto_str, unsigned long* index, Status* status, State* state, Protobuf* protobuf,
		PbCommentList* comments);

#endif //OPENFMT_PROTO_PARSER_H
