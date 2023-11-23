/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse message.
**    创建日期：    2022-10-25
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_MESSAGE_PARSER_H
#define OPENFMT_MESSAGE_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"

PbMessage *parse_pb_message(char *line, SQueue line_queue, PbCommentList *comments);

PbMessage *new_parse_pb_message(char *text, PbCommentList *comments);

#endif //OPENFMT_MESSAGE_PARSER_H
