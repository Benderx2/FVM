/** Class Loader header file **/
#ifndef __CLASSLOADER_H
#define __CLASSLOADER_H
struct classloader_header {
	uint32_t MAGIC;
	uint32_t nfunctions;
};
static const int MAGIC = 0xC0C0A;
struct class_header {
	char name[64];
	uint32_t offset;
};
typedef struct classloader_header classloader_header_t;
#endif
