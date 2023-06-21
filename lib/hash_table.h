/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    simple hash table, source code comes from
**                https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
**    创建日期：    2022-11-14
**    更新日期：    2022-11-14
***********************************************************************************************************************/
#ifndef OPENFMT_HASH_TABLE_H
#define OPENFMT_HASH_TABLE_H
#define CAPACITY 50000 // Size of the Hash Table

typedef struct Item Item;

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Define the Hash Table Item here
**    创建日期：    2022-10-26
**    更新日期：    2022-10-26
***********************************************************************************************************************/
struct Item
{
    char *key;
    void *value;
};

typedef struct HashTable HashTable;

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Define the Hash Table here
**    创建日期：    2022-10-26
**    更新日期：    2022-10-26
***********************************************************************************************************************/
struct HashTable
{
    // Contains an array of pointers to items
    Item **items;
    int size;
    int count;
};

unsigned long hash_function(char *str);

Item *create_item(char *key, char *value);

HashTable *create_table(int size);

void free_item(Item *item);

void free_table(HashTable *table);

void handle_collision(HashTable *table, unsigned long index, Item *item);

void ht_insert(HashTable *table, char *key, char *value);

char *ht_search(HashTable *table, char *key);

void print_search(HashTable *table, char *key);

void print_table(HashTable *table);

#endif //OPENFMT_HASH_TABLE_H