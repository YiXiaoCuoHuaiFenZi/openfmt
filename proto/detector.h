/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-07
**    Updated Date:    2022-10-07
***********************************************************************************************************************/
#ifndef OPENFMT_DETECTOR_H
#define OPENFMT_DETECTOR_H

#include <stdbool.h>

bool is_element(char* line);

bool is_message_element(char* line);

bool is_map_element(char* line);

bool is_enum_element(char* line);

bool is_service_element(char* line);

bool is_reserved_data_field(char* str);

#endif //OPENFMT_DETECTOR_H
