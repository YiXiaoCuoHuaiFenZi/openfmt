/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-11-09
**    更新日期：    2022-11-09
***********************************************************************************************************************/
#ifndef OPENFMT_TEST_UUID_H
#define OPENFMT_TEST_UUID_H
#include "../macro.h"
#include "../../lib/uuid.h"

int test_random_bytes();

int test_uuid4();

void free_uuid_array(UUID *uuid_list[], int len);

#endif //OPENFMT_TEST_UUID_H
