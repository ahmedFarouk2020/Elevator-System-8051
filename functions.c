/*********************************************************/
/*  author   :  farouk                                   */
/*  date     :  29 JUL 2020                              */
/*  version  :  V01                                      */
/*********************************************************/
/* common lib */
#include "C8051F020.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "set.h"
#include "delay.h"

u8 motor_state = 0; // on or off
u8 motion_direction = 0; // up -> 1  down -> 2

void Delay_MS(u16 ms){
    u16 i;
    u16 j;
    for(i=0; i<ms; i++){
        for(j=0; j<120; j++){
        }
    }
}

u8 IsMotorOn(void)
{
	/* check on global variable "motor_state" */
	return motor_state;
}

/* 1. This function checks for queue requests and implement them in a specific manner. 
 * 2. It accesses the Q requests which acts as the input.
 * 3. It uses "stepper" function to rotate the motor.
 */
void elevator(void)
{
	// if going up ignore "going down" request for a while

	// if at floor that is higher than the one requested, ignore it (moving up)

	// 

}

