
#include "music.h"

const char keypad[17] = {
	'1', '2', '3', 'A',
	'4', '5', '6', 'B',
	'7', '8', '9', 'C',
'*', '0', '#', 'D'};

extern enum keys  {Key1, Key2, Key3, KeyA,
	Key4, Key5, Key6, KeyB,
	Key7, Key8, Key9, KeyC,
KeyStar, Key0, KeyPound, KeyD};


//keypad
int is_pressed(int row, int col)
{
	DDRA = 0;
	PORTA = 0;

	SET_BIT(DDRA, row);
	SET_BIT(PORTA, col + 4);
	avr_wait(1);

	if (GET_BIT(PINA, col + 4))
	{
		return 0;
	}

	return 1;
}

//return pressed key on keypad
int get_key()
{
	int row, col;
	for (row = 0; row < 4; ++row)
	{
		for (col = 0; col < 4; ++col)
		{
			if (is_pressed(row, col))
			{
				return (row * 4) + col + 1;
			}
		}
	}
	return 0;
}

void welcome()
{
	lcd_clr();
	lcd_pos(0,0);
	char buf[17];
	sprintf(buf, "ByeJose Player");
	avr_wait(500);
	lcd_puts2(buf);
	lcd_pos(1, 0);
	sprintf(buf, "V1.00");
	lcd_puts2(buf);
	avr_wait(1000);
	
}

int main(void)
{
	avr_init();
	lcd_init();
	lcd_clr();
	welcome();
	lcd_clr();

	note Song1[51]={
		{E,Q},{E,Q},{Rest,H},{E,Q},{E,Q},{E,H},{E,Q},{G,Q},{C,Q + EI},{D,EI},
		{E,H},{F,Q},{F,Q},{F,Q},{F,EI},{F,Q},{E,Q},{E,Q},{E,EI},{E,EI},
		{E,Q},{D,Q},{D,Q},{E,Q},{D,H},{G,H},{E,Q},{E,Q},{E,H},{E,Q},{E,Q},{E,H},
		{E,Q},{G,Q},{C,Q+EI},{D,EI},{E,W},{F,Q},{F,Q},{F,Q},{F,Q},{F,Q},
		{F,Q},{E,Q},{E,EI},{E,EI},{G,Q},{G,Q},{F,Q},{D,Q},{C,W}
	};
	
	note Song2[50]={
		{A,EI},{A,EI},{B,Q},{A,Q},{D,Q},{Csharp,H},
		{A,EI},{A,EI},{B,Q},{A,Q},{E,Q},{D,H},
		{A,EI},{A,EI},{A,Q},{Fsharp,Q},{D,Q},{Csharp,Q},{B,Q},
		{G,EI},{G,EI},{Fsharp,Q},{D,Q},{E,Q},{D,H},
		
		{A,EI},{A,EI},{B,Q},{A,Q},{D,Q},{Csharp,H},
		{A,EI},{A,EI},{B,Q},{A,Q},{E,Q},{D,H},
		{A,EI},{A,EI},{A,Q},{Fsharp,Q},{D,Q},{Csharp,Q},{B,Q},
		{G,EI},{G,EI},{Fsharp,Q},{D,Q},{E,Q},{D,H},
	};
	
	note Song3[42]={
		{F,Q},{F,H},{G,Q},{G,Q},{A,Q},{C,Q},{A,H},{F,Q},{C,Q},{F,Q},{F,Q},{G,Q},{G,Q},{A,H},
		{F,Q},{C,Q}
	};
	songs l[3]={{"Song1", Song1, 51}, 
				{"Song2", Song2, 50}, 
				{"Song3", Song3, 16}};
	
	unsigned int i = 0;
	unsigned int key = 0; //keypad key
	
	sprintf(bufmsg, "Select Song");
	lcd_pos(0,0);
	lcd_puts2(bufmsg);
	
	sprintf(bufmsg,"");
	sprintf(bufmsg, "%s", l[i].title);
	lcd_pos(1,0);
	lcd_puts2(bufmsg);
	
	while (1==1)
	{
		//default
		tempo = 2;
		vol = 2;
		
		key = get_key();
		avr_wait(200);
		if(key == 13){
			(i == 0) ? i = 2 : --i;
			clrBot();
			sprintf(bufmsg, "%s", l[i].title);
			lcd_pos(1,0);
			lcd_puts2(bufmsg);
		}
		else if(key == 15){
			(i == 2) ? i = 0 : ++i;
			clrBot();
			sprintf(bufmsg, "%s", l[i].title);
			lcd_pos(1,0);
			lcd_puts2(bufmsg);
		}
		else if(key == 14){
			play(l[i]);
			lcd_clr();
			
			lcd_clr();
			sprintf(bufmsg,"");
			sprintf(bufmsg, "Select Song");
			lcd_pos(0,0);
			lcd_puts2(bufmsg);
			
			sprintf(bufmsg,"");
			sprintf(bufmsg, "%s", l[i].title);
			lcd_pos(1,0);
			lcd_puts2(bufmsg);
		}
	}
}
