/*
 * 03_ADC.c
 *
 * Created: 21/03/2025 16:41:22
 * Author : nguyen
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void) {

	// Task 1: Design a program which monitors ADC1 voltage, if the voltage is below Vref/2, all the LEDs on port D will be off; if the voltage is over Vref/2, all the LEDs of port D will be turned on.
	DDRA = 0x00; // Set Port A as input
	DDRD = 0xFF; // Set Port D as output
	ADMUX = 0x40; // AVCC as reference, select Channel 0
	ADCSRA = (1<<ADEN) | 0x06; // Enable ADC, set prescaler to 64

	while (1) {
		// Read ADC (Channel 0)
		ADCSRA |= (1<<ADSC); // Start conversion
		while(ADCSRA&(1<<ADSC));
		
		if (ADC > 512) {
			PORTD = 0x00;
			} else {
			PORTD = 0xff;
		}
		
		_delay_ms(5);
	}
}


/*	

int main(void) {		

	// Task 2: Continue from task 1, add another function: the program counts how many times the value is over Vref/2 and displays this count value on port B as binary value from 00H.
	DDRA = 0x00; // Set Port A as input	
	DDRB = 0xff; // Set Port B as output
	DDRD = 0xFF; // Set Port D as output
	ADMUX = 0x40; // AVCC as reference, select Channel 0
	ADCSRA = (1<<ADEN) | 0x06; // Enable ADC, set prescaler to 64
		
	unsigned char count = 0;
	uint8_t isOver512 = 0;
	PORTB = 0xff;

	while (1) {
		// Read ADC (Channel 0)
		ADCSRA |= (1<<ADSC); // Start conversion
		while(ADCSRA&(1<<ADSC)); 
			
		if (ADC >= 512) {
			PORTD = 0x00;
			if (isOver512 == 0) {
				count ++;
				PORTB = ~count;
				isOver512 = 1;
			}
			} else {
			PORTD = 0xff;
			isOver512 = 0;
		}

		_delay_ms(50);
	}
	
	// Task 3: Use ADMUX to select both Channel 0 and 1 from port A as analog input. And use the potentiometer and photoresistor to get 2 variable voltages between 0 and 5V. The program keeps monitoring the voltages of these 2 inputs, if channel 1 is higher than 2, turn on Port B upper 4 LEDs, if not, turn on Port B lower 4 LEDs.
	
	DDRA = 0x00; // Set Port A as input
	DDRB = 0xff; // Set Port B as output
	
	ADCSRA = (1<<ADEN) | 0x06; // Enable ADC, set prescaler to 64
	PORTB = 0xff;

	while (1) {
		// Read ADC (Channel 0)
		ADMUX = 0x40; // AVCC as reference, select Channel 0
		ADCSRA |= (1<<ADSC); // Start conversion
		while(ADCSRA&(1<<ADSC));
		unsigned char potential_val = ADC;
		
		// Read ADC (Channel 1)
		ADMUX = 0x41; // AVCC as reference, select Channel 1
		ADCSRA |= (1<<ADSC); // Start conversion
		while(ADCSRA&(1<<ADSC));
		unsigned char photoresistor_val = ADC;
		
		if (potential_val > photoresistor_val) {
			PORTB = 0x0f;
			} else {
			PORTB = 0xf0;
		}
		
		_delay_ms(100);
	}
	
	// Task 4: Use ADMUX to select Ch0 and Ch1 from potentiometer and photoresistor. Use Port D as button input, and Port B as LED output. If button PD0 is pressed, make an AD conversion on Ch0; if button PD1 is pressed, make an AD conversion on Ch1; If current conversion of Chx is changed over ±0.1Vcc from the previous value, toggles LEDs of Port B. (Ch0 for 0,2,4,6, Ch1 for 1,3,5,7)
	
	DDRA = 0x00; // Set Port A as input
	DDRB = 0xFF; // Set Port B as output
	DDRD = 0x00; // Set Port D as input
	
	ADCSRA = (1<<ADEN) | 0x06; // Enable ADC, set prescaler to 64
	PORTB = 0xff;
	
	// Read ADC (Channel 0) at the first time
	ADMUX = 0x40; // AVCC as reference, select Channel 0
	ADCSRA |= (1<<ADSC); // Start conversion
	while(ADCSRA&(1<<ADSC));
	unsigned char potential_val = ADC;
	
	// Read ADC (Channel 1) at the first time
	ADMUX = 0x41; // AVCC as reference, select Channel 1
	ADCSRA |= (1<<ADSC); // Start conversion
	while(ADCSRA&(1<<ADSC));
	unsigned char photo_val = ADC;

	while (1) {
		unsigned char new_val = 0;
		char channel = -1;
		
		if (PIND == 0xFE) { // check push PD0
			// Read ADC (Channel 0)
			ADMUX = 0x40; // AVCC as reference, select Channel 0
			ADCSRA |= (1<<ADSC); // Start conversion
			while(ADCSRA&(1<<ADSC));
			new_val = ADC;
			channel = 0;
			} else if (PIND == 0xFD) { // check push PD1
			// Read ADC (Channel 1)
			ADMUX = 0x41; // AVCC as reference, select Channel 1
			ADCSRA |= (1<<ADSC); // Start conversion
			while(ADCSRA&(1<<ADSC));
			new_val = ADC;
			channel = 1;
		}
		
		if (channel == 0) {
			if (abs(new_val - potential_val) > 10) {
				PORTB = (PORTB==0xFF) ? 0b01010101 : 0xFF;
				potential_val = new_val;
			}
			} else if (channel == 1) {
			if (abs(new_val - photo_val) > 10) {
				PORTB = (PORTB==0xFF) ? 0b10101010 : 0xFF;
				photo_val = new_val;
			}
		}
		
		_delay_ms(100);
	}

	// Task 5: use ADC7 as analog input, and PortD as digital input to switch board, PortB as LED output. If PD0 is pressed, take a conversion, if the analog voltage is below 1V, all LEDs off, if it's 1-2V, the rightmost 2 LEDs on, if i'ts 2-3V, the rightmost 4 LEDs on, if it's 3-4V 6 LEDs on, if 4-5V, all LEDs are on.
	
	DDRA = 0x00; // Set Port A as input
	DDRB = 0xFF; // Set Port B as output
	DDRD = 0x00; // Set Port D as input
	
	ADCSRA = (1<<ADEN) | 0x06; // Enable ADC, set prescaler to 64
	PORTB = 0xFF;
	
	while (1) {
		
		if (PIND == 0xFE) { // check push PD0
			// Read ADC (Channel 0)
			ADMUX = 0x47; // AVCC as reference, select Channel 7
			ADCSRA |= (1<<ADSC); // Start conversion
			while(ADCSRA&(1<<ADSC));
			
			uint16_t val = ADC;
			unsigned char level = val/205; // divide 1024 steps to 5 level
			
			const uint8_t led_patterns[5] = {0xFF, 0xFC, 0xF0, 0xC0, 0x00};
			PORTB = led_patterns[level];

			} else {
			PORTB = 0xFF;
		}
		_delay_ms(50);
	}

	// Task 6: connect ADC board to PORTA, and connect LDR to PA0. Make a program which	turns on PORTB LEDs if the photoresistor is covered. Display how many times the photoresistor is covered on PORTC.
	
	DDRA = 0x00; // Set Port A as input
	DDRB = 0xFF; // Set Port B as output
	
	ADCSRA = (1<<ADEN) | 0x06; // Enable ADC, set prescaler to 64
	ADMUX = 0x40; // AVCC as reference, select Channel 0
	PORTB = 0xFF;
	
	uint16_t isCovered = 0;
	unsigned char count = 0;
	
	while (1) {
		
		// Read ADC (Channel 0)
		ADCSRA |= (1<<ADSC); // Start conversion
		while(ADCSRA&(1<<ADSC));
		uint16_t val = ADC;
		
		if (val	> 256 && isCovered == 0) { // Set voltage of photoresistor is 1.25V when covered
			count++;
			isCovered = 1;
			PORTB = ~count;
			} else {
			isCovered = 0;
		}
		_delay_ms(150);
	}
	
	// Task 7: connect ADC board to PORTA, and connect Monolithic Photodiode OPT101 to PA0.
	// Program counts how many times the OPT101 is covered by a black plastic piece (on PORTB) and how many times it is covered by a human finger (on PORTC).
	
	DDRA = 0x00; // Set Port A as input
	DDRB = 0xFF; // Set Port B as output
	DDRC = 0xFF; // Set Port C as output

	// Initialize ADC: Enable ADC, set prescaler to 64 (8MHz clock), and AVCC as reference voltage
	ADCSRA = (1<<ADEN) | 0x06; // Enable ADC and prescaler 64
	ADMUX = 0x40; // Select Channel 0 (PA0) and use AVCC as reference
	PORTB = 0xFF; // Initialize PORTB
	PORTC = 0xFF; // Initialize PORTC
	
	unsigned char finger_count = 0;
	unsigned char isFingerCover = 0;
	unsigned char plastic_count = 0;
	unsigned char isPlasticCover = 0;
	
	while (1) {
		
		// Read ADC (Channel 0)
		ADCSRA |= (1<<ADSC); // Start conversion
		while(ADCSRA&(1<<ADSC));
		uint16_t val = ADC;
		
		if (val <= 40) { // Set voltage of Monolithic Photodiode is 0.2V when covered by black plastic
			if (isPlasticCover == 0) {
				plastic_count++;
				isPlasticCover = 1;
				PORTB = ~plastic_count;
				isFingerCover = 0;
			}
			} else if (val >80 && val <120){ // Set voltage of Monolithic Photodiode is 0.4V to 0.6V when covered by finger
			if (isFingerCover == 0) {
				finger_count++;
				isFingerCover = 1;
				PORTC = ~finger_count;
				isPlasticCover = 0;
			}
			} else {
			isPlasticCover = 0;
			isFingerCover = 0;
		}
		_delay_ms(150);
	}
}
	
*/


