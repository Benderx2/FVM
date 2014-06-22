#ifndef _MMGR_H
#define _MMGR_H
/** Memory Manager Struct **/
struct _VMHEAPENTRY {
	struct _VMHEAPENTRY* next;
	uint32_t start;
	uint32_t size;
	uint32_t used;
	uint32_t last;
};
typedef struct _VMHEAPENTRY V_HEAP_ENTRY_t;
/** Heap structure**/
struct V_HEAP {
	V_HEAP_ENTRY_t* fentry;
};
typedef struct V_HEAP V_HEAP_t;
#endif
