/* definitions needed in malloc.c and realloc.c */

#define MALLOC_ALIGNMENT 8

struct mem_chunk 
{
	long valid;
#define VAL_FREE  0xf4ee0abcL
#define VAL_ALLOC 0xa11c0abcL
#define VAL_BORDER 0xb04d0abcL

	struct mem_chunk *next;
	unsigned long size;
};
#define ALLOC_SIZE(ch) (*(long *)((char *)(ch) + sizeof(*(ch))))
#define BORDER_EXTRA ((sizeof(struct mem_chunk) + sizeof(long) + (MALLOC_ALIGNMENT - 1)) & ~(MALLOC_ALIGNMENT - 1))

/* linked list of free blocks */
extern struct mem_chunk _mchunk_free_list;
