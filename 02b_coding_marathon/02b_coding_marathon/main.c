/*
 * testProject.c
 *
 * Created: 16/03/2025 13:16:33
 * Author : nguyen
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

unsigned char checkPress() {
	for (unsigned char i = 0; i<8; i++) {
		if (~PIND & (1 << i)) {
			_delay_ms(50);
			if (~PIND & (1 << i)){
				return 1;
			}
		}
	}
	return 0;
}

int main(void){
	/*
	// Task 0: Display port B LEDs one by one from right to left. Each LED has 1 second, it blinks 5 times
	DDRB = 0xFF;
	
	unsigned char i = 0;
	
	while(1) {
		for (unsigned char j = 0; j<5; j++) {
			PORTB = ~(0x00 | (0x01 << i));
			_delay_ms(100);
			PORTB = 0xff;
			_delay_ms(100);
		}
		i = (i+1)%8;
	}
	*/

	/*
	// Task 1: Display port B LEDs from center to edges, i.e., they should be turned on in this order: xxxooxxx, xxoxxoxx, xoxxxxox, oxxxxxxo, and repeat.
	DDRB = 0xFF;	
	
	while(1) {
		for (unsigned char i = 0; i<4; i++) {
			PORTB = ~(0x00 | (0x10 << i) | (0x08 >> i));
			_delay_ms(1000);
		}
	}
	*/
	
	/*
	// Task 2: Use both port A and B as output port, and flush the 16 LEDs from	left to right with an interval of 200ms of each LED.
	DDRA = 0xff;
	DDRB = 0xFF;
	
	while(1) {
		for (unsigned int i = 0; i<16; i++) {
			if (i<8) {
				PORTB = 0xff;
				PORTA = ~(0x00 | (1 << i));
			} else {
				PORTA = 0xff;
				PORTB = ~(0x00 | (1 << (i-8)));
			}
			_delay_ms(200);
		}
	}
	*/

	/*
	// Task 3: Improve task 2 by acceleration. It means the interval between LEDs is getting smaller and smaller. The first interval is 1000ms, the next is 950, then 900, …
	DDRA = 0xff;
	DDRB = 0xFF;
	
	while(1) {		
		uint32_t delay = 1000;

		for (unsigned char i = 0; i<16; i++) {
			if (i<8) {
				PORTB = 0xff;
				PORTA = ~(0x00 | (1 << i));
				} else {
				PORTA = 0xff;
				PORTB = ~(0x00 | (1 << (i-8)));
			}
			
			for (uint32_t j = 0; j<delay; j++) {
				_delay_ms(1);
			}
			
			delay -=50;
		}
	}
	*/

	/*
	// Task 4: Use Port B to control LEDs, use Port D as button input ports. Let each button controls 1 LED: when PD7 is pressed, it will toggle LED on	PB7. The program starts with all LEDs are OFF
	DDRB = 0xff;
	DDRD = 0x00;
		
	while(1) {
		unsigned char input = 0x00;

		for (unsigned char i=0; i<8; i++) {
			if (~PIND & (1 << i)) {
				_delay_ms(50);
				if (~PIND & (1 << i)) input | (1 << i);
			}
		}
		
		PORTB = ~input;

	}
	*/

	// Task 5: Use Port B to control LEDs, and Port D as button inputs. When program starts, it blinks PB7 at 0.1Hz. When any button(s) is/are pressed, the program blinks PB7 at 10Hz
	DDRB = 0xff;
	DDRD = 0x00;	
	unsigned char isPressed = 0;

	
	while(1) {
		isPressed = checkPress();

		if (isPressed == 0) {
			PORTB = 0x7F;
			for (uint32_t i = 0; i<5000; i++) {
				isPressed = checkPress();
				if (isPressed == 1) {
					break;
				}
				_delay_ms(1);
			}
			if (isPressed == 1) continue;;

			PORTB = 0xFF;
			for (uint32_t i = 0; i<5000; i++) {
				isPressed = checkPress();
				if (isPressed == 1) {
					break;
				}
				_delay_ms(1);
			}
			if (isPressed ==1) continue;;
		} else {
			PORTB = 0x7F;
			_delay_ms(50);
			PORTB = 0xFF;
			_delay_ms(50);
		}
	}

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

	/*
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
	*/
}

