/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   文件相关操作，读写等。
**    Created Date:    2023-03-21
**    Updated Date:    2023-03-21
***********************************************************************************************************************/
#include "file.h"

char* read_text(const char* file_path)
{
	FILE* f = fopen(file_path, "r");
	if (f == NULL)
	{
		return NULL;
	}
	fseek(f, 0L, SEEK_END);
	long num_bytes = ftell(f);
	fseek(f, 0L, SEEK_SET);
	char* text = calloc(num_bytes, sizeof(char));
	fread(text, sizeof(char), num_bytes, f);

	return text;
}