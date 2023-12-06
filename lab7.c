/*
* lab7.c
*
* Created: 7/12/2023 11:34:21 PM
* Author : Marwan & Ahmed
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int main(void){
	// inputs7
	DDRB |= (1 << DDB3);
	DIDR0 |= (1 << ADC0D);
	cli(); // Disable Interrupt
	TCCR2A |= (1 << WGM21) | (1 << WGM20); // Timer set to Fast PWM mode
	TCCR2A |= (1 << COM2A1);
	ADCSRA |= (3 << ADPS0); // set prescale to 128
	ADCSRA |= (1 << ADIE); // enable interrupts
	ADCSRA |= (1 << ADEN); // enable ADC
	ADMUX |= (1 << REFS0); // reference voltage
	sei();	// Enable Interrupts
		// initialize OCR2A register
	OCR2A = 10;
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // set prescale to 1024
	ADCSRA |= (1 << ADSC); // The Conversion
	while(1){
	}
}
ISR(ADC_vect){
		// mapping 0-1024 to 10-36
	OCR2A = (float) ADC * 26/1023 + 10;
		// Reset
	ADCSRA |= (1 << ADSC);
}
