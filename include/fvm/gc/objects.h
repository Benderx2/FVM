#ifndef __OBJECTS_H
#define __OBJECTS_H
#include <stdint.h>
#include <stdbool.h>
#define IS_MARKED 1
#define IS_UNMARKED 0
#define OBJ_IDLE 0
#define FLOAT_TYPE 1
#define INT_TYPE 2
#define STRING_TYPE 3
typedef struct sObject {
	unsigned char marked;
	unsigned int type;
	int index;
	uint32_t value;
	struct sObject* prev;
	struct sObject* next;
} Object;
Object* VM_CreateObject(int type, uint32_t value);
int VM_DestroyObject(int objnum);
int getnumberofObjects(void);
Object* gettail(void);
Object* gethead(void);
Object* getObjectbyindex(int index);
bool ismarked(Object* object);
#endif
