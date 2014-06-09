#ifndef __FV11_H
#define __FV11_H
struct FV11_HEADER 
{
	char[5] FV11_HEADER;
	uint32_t loadaddr;
	char[12] VENDOR_STRING;
};
typedef struct FV11_HEADER FV11_HEADER_t;
static const char[5] HEADER = 0x06, 'F', 'V', 'X' 
