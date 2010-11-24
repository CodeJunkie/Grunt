#define bit(n) (1<<(n)) /* Set bit n to 1 */
#define ZERO_MASK 0x00000000
#define CR4_FLAGS (ZERO_MASK ^ (bit(7) | bit(5)))

.globl start                 # making entry point visible to linker

# setting up the Multiboot header - see GRUB docs for details
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    MEMINFO  	# this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum required

.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# reserve initial kernel stack space
.set STACKSIZE, 0x4000          # that is, 16k.
.comm stack, STACKSIZE, 32      # reserve 16k stack on a quadword boundary

start:
   mov   $(stack + STACKSIZE), %esp # set up the stack
   push  %eax                       # Multiboot magic number
   push  %ebx                       # Multiboot data structure

   // mov $CR4_FLAGS,%eax		# Set PAE and PGE /* Bits 5 & 7 enabled */
   // mov %eax,%cr4		// Move it into Control Reg 4

	cli
	lgdt 	(gdt_end)

   call  kmain            # call kernel proper

   cli
hang:
   hlt                    # halt machine should kernel return
   jmp   hang

.align 8
gdt:
	.quad 0x0000000000000000 # Our null descriptor
	                    
gdt_end:
	.word (gdt_end)-(gdt) 	// 16 Bit GDT Size
	.long (gdt)		// 32 Bit Addr - 64 for 64 Bit Mode
