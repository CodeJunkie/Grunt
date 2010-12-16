/*
 * entry32.S - Written by Travis Sharp, 12/13/2010
 * the entry point that grub pops us into
 */

#include <bootasm.h>

// setting up the Multiboot header - see GRUB docs for details
#define ALIGN    (1<<0)             // align loaded modules on page boundaries
#define MEMINFO  (1<<1)             // provide memory map
#define FLAGS    MEMINFO  			// this is the Multiboot 'flag' field
#define MAGIC    0x1BADB002       	// 'magic number' lets bootloader find the header
#define CHECKSUM -(MAGIC + FLAGS) 	// checksum required

.align 4
MULTIBOOT_HEADER:
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.code32
.text

.set STACKSIZE, 0x4000          // that is, 16k.
.comm stack, STACKSIZE, 32      // reserve 16k stack on a quadword boundary

.globl start
	.type start, @function

start:
	push	$0
	popf		// Reseting EFlags

	push %eax	// Grubs Return Magic Number
	push %ebx	// Struct Address

	call kmain	// This is where we call our kernel. Our kernel will then init itself

eok:
	hlt
	jmp eok
// =================================================================================

// =================================================================================
/*
 * Function: iniDescriptors
 *
 *
 * Description: This will setup and enable your initial GDT, IDT and TSS Descriptors
 * needed for 32bit mode. This will not setup paging, that will be done in C
 *
 */

.globl iniDescriptors
	.type iniDescriptors, @function
iniDescriptors:
	// Enter
	push %ebp		// Preserve calling functions stack
	mov %esp, %ebp	// Setup our own stack

	// Code0
	lgdt	gdtdesc

	mov $0, %eax	// Return 0
	// Exit
	mov	%ebp, %esp	// Reset the stack
	pop %ebp		// Restore original stack pointer
	ret
// =================================================================================

// GDT
.p2align 2                                // force 4 byte alignment
gdt:
  SEG_NULLASM                             // null seg
  SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)   // code seg
  SEG_ASM(STA_W, 0x0, 0xffffffff)         // data seg

gdtdesc:
  .word   (gdtdesc - gdt - 1)              // sizeof(gdt) - 1
  .long   gdt                             // address gdt
