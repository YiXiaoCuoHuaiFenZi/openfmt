/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse OneOf.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_ONEOF_PARSER_H
#define OPENFMT_ONEOF_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"
#include "proto_parser.h"

PbOneOf* make_pb_oneof(char* name, PbCommentList* comments);

void parse_oneof(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		State* state,
		Protobuf* protobuf
);

#endif //OPENFMT_ONEOF_PARSER_H
