.SUFFIXES: .S

CFLAGS=-m32 -g -ffreestanding -nostdlib -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -nostdinc -fno-builtin -nostartfiles -nodefaultlibs
INCLUDES=-Iinclude

OBJS=entry32.o asm.o kscreen.o kmain.o

# defines
LDSCRIPT=link.ld
LD	=ld -g -nostdlib -nodefaultlibs -T $(LDSCRIPT)

CC=gcc $(INCLUDES) $(CFLAGS)

# targets
all: mini-me.bin

install:

clean:
	@echo "Sanitizing machine code ..."
	@rm -f *.o mini-me.bin

start:
	@make clean
	@make
	@./start-vm

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o:	%.S
	$(CC) $(CFLAGS) -c $< -o $@

mini-me.bin: $(OBJS) $(LDSCRIPT) $(HEADERS)
	@echo "Compiling ..."
	$(LD) -o $@ $(OBJS)
	@echo "Installing ..."
	@cp mini-me.bin virtualDrive/boot/mini-me.bin
	@echo "Flush kernel disk caches ..."
	@sync
	@echo "Done!"
	@# echo "Done Compiling! ...\nCreating bootable floppy image ..."
	@#./sign.pl mini-me.bin # We dont need to sign it
	@# dd bs=510-`ls -l mini-me.bin | ls -l mini-me.bin | cut -d' ' -f5` count=1 if=/dev/zero of=blankIt.img
	@# dd bs=512 count=2879 if=/dev/zero of=bootFloppyBLANK.img <- this creates a new RAW image
	@# rm -f bootFloppy.img
	@# cp mini-me.bin bootFloppy.img				# Prep for meshing
	@# cat bootFloppyBLANK.img >> bootFloppy.img	# mashem together
	@# echo "Bootable floppy image created ... bootFloppy.img"
