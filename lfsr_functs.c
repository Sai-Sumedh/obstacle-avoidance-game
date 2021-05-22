#include <at89c5131.h>
/*#include "lcd.h"		// LCD interfacing
#include "serial.c" // UART interfacing
*/
// Goal: create a working LFSR and display its states on LCD

unsigned int update_lfsr(unsigned int lfsr_state)
{
	bit b0=0;
	bit b2 = 0;
	bit x=0;
	unsigned int bdata modified_state=0;
	
	b2 = (lfsr_state/4)%2;
	b0 = lfsr_state%2; 

	x = b0^b2; // b0 XOR b2
	modified_state = (lfsr_state>>1); //xb2b1 = (b2XORb0)b2b1
	modified_state = modified_state  + 4*x;
	return modified_state;
}


/*void display_state(lfsr_state)
{
	char Lstate[4]={0,0,0,'\0'};
	lcd_cmd(0x86); //7th column 1st row
	int_to_string(lfsr_state, Lstate);
	lcd_write_string(Lstate);
	msdelay(10);
	
}
*/