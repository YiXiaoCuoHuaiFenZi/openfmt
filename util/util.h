/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-03
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_UTIL_H
#define OPENFMT_UTIL_H

#include <stdbool.h>

void show_base_colors();

void show_colors();


void print_text_with_color(const char* message, int color_code, bool print_code);

#endif //OPENFMT_UTIL_H
