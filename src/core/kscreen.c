/*
File:	kscreen.c
Author: Travis Sharp
Date:	12/7/10
Based off of code found at www.jamesmolloy.co.uk
Consult the header file for more details
*/

#include "kscreen.h"

/* Cursor Location */
ushort *video_memory = (ushort *)0xB8000;
byte cursor_x = 0;
byte cursor_y = 0;

/* Other Misc Screen Utility Functions */

// Update the hardware cursor.
static void move_cursor()
{
   // The screen is 80 characters wide...
   ushort cursorLocation = cursor_y * 80 + cursor_x;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line.
static void scroll()
{

   // Get a space character with the default colour attributes.
   byte attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   ushort blank = 0x20 /* space */ | (attributeByte << 8);

   // Row 25 is the end, this means we need to scroll up
   if(cursor_y >= 25)
   {
       // Move the current text chunk that makes up the screen
       // back in the buffer by a line
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           video_memory[i] = video_memory[i+80];
       }

       // The last line should now be blank. Do this by writing
       // 80 spaces to it.
       for (i = 24*80; i < 25*80; i++)
       {
           video_memory[i] = blank;
       }
       // The cursor should now be on the last line.
       cursor_y = 24;
   }
}

void kscreen_putch( char c ){
   // The background colour is black (0), the foreground is white (15).
   byte backColour = 0;
   byte foreColour = 15;

   // The attribute byte is made up of two nibbles - the lower being the
   // foreground colour, and the upper the background colour.
   byte  attributeByte = (backColour << 4) | (foreColour & 0x0F);
   // The attribute byte is the top 8 bits of the word we have to send to the
   // VGA board.
   ushort attribute = attributeByte << 8;
   ushort *location;

   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
   }

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == 0x09)
   {
       cursor_x = (cursor_x+8) & ~(8-1);
   }

   // Handle carriage return
   else if (c == '\r')
   {
       cursor_x = 0;
   }

   // Handle newline by moving cursor back to left and increasing the row
   else if (c == '\n')
   {
       cursor_x = 0;
       cursor_y++;
   }
   // Handle any other printable character.
   else if(c >= ' ')
   {
       location = video_memory + (cursor_y*80 + cursor_x);
       *location = c | attribute;
       cursor_x++;
   }

   // Check if we need to insert a new line because we have reached the end
   // of the screen.
   if (cursor_x >= 80)
   {
       cursor_x = 0;
       cursor_y ++;
   }

   // Scroll the screen if needed.
   scroll();
   // Move the hardware cursor.
   move_cursor();
}

void kscreen_clear(){
   // Make an attribute byte for the default colours
   byte attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   ushort blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++) video_memory[i] = blank; // This is a 1-line-loop

   // Move the hardware cursor back to the start.
   cursor_x = 0;
   cursor_y = 0;
   move_cursor();
}

void kscreen_write( char *c ){
   int i = 0;
   while (c[i]) kscreen_putch(c[i++]); // This is a 1-line-loop
}

// These Functions I have written myself.
void kscreen_writeHex32( int n ){
	char hexStr[10];	// We will always print 10 Characters for a Hex number
	hexStr[0] = '0';
	hexStr[1] = 'x';

	// There are 8 4-bit groupings per 32-bit Hex Number
	// So we need to loop 8 times to do this
	int i;
	for( i = 0; i < 8; i++ ){
		int shift = i*4;	// so S=(4K), S = Sigma, 7 is max, k starts at 0
		int tmp = n >> shift;	// Shift the bits according to the iteration
		tmp = tmp & 0x0000000F;	// Do an AND Mask to only keep the bottom 4 bits
		
		// NOTE: The weird 9-i thing is that the above stuff actually parses it backwards?
		// I recall something fuzzy about edianess ... or maby im doing something wrong ...
		// Lolz, it has to deal with the mask and shifting. Im testing starting with the LSB...
		// so yes, it will look reversed if I don't account for it.
		// TODO: See if I can optimize this function.
		switch( tmp ){
			case 0:
				hexStr[(9-i)] = '0';
				break;
			case 1:
				hexStr[(9-i)] = '1';
				break;
			case 2:
				hexStr[(9-i)] = '2';
				break;
			case 3:
				hexStr[(9-i)] = '3';
				break;
			case 4:
				hexStr[(9-i)] = '4';
				break;
			case 5:
				hexStr[(9-i)] = '5';
				break;
			case 6:
				hexStr[(9-i)] = '6';
				break;
			case 7:
				hexStr[(9-i)] = '7';
				break;
			case 8:
				hexStr[(9-i)] = '8';
				break;
			case 9:
				hexStr[(9-i)] = '9';
				break;
			case 10:
				hexStr[(9-i)] = 'A';
				break;
			case 11:
				hexStr[(9-i)] = 'B';
				break;
			case 12:
				hexStr[(9-i)] = 'C';
				break;
			case 13:
				hexStr[(9-i)] = 'D';
				break;
			case 14:
				hexStr[(9-i)] = 'E';
				break;
			case 15:
				hexStr[(9-i)] = 'F';
				break;
		} // End of long switch
	}
	// We Finish by writing it to the screen.	
	kscreen_write( hexStr );
}










