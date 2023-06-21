/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse service.
**    创建日期：    2022-11-15
**    更新日期：    2022-11-15
***********************************************************************************************************************/
#ifndef OPENFMT_SERVICE_PARSER_H
#define OPENFMT_SERVICE_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"

PbService *parse_pb_service(char *line, SQueue lineQueue, PbCommentList *comments);

#endif //OPENFMT_SERVICE_PARSER_H
