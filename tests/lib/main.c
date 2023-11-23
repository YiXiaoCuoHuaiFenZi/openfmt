/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Unit test executable app.
**    创建日期：    2022-10-27
**    更新日期：    2023-03-17
***********************************************************************************************************************/
#include <string.h>
#include "test_str.h"
#include "g_list_test.h"
#include "test_dir.h"
#include "test_uuid.h"
#include "test_hash_table.h"

int main(int argc, char* args[])
{
	if (argc < 2)
		return 1;

	// test str
	if (strcmp(args[1], "test_str_copy") == 0)
		return test_str_copy();
	if (strcmp(args[1], "test_trim") == 0)
		return test_trim();
	if (strcmp(args[1], "test_trim_prefix") == 0)
		return test_trim_prefix();
	if (strcmp(args[1], "test_trim_suffix") == 0)
		return test_trim_suffix();
	if (strcmp(args[1], "test_trim_pre_suf") == 0)
		return test_trim_pre_suf();
	if (strcmp(args[1], "test_starts_with") == 0)
		return test_starts_with();
	if (strcmp(args[1], "test_ends_with") == 0)
		return test_ends_with();
	if (strcmp(args[1], "test_replace") == 0)
		return test_replace();
	if (strcmp(args[1], "test_char_to_binary_str") == 0)
		return test_char_to_binary_str();
	if (strcmp(args[1], "test_int_to_binary_str") == 0)
		return test_int_to_binary_str();
	if (strcmp(args[1], "test_char_to_binary_str_with_space") == 0)
		return test_char_to_binary_str_with_space();
	if (strcmp(args[1], "test_str_to_hex_str") == 0)
		return test_str_to_hex_str();
	if (strcmp(args[1], "test_bytes_to_hex_str") == 0)
		return test_bytes_to_hex_str();
	if (strcmp(args[1], "test_repeat") == 0)
		return test_repeat();

	// test g_list
	if (strcmp(args[1], "test_G_NodeTemplate_int") == 0)
		return test_G_NodeTemplate_int();
	if (strcmp(args[1], "test_G_NodeTemplate_char") == 0)
		return test_G_NodeTemplate_char();
	if (strcmp(args[1], "test_create_list") == 0)
		return test_create_linked_list();
	if (strcmp(args[1], "test_append_list") == 0)
		return test_append_list();
	if (strcmp(args[1], "test_is_empty_list") == 0)
		return test_is_empty_list();
	if (strcmp(args[1], "test_dispose_list") == 0)
		return test_dispose_list();

	// test dir
	if (strcmp(args[1], "test_is_file") == 0)
		return test_is_file();
	if (strcmp(args[1], "test_list_files") == 0)
		return test_list_files();
	if (strcmp(args[1], "test_print_files") == 0)
		return test_print_files();

	// test uuid
	if (strcmp(args[1], "test_random_bytes") == 0)
		return test_random_bytes();
	if (strcmp(args[1], "test_uuid4") == 0)
		return test_uuid4();

	// test hash table
	if (strcmp(args[1], "test_hash_table") == 0)
		return test_hash_table();

	return 0;
}