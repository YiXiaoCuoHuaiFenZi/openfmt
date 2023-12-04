/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-11-23
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_G_HASH_TABLE_H
#define OPENFMT_G_HASH_TABLE_H
#define G_CAPACITY 50000 // Size of the Hash Table
#define G_PRIME 4997     // Used in second hash function

typedef struct GItem GItem;

// Define the Hash Table GItem here
struct GItem
{
	char* key;
	void* data;
	char* data_type;

	void (* data_free_func)(void*);
};

typedef struct GHashTable GHashTable;

struct GHashTable
{
	GItem** items;  // Contains an array of pointers to items
	int size;
	int count;
};

unsigned long g_sum_of_str(const char* str);

unsigned long g_hash_func_one(unsigned long key);

unsigned long g_hash_func_two(unsigned long key);

GItem* g_create_item(const char* key, const char* data_type, void* data, void (* data_free_func)(void*));

void g_free_item(GItem* item);

GHashTable* g_create_hashtable(int size);

void g_hashtable_put(char* key, const char* data_type, void* data, void (* data_free_func)(void*), GHashTable* table);

void* g_hashtable_get(char* key, GHashTable* table);

void g_free_hashtable(GHashTable* table);

#endif //OPENFMT_G_HASH_TABLE_H
