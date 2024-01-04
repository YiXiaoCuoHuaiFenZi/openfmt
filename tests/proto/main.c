/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Unit test executable app.
**    创建日期：    2022-10-27
**    更新日期：    2023-03-17
***********************************************************************************************************************/
#include <string.h>
#include "test_file_format.h"

int main(int argc, char* args[])
{
	printf("test proto.\n");
	printf("test proto %d.\n", argc);
	if (argc < 2)
		return 1;
//
//	// test for format proto files under a directory.
	if (strcmp(args[1], "test_format_directory") == 0){
		printf("(strcmp(args[1], \"test_format_directory\") == 0).\n");
		return test_format_directory("test_data/malformed", "test_data/formatted");
	}

	printf("test proto aaa.\n");
	return 0;
}