/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-11-23
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include "g_hash_table.h"
#include "str.h"
#include "memory.h"

unsigned long g_hash_func(const char *str)
{
    unsigned long sum = 0;
    for (int i = 0; str[i]; i++)
    {
        sum += str[i];
    }
    return sum % G_CAPACITY;
}

GItem *g_create_item(const char *key, const char *data_type, void *data, void (*data_free_func)(void *))
{
    GItem *item = (GItem *) g_malloc(sizeof(GItem));
    item->key = str_copy(key);
    item->data = data;
    item->data_type = str_copy(data_type);
    item->data_free_func = data_free_func;

    return item;
}

void g_free_item(GItem *item)
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

GHashTable *g_create_hashtable(int size)
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

void g_free_hashtable(GHashTable *table)
{
    for (int i = 0; i < table->size; i++)
    {
        GItem *item = table->items[i];
        if (item != NULL)
        {
            g_free_item(item);
        }
    }
    g_free(&(table->items));
    g_free(&table);
}

void g_hashtable_put(char *key, const char *data_type, void *data, void (*data_free_func)(void *), GHashTable *table)
{
    GItem *item = g_create_item(key, data_type, data, data_free_func);
    unsigned long index = g_hash_func((key));
    GItem *current_item = table->items[index];
    if (current_item == NULL)
    {
        if (table->count == table->size)
        {
            printf("Insert Error: Hash Table is full\n");
            g_free_item(item);
            return;
        }
        table->items[index] = item;
        table->count++;
    } else
    {
        if (strcmp(key, current_item->key) == 0)
        {
            table->items[index]->data = data;
            g_free_item(item);
        } else
        {
            // TODO: handle collision.
        }
    }
}

void *g_hashtable_get(char *key, GHashTable *table)
{
    unsigned long index = g_hash_func((key));
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