/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-11-14
**    Updated Date:    2022-11-14
***********************************************************************************************************************/
#include "../../lib/hash_table.h"
#include "test_hash_table.h"

int test_hash_table()
{
	HashTable* ht = create_table(CAPACITY);
	ht_insert(ht, "1", "First address");
	ht_insert(ht, "2", "Second address");
	print_search(ht, "1");
	print_search(ht, "2");
	print_search(ht, "3");
	print_table(ht);
	free_table(ht);
	return 0;
}