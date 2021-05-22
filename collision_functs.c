#include <at89c5131.h>

void reset_values(unsigned int *D_pos, unsigned int *pos, unsigned int *score_and_hs, unsigned int *state_new_disp)
{
	int i;
	*D_pos = 1;
	
	for (i=0;i<7;i++)
	{
		pos[i]=0x20;
	}
	*state_new_disp = 2; //since it will be updated immediately after, and become 0
	score_and_hs[0] = -1; // since it will be incremented immediately after 
}


void display_summary(unsigned int *score_and_hs)
{
	char score_str[3]={0,0,'\0'};
	char high_score_str[3] = {0,0,'\0'};
	lcd_cmd(0x01); //clear screen
	lcd_cmd(0x81);
	lcd_write_string("Score:");
	lcd_cmd(0xC1);
	lcd_write_string("High Score:");

	
	// print score
	lcd_cmd(0x8D); //13th column 1st row
	int_to_string(score_and_hs[0], score_str);
	lcd_write_string(score_str);
	msdelay(10);
	
	//print high score
	lcd_cmd(0xCD); //13th column 2nd row
	int_to_string(score_and_hs[1], high_score_str);
	lcd_write_string(high_score_str);
	msdelay(10);
	
	msdelay(2000);
	
}


void check_collision(unsigned int *pos, unsigned int *D_pos, unsigned int *score_and_hs, unsigned int *state_new_disp)
{
// detect collision
	if (*D_pos==1) //in row1
	{
		//obstacles 0,2,5
		if (pos[0]==0 || pos[0]==1 || pos[2]==1 || pos[5]==0)
		{
			EA=0; //disable interrupts
			if (score_and_hs[0]>score_and_hs[1])
			{
				score_and_hs[1] = score_and_hs[0]; //update high score
			}
			display_summary(score_and_hs);
			reset_values(D_pos, pos, score_and_hs, state_new_disp);
		}
	}
	else //D_pos==0, row2 
	{
		//obstacles 1,3,4
		if (pos[1]==0 || pos[1]==1 || pos[3]==0 || pos[4]==1)
		{
			EA=0; //disable interrupts
			if (score_and_hs[0]>score_and_hs[1])
			{
				score_and_hs[1] = score_and_hs[0]; //update high score
			}
			display_summary(score_and_hs);
			reset_values(D_pos, pos, score_and_hs, state_new_disp);
		}
	}
}


void display_all(unsigned int *pos,unsigned int *D_pos, unsigned int *score_and_hs, unsigned int *state_new_disp)
{
	lcd_cmd(0x01);//clear screen
	lcd_cmd(0x82 + (0x40*(1-*D_pos))); // 3rd column of 2nd row
	lcd_write_string("D");
	msdelay(10);
	
	if (pos[0]>=0 && pos[0]<=15){
	lcd_cmd(0x80 + pos[0]+ 1); //obst0
	lcd_write_string("**");
	}
	if (pos[1]>=0 && pos[1]<=15){
	lcd_cmd(0xC0 + pos[1] + 1); //obst1
	lcd_write_string("**");
	}
	if (pos[2]>=0 && pos[2]<=15){
	lcd_cmd(0x80 + pos[2] + 1); //obst2
	lcd_write_string("*");
	}
	if (pos[3]>=0 && pos[3]<=15){
	lcd_cmd(0xC0 + pos[3] + 2); //obst3
	lcd_write_string("*");
	}
	if (pos[4]>=0 && pos[4]<=15){
	lcd_cmd(0xC0 + pos[4] + 1); //obst4
	lcd_write_string("*");
	}
	if (pos[5]>=0 && pos[5]<=15){
	lcd_cmd(0x80 + pos[5] + 2); //obst5
	lcd_write_string("*");
	}
	//obst 6: nothing, dont need to show
	check_collision(pos, D_pos, score_and_hs, state_new_disp);
	msdelay(500);
	if (EA==0){
		EA=1;
	}
}

void move_D(unsigned int pos[], unsigned int *D_pos, unsigned int score_and_hs[], unsigned int *state_new_disp) 
{
	unsigned char ch=0;
	ch = SBUF;
	switch(ch)
			{
				case 'q': 
					if(*D_pos==0)
					{
						*D_pos = 1;
					}
					break;
				case 'a': 
					if(*D_pos==1)
					{
						*D_pos = 0;
					}
					break;
			}
	show_player(*D_pos);
	check_collision(pos, D_pos, score_and_hs, state_new_disp);
}
	

