#include <multiboot.h>

// System Headers
#include "core/common.h"
#include "core/kscreen.h"

void kmain( void* mbd, unsigned int magic ){

	

	if ( magic != MULTIBOOT_HEADER_MAGIC )
	{
		/* Something went not according to specs. Print an error */
		/* message and halt, but do *not* rely on the multiboot */
		/* data structure. */
	}

	// ini_gdt();

	/* You could either use multiboot.h */
	/* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
	/* or do your offsets yourself. The following is merely an example. */ 
	char * boot_loader_name =(char*) ((long*)mbd)[16];
/*
	// Print a letter to screen to see everything is working:
	unsigned char *videoram = (unsigned char *) 0xb8000;
	videoram[0] = 65; // character 'A'
	videoram[1] = 0x07; // forground, background color.
*/
	kscreen_clear();
	// kscreen_write("Hello, world!");
	int test;
	kscreen_write("Booting Bacon v1.0 ...\n");
	kscreen_write("Current Stack Pointer Address: ");
	asm volatile("mov %%esp, %0": "=m"(test));
	kscreen_writeHex32( test );
}
