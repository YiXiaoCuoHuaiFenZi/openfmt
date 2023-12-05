/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse syntax.
**    创建日期：    2022-10-07
**    更新日期：    2022-10-07
***********************************************************************************************************************/
#ifndef OPENFMT_SYNTAX_PARSER_H
#define OPENFMT_SYNTAX_PARSER_H

#include "proto.h"
#include "lib/queue.h"

void parse_syntax(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf);

#endif //OPENFMT_SYNTAX_PARSER_H
