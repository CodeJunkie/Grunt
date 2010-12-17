#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// A struct describing an interrupt gate.  .... the data structure of an Interrupt Descriptor ...
struct _idt_entry_struct
{
   ushort 	base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   ushort 	sel;                 // Kernel segment selector.
   byte  	always0;             // This must always be zero.
   byte		flags;               // More flags. See documentation.
   ushort	base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));

// A generic Descriptor Pointer table structure
struct _desc_ptr_struct
{
   ushort 	limit;               // The upper 16 bits of all selector limits.
   uint 	base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));

typedef struct _idt_entry_struct idt_entry_t;
typedef struct _desc_ptr_struct desc_ptr_t;

#endif
