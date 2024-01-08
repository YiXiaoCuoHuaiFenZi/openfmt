/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   simple hash table, source code comes from
**                     https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
**    Created Date:    2022-11-14
**    Updated Date:    2022-11-14
***********************************************************************************************************************/
#ifndef OPENFMT_G_HASH_TABLE_H
#define OPENFMT_G_HASH_TABLE_H
#define G_CAPACITY 991           // Size of the Hash Table
#define G_PRIME 7                // Used in second hash function

typedef struct GItem GItem;

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Define the hash table item.
**    Created Date:    2022-10-26
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
struct GItem
{
	char* key;                       // the hash key of the data.
	void* data;                      // data to be stored
	char* data_type;                 // data type of the stored data, used to convert the data to a solid data object.

	void (* data_free_func)(void*);  // the free call back method to free the data, used in free the whole hash table.
};

typedef struct GHashTable GHashTable;

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Define the hash table.
**    Created Date:    2022-10-26
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
struct GHashTable
{
	GItem** items;  // Contains an array of pointers to items
	int size;
	int count;
};

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   calculate the sum of ascii values of chars of the input string.
**    Parameters:      str: string to be calculated.
**                     return: sum of the chars of the string.
**    Created Date:    2022-06-21
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
unsigned long g_sum_of_str(const char* str);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   calculate the index in the hash table of the input string.
**    Parameters:      key_sum: ascii sum of the key.
**                     return: index in the hash table.
**    Created Date:    2022-06-21
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
unsigned long g_hash_func_one(unsigned long key_sum);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   calculate the offset of the key when has collision.
**    Parameters:      key_sum: ascii sum of the key.
**                     return: offset used to fix index collision.
**    Created Date:    2022-06-21
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
unsigned long g_hash_func_two(unsigned long key_sum);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   create generic has table item.
**    Parameters:      key: the key of the data.
**                     data_type: the data type of the data to be stored.
**                     data: the data to be stored.
**                     data_free_func: the pointer of the data free function.
**                     return: generic data item.
**    Created Date:    2022-06-21
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
GItem* g_create_item(const char* key, const char* data_type, void* data, void (* data_free_func)(void*));

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   free the generic item of the has table.
**    Parameters:      item: generic item to be freed.
**    Created Date:    2022-06-21
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
void g_free_item(GItem* item);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   create a generic hash table, init with a size.
**    Parameters:      size: initial size of the has table.
**                     return: created hash table pointer.
**    Created Date:    2022-06-21
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
GHashTable* g_create_hashtable(int size);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   put data to the hash table, if no data free function is not set, the data will not be freed when
**                     call the g_free_hashtable function.
**    Parameters:      key: the key of the data.
**                     data_type: the data type of the data to be stored.
**                     data: the data to be stored.
**                     data_free_func: the pointer of the data free function.
**                     return: none.
**    Created Date:    2022-06-21
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
void g_hashtable_put(char* key, const char* data_type, void* data, void (* data_free_func)(void*), GHashTable* table);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   get data from the hash table by key.
**    Parameters:      key: the key used to find the data.
**                     table: target has table where data to find from.
**                     return: generic pointer of the data.
**    Created Date:    2022-06-21
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
void* g_hashtable_get(char* key, GHashTable* table);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   free the hash table including the data field, the data is freed by the call back free function.
**    Parameters:      key: the key used to find the data.
**                     table: target has table where data to find from.
**                     return: generic pointer of the data.
**    Created Date:    2022-06-21
**    Updated Date:    2022-10-26
***********************************************************************************************************************/
void g_free_hashtable(GHashTable* table);

#endif //OPENFMT_G_HASH_TABLE_H
