#ifndef __STACK_H
#define __STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define DEFAULT_STACK_SIZE 100 * sizeof(int)
typedef struct __stack {
	int* content;
	int no;
} __stack_t;
typedef __stack_t v_stack;
typedef struct __stack_construct {
	v_stack* (*Create)(void);
	int (*Push)(v_stack*, int);
	int (*Pop)(v_stack*);
	int (*Duplicate)(v_stack*);
	int (*GetItem)(v_stack*, int);
} __stack_construct;
__stack_construct Stack;
void init_stack(void);
#endif
