#ifndef COMMON_H
#define COMMON_H

typedef unsigned int 	uint;	// 32-bit unsigned int - 4 bytes
typedef unsigned short 	ushort;	// 16-bit unsigned int - 2 bytes
typedef	unsigned char 	byte;	// 8bits, a single Byte

void outb(ushort port, byte value);	// Used to send a byte to hardware
byte inb(ushort port);			// Read a byte from hardware
ushort inw(ushort port);		// Read 2 bytes from hardware

#endif
