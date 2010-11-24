#include <types.h>
#include <mm/mm.h>
#include <cpu/cpu.h>

ushort _gdt_count;

gdt_desc gdt[MAX_GDT_DESCRIPTORS];

void ini_gdt(){

	_gdt_count = 0; // Set our gdt descriptor counter

	// Create our null descriptor
	gdt[0].lower16 = 	0x00000000;
	gdt[0].upper16 = 	0x00000000;
	gdt[0].base_addr =	0x00000000;
	gdt[0].seg_limit =	0x00000000;	

	// Update the CPU GDT
	update_gdt();
}

void update_gdt(){
	// Tell the cpu to accept our current GDT
	cpu_set_gdt( gdt, _gdt_count );	
}
