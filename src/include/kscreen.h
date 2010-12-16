/*
File:	kscreen.h
Author: Travis Sharp
Date:	12/7/10
Purpose: This is effectively a basic kernel level video driver. This will hopefully
	be replaced with a VESA graphics version in the somewhat near future. Or when
	needed; however, memory management is a bit more important than VESA.

TODO: Write a VESA Version

*/

#ifndef KSCREEN_H
#define KSCREEN_H

void kscreen_putch( char c ); 	// Write a single character to the screen
void kscreen_clear();		// Clear the screen
void kscreen_write( char *c );	// Writr a null-terminated ASCII String to the Screen ( an asm equivalent to .string )

void kscreen_writeHex32( int n );	// Write a number out in 32-bit hex
void kscreen_writeNum32( int n );	// Write a 32-Bit number out 

void kscreen_writeHex64( long long n );	// Write a number out in 64-bit hex
void kscreen_writeNum64( long long n ); // Write a 64-Bit number out

#endif
