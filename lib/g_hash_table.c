/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-11-23
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include "g_hash_table.h"
#include "str.h"
#include "memory.h"
#include "os.h"

unsigned long g_sum_of_str(const char* str)
{
	unsigned long sum = 0;
	for (int i = 0; str[i]; i++)
	{
		sum += str[i];
	}
	return sum;
}

unsigned long g_hash_func_one(unsigned long key)
{
	return key % G_CAPACITY;
}

unsigned long g_hash_func_two(unsigned long key)
{
	return G_PRIME - (key % G_PRIME);
}

GItem* g_create_item(const char* key, const char* data_type, void* data, void (* data_free_func)(void*))
{
	GItem* item = (GItem*)g_malloc(sizeof(GItem));
	item->key = str_copy(key);
	item->data = data;
	item->data_type = str_copy(data_type);
	item->data_free_func = data_free_func;

	return item;
}

void g_free_item(GItem* item)
{
	g_free(to_void_ptr(&(item->key)));
	g_free(to_void_ptr(&(item->data_type)));

	// if the date free function is not set, not call it.
	if (item->data_free_func)
	{
		item->data_free_func(item->data);
	}

	g_free(to_void_ptr(&item));
}

GHashTable* g_create_hashtable(int size)
{
	GHashTable* table = (GHashTable*)g_malloc(sizeof(GHashTable));
	table->size = size;
	table->count = 0;
	table->items = (GItem**)calloc(table->size, sizeof(GItem*));
	for (int i = 0; i < table->size; i++)
	{
		table->items[i] = NULL;
	}

	return table;
}

void g_free_hashtable(GHashTable* table)
{
	for (int i = 0; i < table->size; i++)
	{
		GItem* item = table->items[i];
		if (item != NULL)
		{
			g_free_item(item);
		}
	}
	g_free(to_void_ptr(&(table->items)));
	g_free(to_void_ptr(&table));
}

void g_hashtable_put(char* key, const char* data_type, void* data, void (* data_free_func)(void*), GHashTable* table)
{
	GItem* item = g_create_item(key, data_type, data, data_free_func);
	unsigned long str_sum = g_sum_of_str((key));
	unsigned long probe = g_hash_func_one(str_sum);
	unsigned long offset = g_hash_func_two(str_sum);
	GItem* current_item = table->items[probe];

	// if no item existing, save the item directly.
	if (current_item == NULL)
	{
		if (table->count == table->size)
		{
			fail("Insert Error: Hash Table is full\n");
			g_free_item(item);
			return;
		}
		table->items[probe] = item;
		table->count++;
		return;
	}

	// replace item when the key is the same as existing item.
	if (strcmp(key, current_item->key) == 0)
	{

		table->items[probe]->data = data;
		g_free_item(item);
		return;
	}

	// handle key collision.
	while (table->items[probe] != NULL)
	{
		probe = (probe + offset) % table->size;
	}
	table->items[probe] = item;
	table->count++;
}

void* g_hashtable_get(char* key, GHashTable* table)
{
	unsigned long str_sum = g_sum_of_str((key));
	unsigned long probe = g_hash_func_one(str_sum);
	unsigned long offset = g_hash_func_two(str_sum);

	GItem* item = table->items[probe];
	if (item != NULL && strcmp(item->key, key) == 0)
		return item->data;

	while (1)
	{
		probe = (probe + offset) % table->size;
		item = table->items[probe];
		if (item != NULL && strcmp(item->key, key) == 0)
			return item->data;
	}
}