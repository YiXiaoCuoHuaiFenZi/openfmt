/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-11-01
**    Updated Date:    2022-11-01
***********************************************************************************************************************/
#include "../macro.h"
#include "test_dir.h"
#include "../../lib/dir.h"

int test_is_file()
{
	if (!is_file("test_data/malformed/test_data_1.proto"))
		return TEST_FAIL;

	if (is_file("test_data"))
		return TEST_FAIL;

	return TEST_SUCCESS;
}

int test_list_files()
{
	List file_list = create_linked_list();
	list_files(".", file_list);
	return TEST_SUCCESS;
}

int test_print_files()
{
	List file_list = create_linked_list();
	list_files(".", file_list);
	print_files(file_list);
	return TEST_SUCCESS;
}