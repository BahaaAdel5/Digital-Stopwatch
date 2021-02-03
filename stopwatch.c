/*
link for understanding timer1: https://avrgeeks.com/timer-in-ctc-mode-in-atmega-16/
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char seconds1 = 0;
unsigned char seconds10 = 0;
unsigned char minutes1 = 0;
unsigned char minutes10 = 0;
unsigned char hours1 = 0;
unsigned char hours10 = 0;
unsigned char tick = 0;
unsigned char flag =0;

/*
void timer0_init(){
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
	TCNT0 = 0;
	OCR0 = 250;
	TIMSK |= (1<<OCIE0);
	SREG |= (1<<7);
}

ISR(TIMER0_COMP_vect){
	tick++;
}
*/
///////////////////////////TIMER1
void timer1_init(){
	TCCR1B = (1<<CS12) | (1<<CS10) | (1<<WGM12); //register TCCR1A and TCCR1B are both used for initializing timer1
	//TCNT1L = 0;
	//TCNT1H = 0;
	TCNT1 = 0;
	//OCR1BH = 0b00000011;
	//OCR1BL = 0b11101000;
	OCR1A = 1000;
	TIMSK = (1<<OCIE1A);
	SREG |= (1<<7);
}

ISR(TIMER1_COMPA_vect){
	flag = 1;
}
////////////////////////////INT0 (reset)
void INT0_init(){
	GICR |= (1<<6);
	MCUCR |= (1<<ISC01); //falling edge
}

ISR(INT0_vect){
	seconds1 = 0;
	seconds10 = 0;
	minutes1 = 0;
	minutes10 = 0;
	hours1 = 0;
	hours10 = 0;
}
////////////////////////////INT1 (pause)
void INT1_init(){
	GICR |= (1<<7);
	MCUCR |= (1<<ISC11) | (1<<ISC10); //rising edge
	//MCUCR |= (1<<ISC11);
}

ISR(INT1_vect){
	TCCR1B &= ~(1<<CS12) & ~(1<<CS11) & ~(1<<CS10);
}
////////////////////////////INT2 (resume)
void INT2_init(){
	GICR |= (1<<5);
	MCUCSR &= ~(1<<ISC2); //falling edge
}

ISR(INT2_vect){
	TCCR1B |= (1<<CS12) | (1<<CS10);
}

int main(){
	DDRC = 0xFF;
	DDRA = 0xFF;
	//timer0_init();
	timer1_init();

	DDRD &= ~(1<<2) & ~(1<<3);
	DDRB &= ~(1<<2);
	PORTD |= (1<<2);
	PORTB |= (1<<2);

	//PORTD &= ~(1<<3);
	INT0_init();
	INT1_init();
	INT2_init();
	//PORTD &= ~(1<<3);

	timer1_init(); //???????????????????

	while(1){
		//seconds1
		PORTA |= (1<<5);
		PORTC = (PORTC & 0xF0) | (seconds1 & 0x0F);
		_delay_ms(3);
		PORTA &= ~(1<<5);

		//seconds10
		PORTA |= (1<<4);
		PORTC = (PORTC & 0xF0) | (seconds10 & 0x0F);
		_delay_ms(3);
		PORTA &= ~(1<<4);

		//minutes1
		PORTA |= (1<<3);
		PORTC = (PORTC & 0xF0) | (minutes1 & 0x0F);
		_delay_ms(3);
		PORTA &= ~(1<<3);

		//minutes10
		PORTA |= (1<<2);
		PORTC = (PORTC & 0xF0) | (minutes10 & 0x0F);
		_delay_ms(3);
		PORTA &= ~(1<<2);

		//hours1
		PORTA |= (1<<1);
		PORTC = (PORTC & 0xF0) | (hours1 & 0x0F);
		_delay_ms(3);
		PORTA &= ~(1<<1);

		//hours10
		PORTA |= (1<<0);
		PORTC = (PORTC & 0xF0) | (hours10 & 0x0F);
		_delay_ms(3);
		PORTA &= ~(1<<0);

		/////////////////////////////////////////

		//if(tick == 4){
		if(flag == 1){
			if (seconds1 >= 9){
				seconds1 = 0;
				seconds10++;
			}else{
				seconds1 ++;
			}
			if (seconds10 >= 6){
				seconds10 = 0;
				minutes1++;
			}
			if (minutes1 > 9){
				minutes1 = 0;
				minutes10++;
			}
			if (minutes10 > 6){
				minutes10 = 0;
				hours1++;
			}
			if (hours1 > 9){
				hours1 = 0;
				hours10++;
			}
			if (hours10 > 9){
				hours10 = 0;
			}
			//tick = 0;
			flag = 0;
		}

	}

}


