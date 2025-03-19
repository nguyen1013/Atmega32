#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	/*
	// Task 1: Make a program which outputs Binary numbers from 00000000 to 11111111 on port B, each number is displayed 500ms. 
	
	DDRB = 0xFF;
	
    while (1) 
    {
		for (unsigned char i=0; i<256; i++)
		{
			PORTB = ~(0xff & i);
			_delay_ms(500);
		}			
    }
	*/
	
	/*
	// Task 2: Make a program which outputs BCD numbers from 0 to 99 on port B. When displaying numbers from 0 to 9, the higher 4 LEDs should be OFF
	DDRB = 0xFF;
		
	while (1)
	{
		for (unsigned char i=0; i<256; i++)
		{
			unsigned char low = i%10;
			unsigned char high = i/10;
			
			unsigned char bcd = 0x00 | low | (high <<4);
			
			PORTB = ~bcd;
			_delay_ms(1000);
		}
	}
	*/
	
	// Task 3: Make a program to flush the LEDs from PB0 to PB7 and repeat, as following figure.
	DDRB = 0xFF;
		
	while (1)
	{
		for (unsigned char i=0; i<8; i++)
		{
			PORTB = ~(1 << i);
			_delay_ms(1000);
		}
	}
}

