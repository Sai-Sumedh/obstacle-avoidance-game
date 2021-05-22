#include <at89c5131.h>
/*#include "lcd.h"		// LCD interfacing
#include "serial.c" // UART interfacing
#include "lfsr_functs.c" // LFSR code
*/

/* Goals: 
1. create 7 kinds of obstacles, display on LCD
2. make each obstacle move left by one column once per second
*/
void update_obstacle_positions(unsigned int pos[],unsigned int *lfsr_state,unsigned int state_new_disp, unsigned int lfsr_all[])
{
	int i;
	int j;
	if (state_new_disp==0) // need to display a new obstacle at the right end
			{
				*lfsr_state = update_lfsr(*lfsr_state);
				
				for (i=0; i<7; i++)	
				{
					if (*lfsr_state==lfsr_all[i])
					{
						pos[i]=16;
					}
				}
			}
			for (j=0;j<7;j++)
			{
				if (pos[j]<=16)
				{
					pos[j] = pos[j]-1; //move 1 step left
					if (pos[j]<0)
					{
						pos[j]=0x20;//back to default
					}
				}
			}
}



/*void obst(unsigned int global_pos, unsigned int obst_id)
{
	// obstacle:
	// 0**
	// 000
	
	unsigned int start_loc1 = 0;
	unsigned int start_loc2 = 0;

	switch (obst_id)
	{
		case 0:
			start_loc1 = 0x80 + global_pos;
			lcd_cmd(start_loc1);
			lcd_write_string(" **");
			
			start_loc2 = 0xC0 + global_pos;
			lcd_cmd(start_loc2);
			lcd_write_string("   ");
			break;
		case 1:
			start_loc1 = 0x80 + global_pos;
			lcd_cmd(start_loc1);
			lcd_write_string("   ");
			
			start_loc2 = 0xC0 + global_pos;
			lcd_cmd(start_loc2);
			lcd_write_string(" **");	
			break;
		case 2:
			start_loc1 = 0x80 + global_pos;
			lcd_cmd(start_loc1);
			lcd_write_string(" * ");
			
			start_loc2 = 0xC0 + global_pos;
			lcd_cmd(start_loc2);
			lcd_write_string("   ");
			break;
		
		case 3:
			start_loc1 = 0x80 + global_pos;
			lcd_cmd(start_loc1);
			lcd_write_string("   ");
			
			start_loc2 = 0xC0 + global_pos;
			lcd_cmd(start_loc2);
			lcd_write_string("  *");			
			break;
		case 4:
			start_loc1 = 0x80 + global_pos;
			lcd_cmd(start_loc1);
			lcd_write_string("   ");
			
			start_loc2 = 0xC0 + global_pos;
			lcd_cmd(start_loc2);
			lcd_write_string(" * ");
			break;
		case 5:
			start_loc1 = 0x80 + global_pos;
			lcd_cmd(start_loc1);
			lcd_write_string("  *");
			
			start_loc2 = 0xC0 + global_pos;
			lcd_cmd(start_loc2);
			lcd_write_string("   ");			
			break;
		case 6:
			start_loc1 = 0x80 + global_pos;
			lcd_cmd(start_loc1);
			lcd_write_string("   ");
			
			start_loc2 = 0xC0 + global_pos;
			lcd_cmd(start_loc2);
			lcd_write_string("   ");	
			break;
		
	}
	
}


*/
