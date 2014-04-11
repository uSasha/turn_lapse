/*
 * camera.c
 *
 *  Created on: 06.04.2014
 *      Author: Alexander
 */

#include <DAVE3.h>
#include "delay.h"



void camera_shot(void)
{
	for(int i=0; i<16; i++)
	{
		IO004_SetPin(IO004_Handle4);
		delay_11US;
		IO004_ResetPin(IO004_Handle4);
		delay_11US;
	}

	delay_7300US;

	for(int i=0; i<16; i++)
	{
		IO004_SetPin(IO004_Handle4);
		delay_11US;
		IO004_ResetPin(IO004_Handle4);
		delay_11US;
	}
}
