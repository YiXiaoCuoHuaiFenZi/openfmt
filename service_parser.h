/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse service.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_SERVICE_PARSER_H
#define OPENFMT_SERVICE_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"
#include "proto_parser.h"

PbService* make_pb_service(char* line, PbCommentList* comments);

void parse_service(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		State* state,
		Protobuf* protobuf
);

#endif //OPENFMT_SERVICE_PARSER_H
