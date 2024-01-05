/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Unit test for str lib methods.
**    Created Date:    2022-10-24
**    Updated Date:    2023-06-01
***********************************************************************************************************************/
#include <string.h>
#include "../macro.h"
#include "../../lib/str.h"
#include "../../lib/memory.h"

int test_str_copy()
{
	char* s0 = str_copy("     a aamain.c    ");
	if (strcmp(s0, "     a aamain.c    ") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	char* s1 = str_copy("聪明的一休    ");
	if (strcmp(s1, "聪明的一休    ") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}

	char* s3 = str_copy("amount");
	if (strcmp(s3, "amount") != 0)
	{
		g_free(to_void_ptr(&s3));
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_trim()
{
	char* s0 = trim("     a aamain.c    ");
	if (strcmp(s0, "a aamain.c") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	char* s1 = trim("     聪明的一休    ");
	if (strcmp(s1, "聪明的一休") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}

	char* s2 = trim("聪明的一休    ");
	if (strcmp(s2, "聪明的一休") != 0)
	{
		g_free(to_void_ptr(&s2));
		return TEST_FAIL;
	}

	char* s3 = trim("request_context");
	if (strcmp(s3, "request_context") != 0)
	{
		g_free(to_void_ptr(&s3));
		return TEST_FAIL;
	}

	char* s4 = trim("}");
	if (strcmp(s4, "}") != 0)
	{
		g_free(to_void_ptr(&s4));
		return TEST_FAIL;
	}

	char* s5 = trim("/*\n");
	if (strcmp(s5, "/*") != 0)
	{
		g_free(to_void_ptr(&s5));
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_trim_prefix()
{
	char* s0 = trim_prefix("aaadasdsa", "aaa");
	if (strcmp(s0, "dasdsa") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	char* s1 = trim_prefix("aaadasdsa", "");
	if (strcmp(s1, "aaadasdsa") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}

	char* s2 = trim_prefix("你好啊今天是个好日子", "你好啊");
	if (strcmp(s2, "今天是个好日子") != 0)
	{
		g_free(to_void_ptr(&s2));
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_trim_suffix()
{
	char* s0 = trim_suffix("aaadasdsa", "dsa");
	if (strcmp(s0, "aaadas") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	char* s1 = trim_suffix("aaadasdsa", "");
	if (strcmp(s1, "aaadasdsa") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}

	char* s2 = trim_suffix("你好啊今天是个好日子", "个好日子");
	if (strcmp(s2, "你好啊今天是") != 0)
	{
		g_free(to_void_ptr(&s2));
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_trim_pre_suf()
{
	char* s0 = trim_pre_suf("aaadasdsa", "a");
	if (strcmp(s0, "aadasds") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	char* s1 = trim_pre_suf("aaadasdsa", "");
	if (strcmp(s1, "aaadasdsa") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}


	char* s2 = trim_pre_suf("个好日子你好啊今天是个好日子", "个好日子");
	if (strcmp(s2, "你好啊今天是") != 0)
	{
		g_free(to_void_ptr(&s2));
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_starts_with()
{
	if (!starts_with("das", "dasdas uuu"))
		return TEST_FAIL;
	if (starts_with("ccc", "dasdas uuu"))
		return TEST_FAIL;

	return TEST_SUCCESS;
}

int test_ends_with()
{
	if (!ends_with("uuu", "dasdas uuu"))
		return TEST_FAIL;
	if (ends_with("ccc", "dasdas uuu"))
		return TEST_FAIL;

	return TEST_SUCCESS;
}

int test_replace()
{
	char* s0 = replace("foo", "~", "foobar foobar foobar");
	if (strcmp(s0, "~bar ~bar ~bar") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	char* s1 = replace("个", "~~", "个好日子你好啊今天是个好日子");
	if (strcmp(s1, "~~好日子你好啊今天是~~好日子") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}

	char* s2 = replace("\n", "\n====",
			"The fasdghjk adsfgh\nChronological work  legs\n\n\nsafdf\nChronological work  legs");
	if (strcmp(s2,
			"The fasdghjk adsfgh\n====Chronological work  legs\n====\n====\n====safdf\n====Chronological work  legs") !=
		0)
	{
		g_free(to_void_ptr(&s2));
		return TEST_FAIL;
	}

	char* s3 = replace("bbb", "~", "abbbbbccmmmbbb");
	if (strcmp(s3, "a~bbccmmm~") != 0)
	{
		g_free(to_void_ptr(&s3));
		return TEST_FAIL;
	}

	char* s4 = replace("\n", "\n====", "\n    map field comment a\n    // map field comment b\n\n     ");
	if (strcmp(s4, "\n====    map field comment a\n====    // map field comment b\n====\n====     ") != 0)
	{
		g_free(to_void_ptr(&s4));
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_char_to_binary_str()
{
	char* s0 = char_to_binary_str('a');
	if (strcmp(s0, "01100001") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	char* s1 = char_to_binary_str('y');
	if (strcmp(s1, "01111001") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_int_to_binary_str()
{
	char* s0 = int_to_binary_str(123456);
	if (strcmp(s0, "00000000000000011110001001000000") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	char* s1 = int_to_binary_str(453467234);
	if (strcmp(s1, "00011011000001110101110001100010") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_char_to_binary_str_with_space()
{
	char* s0 = char_to_binary_str_with_space("123456");
	if (strcmp(s0, "00110001 00110010 00110011 00110100 00110101 00110110") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	char* s1 = char_to_binary_str_with_space("acasdasd");
	if (strcmp(s1, "01100001 01100011 01100001 01110011 01100100 01100001 01110011 01100100") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_str_to_hex_str()
{
	char output1[13] = {};
	str_to_hex_str("123456", output1);
	if (strcmp(output1, "313233343536") != 0)
	{
		return TEST_FAIL;
	}

	char output2[17] = {};
	str_to_hex_str("acasdasd", output2);
	if (strcmp(output2, "6163617364617364") != 0)
	{
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_bytes_to_hex_str()
{
	byte input1[7] = { 1, 2, 3, 4, 5, 6, 7 };
	char* s0 = bytes_to_hex_str(input1, 7);
	if (strcmp(s0, "01020304050607") != 0)
	{
		g_free(to_void_ptr(&s0));
		return TEST_FAIL;
	}

	byte input2[2] = { 76, 77 };
	char* s1 = bytes_to_hex_str(input2, 2);
	if (strcmp(s1, "4c4d") != 0)
	{
		g_free(to_void_ptr(&s1));
		return TEST_FAIL;
	}

	g_free(to_void_ptr(&s0));
	g_free(to_void_ptr(&s1));
	return TEST_SUCCESS;
}

int test_repeat()
{
	char* s0 = repeat("abc", 5);
	if (strcmp(s0, "abcabcabcabcabc") != 0)
	{
		return TEST_FAIL;
	}

	char* s1 = repeat(" ", 5);
	if (strcmp(s1, "     ") != 0)
	{
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_pick_str_until()
{
	char* s0 = pick_str_until("abcdefghijklmn\n\raddasd\n9adasd", 'e', true);
	if (strcmp(s0, "abcde") != 0)
	{
		return TEST_FAIL;
	}

	char* s1 = pick_str_until("abcdefghijklmn\n\raddasd\n9adasd", 'e', false);
	if (strcmp(s1, "abcd") != 0)
	{
		return TEST_FAIL;
	}

	char* s3 = pick_str_until("abcdefghijklmn\n\raddasd\n9adasd", '\n', true);
	if (strcmp(s3, "abcdefghijklmn\n") != 0)
	{
		return TEST_FAIL;
	}

	char* s4 = pick_str_until("abcdefghijklmn\n\raddasd\n9adasd", '9', false);
	if (strcmp(s4, "abcdefghijklmn\n\raddasd\n") != 0)
	{
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}