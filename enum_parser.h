/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse enum.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_ENUM_PARSER_H
#define OPENFMT_ENUM_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"
#include "proto_parser.h"

PbEnum* make_pb_enum(char* name, PbCommentList* comments);

void parse_pb_enum(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		State* state,
		Protobuf* protobuf
);

#endif //OPENFMT_ENUM_PARSER_H
