// Common Kernel Functions
// Written by Travis Sharp - CodeJunkie

#include "common.h"

// A function to write a byte to a specified port
void outb( ushort port, byte value ) { asm volatile( "outb %1, %0" : : "dN" (port), "a" (value) ); }

// Read a byte from specified port
byte inb( ushort port ) {
	byte ret;
	asm volatile( "inb %1, %0" : "=a" (ret) : "dN" (port) );
	return ret;
}

// Read 2 bytes from specified port
ushort inw( ushort port ) {
	ushort ret;
	asm volatile( "inw %1, %0" : "=a" (ret) : "dN" (port) );
	return ret;
}
