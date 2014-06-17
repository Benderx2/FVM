#ifndef __FV11_H
#define __FV11_H
// 24-byte FV11 Header.
struct FV11_HEADER 
{
	/* FV11 Header */
	uint32_t MAGIC;
	/* 11-byte Vendor String */
	char VENDOR_STRING[12];
	/* Pointer to start MUST be 4-bytes aligned OR FAIL */
	uint32_t start_function;
	/* Time stamp */
	uint32_t timestamp;
}__attribute__((packed)); // Oh, please GCC don't align this header.
typedef struct FV11_HEADER FV11_HEADER_t;
/* FVM Executable Header */
#define FVM_MAGIC_HEADER 0x1D4ED43B;
#endif

