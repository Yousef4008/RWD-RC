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

#include "../../LIB/std_types.h"

/*______________________________________________________________________________
 |                               Types Definitions          	                |
 |______________________________________________________________________________|
 */
typedef enum {	NO_PRESCALER = 1 	, CLK_8_PRESCALER , CLK_64_PRESCALER ,
				CLK_256_PRESCALER 	, CLK_1024_PRESCALER
			 }Timer1_Prescaler;

typedef enum { NORMAL_MODE , COMPARE_MODE = 8 , FAST_PWM = 24 }Timer1_Mode;

typedef struct {
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
uint16 top_count;	  // it will be used in PWM mode only
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Functional responsible for Initialize Timer1 by:
    1. Setting the initial value of the counter
    2. Setup the mode (Normal / Compare)
    3. Setup the prescaler
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description :
 -> Functional responsible for uninitialize timer1
 */
void Timer1_deInit(void);

/*
 * Description :
 -> Functional responsible for setting the call back function
 */
void Timer1_setCallBack(void(*a_ptr)(void));
