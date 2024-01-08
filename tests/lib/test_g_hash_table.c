/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-11-14
**    Updated Date:    2022-11-14
***********************************************************************************************************************/
#include <string.h>
#include "../macro.h"
#include "../../lib/g_hash_table.h"
#include "test_g_hash_table.h"

int test_g_hash_table()
{
	GHashTable* ht = g_create_hashtable(G_CAPACITY);
	g_hashtable_put("1", "char", "First address", NULL, ht);
	g_hashtable_put("2", "char", "Second address", NULL, ht);

	// test for collision handle.
	g_hashtable_put("ab", "char", "ab address", NULL, ht);
	g_hashtable_put("ba", "char", "ba address", NULL, ht);

	char* v1 = g_hashtable_get("1", ht);
	char* v2 = g_hashtable_get("2", ht);
	char* v3 = g_hashtable_get("ab", ht);
	char* v4 = g_hashtable_get("ba", ht);

	if (strcmp(v1, "First address") != 0)
		return TEST_FAIL;
	if (strcmp(v2, "Second address") != 0)
		return TEST_FAIL;
	if (strcmp(v3, "ab address") != 0)
		return TEST_FAIL;
	if (strcmp(v4, "ba address") != 0)
		return TEST_FAIL;

	g_free_hashtable(ht); // TODO seems the table its self(ht) is not be set to NULL.
	return TEST_SUCCESS;
}