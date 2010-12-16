/*
File:	kmain.c
Author: Travis Sharp
Date:	12/14/10
Purpose: This is the main entry point for the kernel. This will setup the GDT,
	IDT, TSS, Paging ... etc. that the system will need. The paging mechanism
	will be a fairly compilcated system due to the plan of having an interface
	mechanism to the paging system running as a user process. There will be an
	underlying system that will check for user and process privlege levls.

*/

#include <ktypes.h>
#include <kcommon.h>
#include <kscreen.h>

void kmain( uint magic, uint* multibootData ) {
	kscreen_clear();
	kscreen_write("booting mini-me.bin ...\n");
	kscreen_writeHex32( kread_cr0() );
	kscreen_write("\n");
	kwrite_cr0( (0xFFFFFFFE & kread_cr0()) );
	kscreen_writeHex32( kread_cr0() );
	kwrite_cr0( (0x00000001 | kread_cr0()) );
	kscreen_write("\n");
	kscreen_writeHex32( kread_cr0() );
	
	kwrite_cr0( (0x00000001 | kread_cr0()) );
	//kwrite_cr1( (0x00000001 | kread_cr1()) );
	kwrite_cr2( (0x00000001 | kread_cr2()) );
	kwrite_cr3( (0x00000001 | kread_cr3()) );
	kwrite_cr4( (0x00000001 | kread_cr4()) );

}
