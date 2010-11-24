#include <types.h>
#include <mm/mm.h>
#include <cpu/cpu.h>

// Interrupts
void cpu_disable_interrupts(){ asm("cli"); } // Disable Interrupts
void cpu_enable_interrupts(){ asm("sti"); } // Enable Interuupts

// Memory Stuff
void cpu_set_gdt( gdt_desc *gdt, ushort count ){

	lgdt_data lgdt;

	lgdt.size = ((count*sizeof(gdt_desc))+sizeof(gdt_desc));
	lgdt.gdt_data = &gdt;

	cpu_disable_interrupts();
	asm( "lgdt %0" : : "m" (lgdt));
	cpu_enable_interrupts();

}
