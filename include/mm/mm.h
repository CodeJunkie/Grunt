#ifndef _MM_H
#define _MM_H

#include <types.h>

#define MAX_GDT_DESCRIPTORS 8

// Generic Descriptor Structure
struct _gen_descriptor{
	ushort lower16;
	ushort upper16;
	ushort base_addr;
	ushort seg_limit;
};

typedef struct _gen_descriptor gdt_desc;

void ini_gdt();
void update_gdt();

#endif
