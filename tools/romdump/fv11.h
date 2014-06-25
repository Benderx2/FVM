#ifndef __FV11_H
#define __FV11_H
#include <stdint.h>
struct FV11_HEADER {
	int32_t magic;
	int32_t start_addr;
	int32_t where_to_load;
	int32_t length_of_text;
	int32_t start_of_data;
	int32_t where_to_load_data;
	int32_t length_of_data;
	int32_t bss_start;
	int32_t bss_length;
	int32_t stack_buf;
	char vendorstring[8];
};
typedef struct FV11_HEADER FV11_HEADER_t;
static const int FV11_MAGIC = 0xC00C1E5;
#endif
	
