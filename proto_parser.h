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
	extend,
	message,
	message_element,
	extend_element,
	proto_enum,
	enum_element,
	service,
	service_element,
	one_of,
	invalid_key_word
} Status;

Protobuf* parse(const char* file_path);

void parse_proto_string(Protobuf* protobuf, const char* proto_str);

Status get_status_from_key_word(const char* key_word);

void parse_obj(const char* proto_str, unsigned long* index, Status* status, State* state, Protobuf* protobuf,
		PbCommentList* comments);

#endif //OPENFMT_PROTO_PARSER_H
