/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-28
**    Updated Date:    2022-10-28
***********************************************************************************************************************/
#ifndef OPENFMT_G_LIST_TEST_H
#define OPENFMT_G_LIST_TEST_H

#include "../../lib/g_list.h"

int test_G_NodeTemplate_int();

int test_G_NodeTemplate_char();

int test_create_linked_list();

int test_append_list();

int test_is_empty_list();

int test_dispose_list();

void free_char_test(GCharNode* ptr);

#endif //OPENFMT_G_LIST_TEST_H
