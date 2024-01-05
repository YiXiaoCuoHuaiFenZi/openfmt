/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   simple hash table implementation.
**    Created Date:    2022-11-14
**    Updated Date:    2023-06-01
***********************************************************************************************************************/
#include "hash_table.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash_function(char* str)
{
	unsigned long i = 0;
	for (int j = 0; str[j]; j++)
		i += str[j];
	return i % CAPACITY;
}

Item* create_item(char* key, char* value)
{
	// Creates a pointer to a new hash table item
	Item* item = (Item*)g_malloc(sizeof(Item));
	item->key = (char*)g_malloc(strlen(key) + 1);
	item->value = (char*)g_malloc(strlen(value) + 1);

	strcpy(item->key, key);
	strcpy(item->value, value);

	return item;
}

HashTable* create_table(int size)
{
	// Creates a new HashTable
	HashTable* table = (HashTable*)g_malloc(sizeof(HashTable));
	table->size = size;
	table->count = 0;
	table->items = (Item**)calloc(table->size, sizeof(Item*));
	for (int i = 0; i < table->size; i++)
	{
		table->items[i] = NULL;
	}

	return table;
}

void free_item(Item* item)
{
	// Frees an item
	g_free(to_void_ptr(&(item->key)));
	g_free(to_void_ptr(&(item->value)));
	g_free(to_void_ptr(&item));
}

void free_table(HashTable* table)
{
	// Frees the table
	for (int i = 0; i < table->size; i++)
	{
		Item* item = table->items[i];
		if (item != NULL)
		{
			free_item(item);
		}
	}

	g_free(to_void_ptr(&(table->items)));
	g_free(to_void_ptr(&table));
}

void handle_collision(HashTable* table, unsigned long index, Item* item)
{
}

void ht_insert(HashTable* table, char* key, char* value)
{
	// Create the item
	Item* item = create_item(key, value);

	// Compute the index
	unsigned long index = hash_function(key);

	Item* current_item = table->items[index];

	if (current_item == NULL)
	{
		// Key does not exist.
		if (table->count == table->size)
		{
			// Hash Table Full
			printf("Insert Error: Hash Table is full\n");
			// Remove the created item
			free_item(item);
			return;
		}

		// Insert directly
		table->items[index] = item;
		table->count++;
	}
	else
	{
		// Scenario 1: We only need to update value
		if (strcmp(current_item->key, key) == 0)
		{
			strcpy(table->items[index]->value, value);
			return;
		}
		else
		{
			// Scenario 2: Collision
			// We will handle case this a bit later
			handle_collision(table, index, item);
			return;
		}
	}
}

char* ht_search(HashTable* table, char* key)
{
	// Searches the key in the hashtable
	// and returns NULL if it doesn't exist
	unsigned long index = hash_function(key);
	Item* item = table->items[index];

	// Ensure that we move to a non-NULL item
	if (item != NULL)
	{
		if (strcmp(item->key, key) == 0)
			return item->value;
	}
	return NULL;
}

void print_search(HashTable* table, char* key)
{
	char* val;
	if ((val = ht_search(table, key)) == NULL)
	{
		printf("Key:%s does not exist\n", key);
		return;
	}
	else
	{
		printf("Key:%s, Value:%s\n", key, val);
	}
}

void print_table(HashTable* table)
{
	printf("\nHash Table\n-------------------\n");
	for (int i = 0; i < table->size; i++)
	{
		if (table->items[i])
		{
			printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, (char*)(table->items[i]->value));
		}
	}
	printf("-------------------\n\n");
}