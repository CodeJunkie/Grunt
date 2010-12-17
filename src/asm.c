// Basic I/O Functions

#include <ktypes.h>

// A function to write a byte to a specified port
void outb( ushort port, byte value ) { 
	asm volatile( "outb %1, %0" : : "dN" (port), "a" (value) ); 
}

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

// Control Register R/W Functions

// Write
void kwrite_cr0( uint data ) {
	asm volatile( "movl %0, %%eax" : : "m" (data) );
	asm volatile( "movl %%eax, %%cr0" : : );
}

void kwrite_cr2( uint data ) {
	asm volatile( "movl %0, %%eax" : : "a" (data) );
	asm volatile( "movl %%eax, %%cr2" : : );
}

void kwrite_cr3( uint data ) {
	asm volatile( "movl %0, %%eax" : : "a" (data) );
	asm volatile( "movl %%eax, %%cr3" : : );
}

void kwrite_cr4( uint data ) {
	asm volatile( "movl %0, %%eax" : : "a" (data) );
	asm volatile( "movl %%eax, %%cr4" : : );
}

// Read
uint kread_cr0( ) {
	uint data = 0x0;
	asm volatile( "movl %%cr0, %%eax" : : );
	asm volatile( "movl %%eax, %0" : "=m" (data) : );
	return data;
}

uint kread_cr2( ) {
	uint data = 0x0;
	asm volatile( "movl %%cr2, %%eax" : : );
	asm volatile( "movl %%eax, %0" : "=m" (data) : );
	return data;
}

uint kread_cr3( ) {
	uint data = 0x0;
	asm volatile( "movl %%cr3, %%eax" : : );
	asm volatile( "movl %%eax, %0" : "=m" (data) : );
	return data;
}

uint kread_cr4( ) {
	uint data = 0x0;
	asm volatile( "movl %%cr4, %%eax" : : );
	asm volatile( "movl %%eax, %0" : "=m" (data) : );
	return data;
}

// =================================================================================
// = Interrupt Enabling and Disabling Functions
// =================================================================================
void kinterrupt_enable(){
	asm volatile( "sti" : : );
}

void kinterrupt_disable(){
	asm volatile( "cli" : : );
}





