/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-11-02
**    更新日期：    2022-11-02
***********************************************************************************************************************/
#ifndef OPENFMT_UUID_H
#define OPENFMT_UUID_H

#include "type.h"

struct UUID_;
typedef struct UUID_ UUID;
/***********************************************************************************************************************
**              https://www.rfc-editor.org/rfc/rfc4122
**                       Layout and Byte Order
**
** 0                   1                   2                   3
**  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
** +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
** |                          time_low                             |
** +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
** |       time_mid                |         time_hi_and_version   |
** +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
** |clk_seq_hi_res |  clk_seq_low  |         node (0-1)            |
** +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
** |                         node (2-5)                            |
** +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
***********************************************************************************************************************/
struct UUID_
{
	byte time_low[4];
	byte time_mid[2];
	byte time_hi_and_version[2];
	byte clk_seq_hi_reserved[1];
	byte clk_seq_low[1];
	byte node[6];

	unsigned int int_time_low;
	unsigned int int_time_mid;
	unsigned int int_time_hi_and_version;
	unsigned int int_clk_seq_hi_reserved;
	unsigned int int_clk_seq_low;
	unsigned int int_node;                // no int which size is 18 bits, don't define it.

	unsigned short int version;
	char* value;                          // f81d4fae-7dec-11d0-a765-00a0c91e6bf6
	char* hex;                            // f81d4fae7dec11d0a76500a0c91e6bf6
	char* urn;                            // urn:uuid:f81d4fae-7dec-11d0-a765-00a0c91e6bf6
};

void read_urandom();

byte* random_bytes(unsigned int byte_size);

UUID* uuid4();

void free_uuid4(UUID* uuid);

#endif //OPENFMT_UUID_H
