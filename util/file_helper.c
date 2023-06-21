/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-09-30
**    更新日期：    2022-09-30
***********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_helper.h"
#include "../lib/memory.h"


List ReadLineToList(const char *filePath)
{
    FILE *fp;
    char *des_line = NULL;
    size_t len = 0;
    size_t read = 0;

    fp = fopen(filePath, "r");
    if (fp == NULL)
    {
        printf("could not open file: %s", filePath);
        return NULL;
    }

    List list = CreateList();
    while ((read = getline(&des_line, &len, fp)) != -1)
    {
        char *line = (char *) g_malloc(strlen(des_line) + 1);
        strcpy(line, des_line);
        AppendList(line, "char", list);
    }

    fclose(fp);
    g_free(&des_line);

    return list;
}

void PrintLineList(List lines)
{
    PtrToNode pNode = lines->next;
    while (pNode)
    {
        char *line = (char *) pNode->data;
        printf("%s", line);
        pNode = pNode->next;
    }
}

SQueue ReadLineToSQueue(const char *filePath)
{
    FILE *fp;
    char *des_line = NULL;
    size_t len = 0;
    size_t read = 0;

    fp = fopen(filePath, "r");
    if (fp == NULL)
    {
        printf("could not open file: %s", filePath);
        return NULL;
    }

    SQueue lines = CreateSQueue();
    while ((read = getline(&des_line, &len, fp)) != -1)
    {
        char *line = (char *) g_malloc(strlen(des_line) + 1);
        strcpy(line, des_line);
        EnSQueue(line, lines);
    }

    fclose(fp);
    g_free(&des_line);

    return lines;
}

void PrintSQueue(SQueue lineQueue)
{
    PtrToSQueueNode currentNode = lineQueue->head;
    while (currentNode)
    {
        printf("%s", currentNode->str);
        currentNode = currentNode->next;
    }
}