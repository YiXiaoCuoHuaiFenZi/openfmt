/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-11-23
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include "g_hash_table.h"
#include "str.h"
#include "memory.h"

unsigned long HashFunc(const char *str)
{
    unsigned long sum = 0;
    for (int i = 0; str[i]; i++)
    {
        sum += str[i];
    }
    return sum % G_CAPACITY;
}

GItem *CreateGItem(const char *key, const char *data_type, void *data, void (*data_free_func)(void *))
{
    GItem *item = (GItem *) g_malloc(sizeof(GItem));
    item->key = str_copy(key);
    item->data = data;
    item->data_type = str_copy(data_type);
    item->data_free_func = data_free_func;

    return item;
}

void FreeGItem(GItem *item)
{
    g_free(&(item->key));
    g_free(&(item->data_type));

    /*
    ** if the date free function is not set, not call it.
    */
    if (item->data_free_func)
    {
        item->data_free_func(item->data);
    }

    g_free(&item);
}

GHashTable *CreateGHashTable(int size)
{
    GHashTable *table = (GHashTable *) g_malloc(sizeof(GHashTable));
    table->size = size;
    table->count = 0;
    table->items = (GItem **) calloc(table->size, sizeof(GItem *));
    for (int i = 0; i < table->size; i++)
    {
        table->items[i] = NULL;
    }

    return table;
}

void FreeGHashTable(GHashTable *table)
{
    for (int i = 0; i < table->size; i++)
    {
        GItem *item = table->items[i];
        if (item != NULL)
        {
            FreeGItem(item);
        }
    }
    g_free(&(table->items));
    g_free(&table);
}

void GHashTablePut(char *key, const char *data_type, void *data, void (*data_free_func)(void *), GHashTable *table)
{
    GItem *item = CreateGItem(key, data_type, data, data_free_func);
    unsigned long index = HashFunc((key));
    GItem *current_item = table->items[index];
    if (current_item == NULL)
    {
        if (table->count == table->size)
        {
            printf("Insert Error: Hash Table is full\n");
            FreeGItem(item);
            return;
        }
        table->items[index] = item;
        table->count++;
    } else
    {
        if (strcmp(key, current_item->key) == 0)
        {
            table->items[index]->data = data;
            FreeGItem(item);
        } else
        {
            // TODO: handle collision.
        }
    }
}

void *GHashTableGet(char *key, GHashTable *table)
{
    unsigned long index = HashFunc((key));
    GItem *item = table->items[index];
    if (item != NULL)
    {
        if (strcmp(item->key, key) == 0)
        {
            return item->data;
        }
    }
    return NULL;
}