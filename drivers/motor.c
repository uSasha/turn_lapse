/*
 * motor.c
 *
 *  Created on: 06.04.2014
 *      Author: Alexander
 */

#include <DAVE3.h>
#include "delay.h"

void motor_turn(uint16_t turn_angle)
{
	IO004_SetPin(IO004_Handle3);
	delay_ms(turn_angle * 100);
	IO004_ResetPin(IO004_Handle3);
}
