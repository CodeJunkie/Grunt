#ifndef _CPU_H
#define _CPU_H

#include <types.h>
#include <mm/mm.h>

void cpu_disable_interrupts();
void cpu_enable_interrupts();
void cpu_set_gdt( gdt_desc gdt[MAX_GDT_DESCRIPTORS], ushort count );

struct _lgdt_data {
	ushort size; 
	long long gdt_data;
};

typedef struct _lgdt_data lgdt_data;

#endif
