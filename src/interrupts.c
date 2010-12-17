#include <ktypes.h>
#include <kcommon.h>
#include <kscreen.h>
#include <descriptors.h>

idt_entry_t	k_idt[32];
desc_ptr_t	k_idt_ptr;

// Write len copies of val into dest.
void memset(byte *dest, byte val, uint len)
{
    byte *temp = (byte *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

static void idt_set_gate(byte num, uint base, ushort sel, byte flags)
{
    k_idt[num].base_lo = base & 0xFFFF;
    k_idt[num].base_hi = (base >> 16) & 0xFFFF;

    k_idt[num].sel     = sel;
    k_idt[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    k_idt[num].flags   = flags /* | 0x60 */;
}

void generic_interrupt(){
	kinterrupt_disable();
	kscreen_write( "YO, I'm an unhandled interrupt ..." );
	kinterrupt_enable();
}

void kini_idt(){

	kscreen_write( "Entering idt init...\n");

	// Setup some space and values
	k_idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    k_idt_ptr.base  = (uint)&k_idt;

	kscreen_write( "memset...\n");
    memset(&k_idt, 0, sizeof(idt_entry_t)*256);

	// Make Sure that interrups are indeed disabled.	
	kinterrupt_disable();

	// We need to do a malloc here for k_idt, or it won't get allocated
	// and the program will probably throw a segmentation fault thus
	// causing the machine to tripple-fault for not having an appropriate
	// interrupt handler .... or it wont do anytihng. Lol.

	int i;

	for( i = 0; i < 32; i++ ){
		kscreen_write( "Setting up interrupt #");
		kscreen_writeHex32( i );
		kscreen_write( "\n" );
		idt_set_gate( i, (uint)generic_interrupt , 0x10, 0x8E);
	}
	
	kscreen_write( "enabling interrupts");
	// After setting up our IDT, we should be able to do this...
	kinterrupt_enable();
}


