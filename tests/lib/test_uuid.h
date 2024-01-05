/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Unit tests for UUID.
**    Created Date:    2022-11-09
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
#ifndef OPENFMT_TEST_UUID_H
#define OPENFMT_TEST_UUID_H

#include "../macro.h"
#include "../../lib/uuid.h"

int test_random_bytes();

int test_uuid4();

void free_uuid_array(UUID* uuid_list[], int len);

#endif //OPENFMT_TEST_UUID_H
