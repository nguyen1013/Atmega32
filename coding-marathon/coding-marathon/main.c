#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void) {
	DDRB = 0xFF; // Set PORTB as output
	ADCSRA = (1 << ADEN) | 0x06; // Enable ADC, prescaler = 64
	
	unsigned int count = 0;
	unsigned int previous_val = 0;
	PORTB = 0xff;

	while (1) {
		// Start ADC conversion
		ADMUX = 0x40; // AVCC as reference, Channel 0
		ADCSRA |= (1 << ADSC); // Start conversion
		while (ADCSRA & (1 << ADSC)); // Wait for completion
		unsigned int val = ADC; // Read ADC value
		
		// Detect obstruction (rising edge)
		if (val >= 400 && previous_val < 400) {
			count++; // Increment count
		}
		previous_val = val; // Update previous value
		
		// Convert count to BCD and display on PORTB
		unsigned char tens = count / 10;
		unsigned char ones = count % 10;
		PORTB = ~((tens << 4) | ones); // High nibble: tens, Low nibble: ones

		_delay_ms(200); // Add a small delay for stability
	}
}
