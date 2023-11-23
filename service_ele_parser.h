/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse service element.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_SERVICE_ELE_PARSER_H
#define OPENFMT_SERVICE_ELE_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"

PbServiceElement* make_pb_service_element(char* text, PbCommentList* top_comments);

#endif //OPENFMT_SERVICE_ELE_PARSER_H
