/*
 * camera.c
 *
 *  Created on: 06.04.2014
 *      Author: Alexander
 */

#include <DAVE3.h>
#include "delay.h"
//
//void camera_shot(uint16_t shot_time)
//{
//	IO004_SetPin(IO004_Handle4);
//	delay_ms(shot_time * 1000);
//	IO004_ResetPin(IO004_Handle4);
//}
//

void camera_shot()
{
	for(int i=0; i<16; i++)
	{
		IO004_SetPin(IO004_Handle4);
		delay_us(11);
		IO004_ResetPin(IO004_Handle4);
		delay_us(11);
//		digitalWrite(irLED, HIGH);
//		delayMicroseconds(11);
//		digitalWrite(irLED, LOW);
//		delayMicroseconds(11);
	}
	delay_us(7330);
//	delayMicroseconds(7330);
	for(int i=0; i<16; i++)
	{
		IO004_SetPin(IO004_Handle4);
		delay_us(11);
		IO004_ResetPin(IO004_Handle4);
		delay_us(11);
//		digitalWrite(irLED, HIGH);
//		delayMicroseconds(11);
//		digitalWrite(irLED, LOW);
//		delayMicroseconds(11);
	}
}
