#include <at89c5131.h>

// Goal: Achieve control of D using keyboard


/* 
Steps: 
display D at (1, 3) on LCD
if keyboard input is q or a
and position is down or up, 
move to other position
*/


/*void show_player_up(void){
	
	//lcd_cmd(0x01); // clear screen- this cant be used when other components exist on screen which are not to be disturbed
	lcd_cmd(0x82); // 3rd column of 1st row
	lcd_write_string("D");
	msdelay(10);
	
	
}
void show_player_down(void){
	
	//lcd_cmd(0x01); // clear screen- this cant be used when other components exist on screen which are not to be disturbed
	lcd_cmd(0xC2); // 3rd column of 2nd row
	lcd_write_string("D");
	msdelay(10);
	
	
}*/

void show_player(unsigned int D_pos)
{
	lcd_cmd(0x82 + (0x40*(1-D_pos))); // 3rd column of 2nd row
	lcd_write_string("D");
	msdelay(10);
	lcd_cmd(0x82 + 0x40*D_pos);
	lcd_write_string(" ");
	msdelay(10);
}

