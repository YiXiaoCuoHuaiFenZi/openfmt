/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2023-12-06
**    Updated Date:    2023-12-06
***********************************************************************************************************************/
#include <ctype.h>
#include <stdbool.h>
#include "common.h"

bool is_new_line(char c)
{
	return (c == '\r' || c == '\n');
}

void skip_spaces(const char* str, unsigned long* index)
{
	char ch = str[*index];
	while (ch != '\0')
	{
		if (!isspace(ch))
		{
			break;
		}
		*index = *index + 1;
		ch = str[*index];
	}
}
