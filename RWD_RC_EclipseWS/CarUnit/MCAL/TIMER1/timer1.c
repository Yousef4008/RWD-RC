/*	____________________________________________________________________________
  |																			    |
  | Driver: Timer1															    |
  |																			    |
  | File Name: timer1.h														    |
  |																			    |
  | Description: Header file for timer1 driver				  		    	    |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
 */

#include "timer1.h"
#include "avr/io.h"
#include "avr/interrupt.h"


/*______________________________________________________________________________
 |                               Global Variables          		                |
 |______________________________________________________________________________|
 */

void (*target_routine)(void) = NULL_PTR;

/*______________________________________________________________________________
 |                           Interrupt Service Routine                          |
 |______________________________________________________________________________|
 */

ISR (TIMER1_OVF_vect){
	if(target_routine != NULL_PTR)
		(*target_routine)();
}

ISR (TIMER1_COMPA_vect){
	if(target_routine != NULL_PTR)
		(*target_routine)();
}

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Functional responsible for Initialize Timer1 by:
    1. Setting the initial value of the counter
    2. Setup the mode (Normal / Compare)
    3. Setup the prescaler
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){

	TCNT1 = Config_Ptr->initial_value;		/* Set timer1 initial count to zero */

	if (Config_Ptr->mode == NORMAL_MODE){

		TIMSK |= (1<<TOIE1); /* Enable Timer1 Overflow Interrupt */

		/* Configure timer control register TCCR1A
		 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
		 * 2. FOC1A=1 FOC1B=0
		 * 3. Normal Mode WGM10=0 WGM11=0 (Mode Number 1)
		 */

		TCCR1A = (1<<FOC1A);
		/* Configure timer control register TCCR1B
		 * 1. Normal Mode WGM12=0 WGM13=0 (Mode Number 1)
		 * 2. Prescaler is configurable
		 */
		TCCR1B = Config_Ptr->prescaler;

	}
	else if(Config_Ptr->mode == COMPARE_MODE){

		OCR1A = Config_Ptr->compare_value;

		TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */

		/* Configure timer control register TCCR1A
		 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
		 * 2. FOC1A=1 FOC1B=0
		 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
		 */
		TCCR1A = (1<<FOC1A);

		/* Configure timer control register TCCR1B
		 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
		 * 2. Prescaler is configurable
		 */
		TCCR1B = Config_Ptr->prescaler | Config_Ptr->mode;
	}
	else{

		ICR1 = Config_Ptr->top_count;	/* Set TOP count for timer1 in ICR1 register */

		OCR1A = Config_Ptr->compare_value;

		TCCR1A = (1<<WGM11) | (1<<COM1A1);

		TCCR1B = Config_Ptr->prescaler | Config_Ptr->mode;


	}
}

/*
 * Description :
 -> Functional responsible for uninitialize timer1
 */
void Timer1_deInit(void){
	TCNT1 = 0;
	TCCR1B = 0;
}

/*
 * Description :
 -> Functional responsible for setting the call back function
 */
void Timer1_setCallBack(void(*a_ptr)(void)){
	target_routine = a_ptr;
}
