/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   UUID生成
**    Created Date:    2022-11-02
**    Updated Date:    2023-06-01
***********************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uuid.h"
#include "str.h"
#include "memory.h"

void read_urandom()
{
	FILE* fp;
	fp = fopen("/dev/urandom", "r");
	unsigned char buffer[8];
	fread(buffer, 8, 8, fp);
	for (int i = 0; i < 8; ++i)
		printf("%d\n", buffer[i]);
	printf("\n");
	fclose(fp);
}


byte* random_bytes(unsigned int size)
{
	unsigned int int_size = sizeof(int);
	unsigned int call_rand_amount = size / int_size;
	if (size % int_size != 0)
	{
		call_rand_amount++;
	}

	/*
	** create random bytes using rand(), store them to a buff.
	** the result bytes will be picked from it.
	*/
	// why define it as unsigned char, then all bytes is converted unsigned char automatically?
	unsigned char buff[call_rand_amount * int_size];
	unsigned char* cur = buff;
	for (int i = 0; i < call_rand_amount; i++)
	{
		int rand_number = rand();
		memcpy(cur, &rand_number, int_size);
		cur = cur + int_size;
	}
	buff[call_rand_amount * int_size] = '\0';

	// copy random bytes from temp random bytes buff array.
	unsigned char* bytes = (unsigned char*)g_malloc(size);
	for (int i = 0; i < size; i++)
	{
		bytes[i] = buff[i];
	}
	return bytes;
}

UUID* uuid4()
{
	byte* bytes = random_bytes(16);

	UUID* uuid = (UUID*)g_malloc(sizeof(UUID));
	uuid->time_low[0] = bytes[0];
	uuid->time_low[1] = bytes[1];
	uuid->time_low[2] = bytes[2];
	uuid->time_low[3] = bytes[3];
	uuid->time_mid[0] = bytes[4];
	uuid->time_mid[1] = bytes[5];
	uuid->time_hi_and_version[0] = bytes[6];
	uuid->time_hi_and_version[1] = (bytes[7] & 0x4f) | 0x40; // 0x4f: 01001111, 0x40: 01000000
	uuid->clk_seq_hi_reserved[0] = bytes[8];
	uuid->clk_seq_low[0] = bytes[9];
	uuid->node[0] = bytes[10];
	uuid->node[1] = bytes[11];
	uuid->node[2] = bytes[12];
	uuid->node[3] = bytes[13];
	uuid->node[4] = bytes[14];
	uuid->node[5] = bytes[15];

	g_free(to_void_ptr(&bytes));

	uuid->int_time_low = uuid->time_low[0] | uuid->time_low[1] << 8 | uuid->time_low[2] << 16 | uuid->time_low[3] << 24;
	uuid->int_time_mid = uuid->time_mid[0] | uuid->time_mid[1] << 8;
	uuid->int_time_hi_and_version = uuid->time_hi_and_version[0] | uuid->time_hi_and_version[1] << 8;
	uuid->int_clk_seq_hi_reserved = uuid->clk_seq_hi_reserved[0];
	uuid->int_clk_seq_low = uuid->clk_seq_low[0];
	// uuid->int_node = uuid->node[0] | uuid->node[1] << 8 | uuid->node[2] << 16 | uuid->node[3] << 24 | uuid->node[4] << 32 | uuid->node[5] << 40;

	char* buff_int_time_low = (char*)g_malloc(9);
	sprintf(buff_int_time_low, "%08x", uuid->int_time_low);

	char* buff_int_time_mid = (char*)g_malloc(5);
	sprintf(buff_int_time_mid, "%04x", uuid->int_time_mid);

	char* buff_int_time_hi_and_version = (char*)g_malloc(5);
	sprintf(buff_int_time_hi_and_version, "%04x", uuid->int_time_hi_and_version);

	char* buff_int_clk_seq_hi_reserved = (char*)g_malloc(3);
	sprintf(buff_int_clk_seq_hi_reserved, "%02x", uuid->int_clk_seq_hi_reserved);

	char* buff_int_clk_seq_low = (char*)g_malloc(3);
	sprintf(buff_int_clk_seq_low, "%02x", uuid->int_clk_seq_low);

	char* node = bytes_to_hex_str(uuid->node, 6);

	char* value = (char*)g_malloc(37);
	strcat(value, buff_int_time_low);
	strcat(value, "-");
	strcat(value, buff_int_time_mid);
	strcat(value, "-");
	strcat(value, buff_int_time_hi_and_version);
	strcat(value, "-");
	strcat(value, buff_int_clk_seq_hi_reserved);
	strcat(value, buff_int_clk_seq_low);
	strcat(value, "-");
	strcat(value, node);
	value[36] = '\0';

	char* hex = replace("-", "", value);

	char* urn = (char*)g_malloc(46);
	strcat(urn, "urn:uuid:");
	strcat(urn, value);
	urn[45] = '\0';

	uuid->value = value;
	uuid->urn = urn;
	uuid->hex = hex;
	uuid->version = 4;

	g_free(to_void_ptr(&buff_int_time_low));
	g_free(to_void_ptr(&buff_int_time_mid));
	g_free(to_void_ptr(&buff_int_time_hi_and_version));
	g_free(to_void_ptr(&buff_int_clk_seq_hi_reserved));
	g_free(to_void_ptr(&buff_int_clk_seq_low));
	g_free(to_void_ptr(&node));

	return uuid;
}

void free_uuid4(UUID* uuid)
{
	g_free(to_void_ptr(&(uuid->value)));
	g_free(to_void_ptr(&(uuid->hex)));
	g_free(to_void_ptr(&(uuid->urn)));
	g_free(to_void_ptr(&uuid));
}