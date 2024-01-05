/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-03
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "../lib/memory.h"

#define ANSI_COLOR_PREFIX   "\x1b["
#define ANSI_COLOR_SUFFIX   "m"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void show_base_colors()
{
	printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");
}

void show_colors()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int color_code = i * 16 + j;
			print_text_with_color("This text is colorful", color_code, true);
			printf("\n");
		}
	}
}

void print_text_with_color(const char* message, int color_code, bool print_code)
{
	char* colorCodeStr;
	char* anciColorStr;
	if (color_code < 10)
	{
		colorCodeStr = g_malloc(1);
		anciColorStr = g_malloc(7);
	}
	else if (color_code < 100)
	{
		colorCodeStr = g_malloc(2);
		anciColorStr = g_malloc(8);
	}
	else
	{
		colorCodeStr = g_malloc(3);
		anciColorStr = g_malloc(9);
	}
	sprintf(colorCodeStr, "%d", color_code);
	strcat(anciColorStr, ANSI_COLOR_PREFIX);
	strcat(anciColorStr, colorCodeStr);
	strcat(anciColorStr, ANSI_COLOR_SUFFIX);

	printf("%s", anciColorStr);
	if (print_code)
	{
		printf("%d  %s", color_code, message);
	}
	else
	{
		printf("%s", message);
	}

	printf(ANSI_COLOR_RESET);

	g_free(to_void_ptr(&colorCodeStr));
	g_free(to_void_ptr(&anciColorStr));
}