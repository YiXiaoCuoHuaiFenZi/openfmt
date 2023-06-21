/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-03
**    更新日期：    2022-10-03
***********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void ShowBaseColors()
{
    printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");
}

void ShowColors()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int colorCode = i * 16 + j;
            PrintTextWithColor("This text is colorful", colorCode, true);
            printf("\n");
        }
    }
}

void PrintTextWithColor(const char *message, int colorCode, bool printCode)
{
    char *colorCodeStr;
    char *anciColorStr;
    if (colorCode < 10)
    {
        colorCodeStr = g_malloc(1);
        anciColorStr = g_malloc(7);
    } else if (colorCode < 100)
    {
        colorCodeStr = g_malloc(2);
        anciColorStr = g_malloc(8);
    } else
    {
        colorCodeStr = g_malloc(3);
        anciColorStr = g_malloc(9);
    }
    sprintf(colorCodeStr, "%d", colorCode);
    strcat(anciColorStr, ANSI_COLOR_PREFIX);
    strcat(anciColorStr, colorCodeStr);
    strcat(anciColorStr, ANSI_COLOR_SUFFIX);

    printf("%s", anciColorStr);
    if (printCode)
    {
        printf("%d  %s", colorCode, message);
    } else
    {
        printf("%s", message);
    }

    printf(ANSI_COLOR_RESET);

    g_free(&colorCodeStr);
    g_free(&anciColorStr);
}