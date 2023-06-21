/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse enum.
**    创建日期：    2022-11-15
**    更新日期：    2022-11-15
***********************************************************************************************************************/
#ifndef OPENFMT_ENUM_PARSER_H
#define OPENFMT_ENUM_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"

PbEnum *parse_pb_enum(char *line, SQueue lineQueue, PbCommentList *comments);

#endif //OPENFMT_ENUM_PARSER_H
