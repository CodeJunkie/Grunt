/*
	File:	kcommon.h
	Author: Travis Sharp
	Date:	12/14/10
	Purpose: Common Core Kernel Subroutine Prototypes +Core Data Structures

*/

#ifndef KCOMMON_H
#define KCOMMON_H



// asm.c

void outb( ushort port, byte value ) ;
byte inb( ushort port );
ushort inw( ushort port );

// TODO: Write data structures to represent each control register

void kwrite_cr0( uint data );
void kwrite_cr1( uint data );
void kwrite_cr2( uint data );
void kwrite_cr3( uint data );
void kwrite_cr4( uint data );

uint kread_cr0( );
uint kread_cr1( );
uint kread_cr2( );
uint kread_cr3( );
uint kread_cr4( );

#endif
