/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-07
**    更新日期：    2022-10-07
***********************************************************************************************************************/
#ifndef OPENFMT_DETECTOR_H
#define OPENFMT_DETECTOR_H

#include <stdbool.h>

bool is_element(char* line);

bool is_message_element(char* line);

bool is_map_element(char* line);

bool is_enum_element(char* line);

bool is_service_element(char* line);

#endif //OPENFMT_DETECTOR_H
