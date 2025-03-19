/*
 * testProject.c
 *
 * Created: 16/03/2025 13:16:33
 * Author : nguyen
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

/*
unsigned char checkDirection(unsigned char dir) {	
	unsigned char new_dir = dir;
	if (PIND == 0xFE) {
		_delay_ms(50);
		if (PIND == 0xFE) new_dir ^= 0x01;
		while (PIND==0xFE);
	}
	return new_dir;
}
*/


int main(void){
	/*
	unsigned char input;
	DDRB = 0xFF;
	DDRD = 0x00;
	while (1) {
		input = PIND;
		if(input == 0xFE) PORTB = 0x0F;
		else if(input == 0xFD) PORTB = 0xF0;
		else if(input == 0xFC) PORTB = 0xAA;
		else PORTB = 0x00;
	}
	*/
	/*
	// Exercise 1: Make a program which displays Port B LEDs as 0x0x0x0x if
	// PD0 buttons is pressed, and x0x0x0x0 if PD7 button is pressed. If no
	// button is pressed, all LEDs are off
	DDRB = 0xFF;
	DDRD = 0x00;
	
	while (1)
	{
		if (PIND == 0xFE) 
		{
			PORTB = 0b01010101; 
		} 
		else if (PIND == 0x7F)
		{
			PORTB = 0b10101010;
		}
		else
		{
			PORTB = 0xFF;
		}
	}
	*/
	/*
	// Exercise 2: Make a program which all LEDs are off at the start. It turns on Port B LEDs if PD0 button is clicked, the LEDs will be turned off if PD0 button is clicked again. And repeat this procedure. (You may need a delay to prevent bouncing)
	DDRB = 0xFF;
	DDRD = 0x00;
	
	unsigned char isLedOn = 0;	

	while (1)
	{
		
		if (PIND == 0xFE)
		{
			_delay_ms(100);
			if (PIND == 0xFE) isLedOn ^= 0x01;
			while (PIND==0xFE);
		}
		
		if (isLedOn)
		{
			PORTB = 0x00;
		} 
		else
		{
			PORTB = 0xFF;
		}
	}
	*/

	/*	
	// Exercise 3: Make a program which flushes LEDs of PB from 0 to 7 repeatedly. The direction of flush will be changed if PD0 button is clicked.
	DDRB = 0xFF;
	DDRD = 0x00;
	
	unsigned char direction = 0; // 0 -> PB0 to PB 7 and vice versa
	unsigned char i = 0;

	while (1)
	{
		
		if (direction)
		{
			PORTB = ~(0x01 << i);	
		}
		else
		{
			PORTB = ~(0x01 << (7-i));
		}
		i = ((i+1) > 7) ? 0 : (i + 1);
		
		if (PIND == 0xFE) {
			_delay_ms(50);
			if (PIND == 0xFE) direction ^= 0x01;
			while (PIND==0xFE);
			i = 0;		

		}

		_delay_ms(200);

	}
	*/

	// Make a program which blinks PB0 at 10Hz. If any 2 buttons are pushed down, the program blinks PB7 at 20Hz.
	DDRB = 0xFF;
	DDRD = 0x00;
	
	while (1) {
		unsigned char count = 0;

		for (unsigned char i=0; i<8; i++) {
			if (!(PIND & (0x01<<i))) {
				_delay_ms(50);
				if (~PIND & (0x01<<i)) count ++;
			}
		}		

		if (count==2) {
			PORTB = 0x7F;
			_delay_ms(25);
			PORTB = 0xff;
			_delay_ms(25);
		} else {
			PORTB = 0xFE;
			_delay_ms(50);
			PORTB = 0xff;
			_delay_ms(50);
		}
	}
}

