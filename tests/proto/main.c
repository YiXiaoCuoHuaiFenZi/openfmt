/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Unit test executable app.
**    Created Date:    2022-10-27
**    Updated Date:    2023-03-17
***********************************************************************************************************************/
#include <string.h>
#include "test_file_format.h"

int main(int argc, char* args[])
{
	if (argc < 2)
		return 1;

	// test for format proto files under a directory.
	if (strcmp(args[1], "test_format_directory") == 0)
		return test_format_directory("test_data/malformed", "test_data/formatted");

	return 0;
}