/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-11-23
**    更新日期：    2022-11-23
***********************************************************************************************************************/
#ifndef OPENFMT_G_HASH_TABLE_H
#define OPENFMT_G_HASH_TABLE_H
#define G_CAPACITY 50000 // Size of the Hash Table

typedef struct GItem GItem;

// Define the Hash Table GItem here
struct GItem
{
    char *key;
    void *data;
    char *data_type;

    void (*data_free_func)(void *);
};

typedef struct GHashTable GHashTable;

struct GHashTable
{
    GItem **items;  // Contains an array of pointers to items
    int size;
    int count;
};

unsigned long HashFunc(const char *str);

GItem *CreateGItem(const char *key, const char *data_type, void *data, void (*data_free_func)(void *));

void FreeGItem(GItem *item);

GHashTable *CreateGHashTable(int size);

void GHashTablePut(char *key, const char *data_type, void *data, void (*data_free_func)(void *), GHashTable *table);

void *GHashTableGet(char *key, GHashTable *table);

void FreeGHashTable(GHashTable *table);

#endif //OPENFMT_G_HASH_TABLE_H
