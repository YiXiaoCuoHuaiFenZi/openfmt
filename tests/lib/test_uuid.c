/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    UUID单元测试
**    创建日期：    2022-11-09
**    更新日期：    2023-05-08
***********************************************************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "test_uuid.h"

int test_random_bytes()
{
	byte* bytes1 = random_bytes(16);
	int a1 = bytes1[0] | bytes1[1] << 8 | bytes1[2] << 16 | bytes1[3] << 24;
	int b1 = bytes1[4] | bytes1[5] << 8 | bytes1[6] << 16 | bytes1[7] << 24;
	int c1 = bytes1[8] | bytes1[9] << 8 | bytes1[10] << 16 | bytes1[11] << 24;
	int d1 = bytes1[12] | bytes1[13] << 8 | bytes1[14] << 16 | bytes1[15] << 24;

	byte* bytes2 = random_bytes(16);
	int a2 = bytes2[0] | bytes2[1] << 8 | bytes2[2] << 16 | bytes2[3] << 24;
	int b2 = bytes2[4] | bytes2[5] << 8 | bytes2[6] << 16 | bytes2[7] << 24;
	int c2 = bytes2[8] | bytes2[9] << 8 | bytes2[10] << 16 | bytes2[11] << 24;
	int d2 = bytes2[12] | bytes2[13] << 8 | bytes2[14] << 16 | bytes2[15] << 24;

	if (a1 == a2 && b1 == b2 && c1 == c2 && d1 == d2)
	{
		return TEST_FAIL;
	}

	return TEST_SUCCESS;
}

int test_uuid4()
{
#define size 1000
	UUID* uuid_list[size] = { NULL };
	for (int i = 0; i < size; i++)
	{
		UUID* u = uuid4();
		printf("%s\n", u->hex);

		bool is_present = false;
		for (int j = 0; j < size; j++)
		{
			UUID* t = uuid_list[j];
			if (t == NULL)
			{
				break;
			}

			is_present = strcmp(u->hex, t->hex) == 0;
		}

		if (!is_present)
		{
			uuid_list[i] = u;
			continue;
		}

		free_uuid_array(uuid_list, size);
		return TEST_FAIL;
	}
	free_uuid_array(uuid_list, size);

	return TEST_SUCCESS;
}

void free_uuid_array(UUID* uuid_list[], int len)
{
	for (int i = 0; i < len; i++)
	{
		UUID* t = uuid_list[i];
		if (t == NULL)
		{
			break;
		}
		free_uuid4(t);
	}
}