/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse protobuf file to ADT(Abstract Data Type).
**    Created Date:    2022-09-30
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_PROTO_PARSER_H
#define OPENFMT_PROTO_PARSER_H

#include "common.h"
#include "proto.h"
#include "../lib/str_queue.h"
#include "object_parser.h"
#include "../lib/stack.h"

Protobuf* parse(const char* file_path);

void parse_proto_string(Protobuf* protobuf, const char* proto_str);

Status get_status_from_key_word(const char* key_word);

void parse_obj(
		const char* proto_str,
		unsigned long* index,
		const Status* status,
		Protobuf* protobuf,
		PbCommentList* comments,
		Stack object_stack
);

#endif //OPENFMT_PROTO_PARSER_H
