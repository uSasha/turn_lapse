/*
 * camera.c
 *
 *  Created on: 06.04.2014
 *      Author: Alexander
 */

#include <DAVE3.h>
#include "delay.h"

void camera_shot(uint16_t shot_time)
{
	IO004_SetPin(IO004_Handle4);
	delayms(shot_time * 1000);
	IO004_ResetPin(IO004_Handle4);
}

