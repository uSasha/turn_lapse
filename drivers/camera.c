/*
 * camera.c
 *
 *  Created on: 06.04.2014
 *      Author: Alexander
 */

#include <DAVE3.h>
#include "delay.h"



//#define delay_7300US 	for(int i = 0; i < 10450; i++)
//#define delay_11US		for(int i = 0; i < 18; i++)


#define delay_7125US 	for(int i = 0; i < 10050; i++)
#define delay_15US		for(int i = 0; i < 24; i++)



void camera_shot(void)
{
	for(int i=0; i<22; i++)
	{
		IO004_SetPin(IO004_Handle4);
		delay_15US;
		IO004_ResetPin(IO004_Handle4);
		delay_15US;
	}

	delay_7125US;

	for(int i=0; i<22; i++)
	{
		IO004_SetPin(IO004_Handle4);
		delay_15US;
		IO004_ResetPin(IO004_Handle4);
		delay_15US;
	}
}
