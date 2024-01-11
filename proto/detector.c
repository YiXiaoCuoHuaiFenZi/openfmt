/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-07
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include <printf.h>
#include "detector.h"
#include "../lib/str.h"
#include "../lib/memory.h"

bool is_map_element(char* str)
{
	// the map element looks like: map<string, Project> projects = 3;
	char* t = trim(str);
	char* r = replace(" ", "", t);
	bool is = starts_with("map<", r);
	g_free(to_void_ptr(&t));
	g_free(to_void_ptr(&r));
	return is;
}

bool is_element(char* str)
{
	char* semicolon = strstr(str, ";");
	char* double_slash = strstr(str, "//");
	char* slash_star = strstr(str, "/*");
	char* equal_sign = strstr(str, "=");
	if (semicolon == NULL)
		return false;

	if (is_reserved_data_field(str))
		return true;

	if (double_slash && semicolon > double_slash)
		return false;

	if (slash_star && semicolon > slash_star)
		return false;

	if (is_service_element(str))
		return true;

	if (is_map_element(str))
		return true;

	if (equal_sign)
		return true;

	return false;
}

bool is_message_element(char* str)
{
	// Example: repeated common.Tiger work_legs = 3;               // Chronological work  legs
	if (!is_element(str))
		return false;

	if (is_reserved_data_field(str))
		return true;

	if (is_service_element(str))
		return false;

	if (is_map_element(str))
		return true;

	// copy original string (char *) to char [], so it can use strtok to detect substrings(split).
	unsigned int len = strlen(str);
	char temp_str[len];
	for (int index = 0; index < len; index++)
	{
		temp_str[index] = str[index];
	}

	char* token = strtok(temp_str, "=");
	if (token == NULL)
	{
		return false; // no equal sign, return false.
	}
	token = strtok(token, " ");

	// check if the left of equal sign has only one string(the enum element name).
	int space_amount = 0;
	while (token != NULL)
	{
		if (strcmp(token, " ") != 0)
			space_amount++;
		token = strtok(NULL, " ");
	}
	return space_amount >= 2;
}

bool is_reserved_data_field(char* str)
{
	char* semicolon = strstr(str, ";");
	if (semicolon == NULL)
		return false;

	// Example of reserved keyword.
	// reserved 2, 15, 9 to 11;
	// reserved "foo", "bar";
	char* reserved_key_word = strstr(str, "reserved ");
	if (reserved_key_word)
		return true;

	return false;
}

bool is_enum_element(char* str)
{
	if (!is_element(str))
		return false;

	// copy original string (char *) to char [], so it can use strtok to detect substrings(split).
	unsigned int len = strlen(str);
	char temp_str[len];
	for (int index = 0; index < len; index++)
	{
		temp_str[index] = str[index];
	}

	char* token = strtok(temp_str, "=");
	if (token == NULL)
	{
		return false; // no equal sign, return false.
	}
	token = strtok(token, " ");

	// check if the left of equal sign has only one string(the enum element name).
	int space_amount = 0;
	while (token != NULL)
	{
		if (strcmp(token, " ") != 0)
			space_amount++;
		token = strtok(NULL, " ");
	}
	return space_amount == 1;
}

bool is_service_element(char* str)
{
	char* t = trim(str);
	bool is = starts_with("rpc ", t);
	g_free(to_void_ptr(&t));
	return is;
}
