/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse Extend.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_EXTEND_PARSER_H
#define OPENFMT_EXTEND_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"

PbMessage* make_pb_extend(char* name, PbCommentList* comments);

#endif //OPENFMT_EXTEND_PARSER_H
