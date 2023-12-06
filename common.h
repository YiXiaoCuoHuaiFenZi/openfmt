/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2023-12-06
**    更新日期：    2023-12-06
***********************************************************************************************************************/
#ifndef OPENFMT_COMMON_H
#define OPENFMT_COMMON_H

#include <string.h>
#include "lib/str.h"

bool is_new_line(const char c);

void skip_spaces(const char* str, unsigned long* index);

char* get_str_until(const char* str, unsigned long* index, char ch, bool include);

char* pick_str_until(const char* str, unsigned long* index, char ch, bool include);

#endif //OPENFMT_COMMON_H
