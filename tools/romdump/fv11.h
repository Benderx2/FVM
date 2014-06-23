#ifndef __FV11_H
#define __FV11_H
#include <stdint.h>
struct FV11_HEADER {
	uint32_t magic;
	uint32_t start_addr;
	uint32_t where_to_load;
	uint32_t length_of_text;
	// 8-byte vendor string
	char vendorstring[8];
};
typedef struct FV11_HEADER FV11_HEADER_t;
static const int FV11_MAGIC = 0xC00C1E5;
#endif
	
