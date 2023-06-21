/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-09-30
**    更新日期：    2022-09-30
***********************************************************************************************************************/
#ifndef OPENFMT_FILE_HELPER_H
#define OPENFMT_FILE_HELPER_H

#include "../lib/linked_list.h"
#include "../lib/str_queue.h"

List ReadLineToList(const char *filePath);

void PrintLineList(List lines);

SQueue ReadLineToSQueue(const char *filePath);

void PrintSQueue(SQueue lineQueue);

#endif //OPENFMT_FILE_HELPER_H
