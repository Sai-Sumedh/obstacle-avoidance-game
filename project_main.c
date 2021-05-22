#include <at89c5131.h>
#include "lcd.h"		// LCD interfacing
#include "serial.c" // UART interfacing
#include "lfsr_functs.c" // LFSR functions
#include "obstacles_functs.c" // functions to display, move obstacles
#include "moved_functs.c" //functions to move the dinosaur
#include "collision_functs.c" //functions to deal with collisions

unsigned int D_pos=1;
unsigned int pos[7] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}; // since 7 different obstacles
unsigned int score_and_hs[2]={0,0}; //score_and_hs[0] is the score, while score_and_hs[1] is the high score 
unsigned int state_new_disp=0; // when 0, initialize a new obstacle, else just move everything left

void main(void) 
	{
	//initialize variables
	unsigned int bdata lfsr_state=0x01; 
	unsigned int lfsr_all[7] = {0x01, 0x04, 0x06, 0x07,0x02, 0x03, 0x05};
	//initialize lcd and serial comm.
	lcd_init();
	uart_init();

	while(1)		
	{
		update_obstacle_positions(pos, &lfsr_state, state_new_disp, lfsr_all);
		display_all(pos, &D_pos, score_and_hs, &state_new_disp);
		score_and_hs[0] = score_and_hs[0]+1; //update score
		state_new_disp = (state_new_disp+1)%3;
	}
	}
	
void serial_ISR_D(void) interrupt 4
{
		if(TI==1)			//check whether TI is set
		{
			TI = 0;			//Clear TI flag
			tx_complete = 1;	//Set tx_complete flag indicating interrupt completion
		}
		else if(RI==1)			//check whether RI is set
		{
			RI = 0;			//Clear RI flag
			//rx_complete = 1;	//Set rx_complete flag indicating interrupt completion
			move_D(pos, &D_pos, score_and_hs, &state_new_disp);	
		}
}

