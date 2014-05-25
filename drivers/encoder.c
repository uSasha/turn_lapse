/*
 * encoder.c
 *
 *  Created on: 12.04.2014
 *      Author: Alexander
 */
#include <DAVE3.h>
#include "encoder.h"

#define debounce() 	for(uint32_t i = 0; i < 10000; i++)

uint16_t input = NO_INPUT;


uint16_t encoder_getInput(void)
{
	uint16_t temp_input = input;
	input = NO_INPUT;
	return temp_input;
}


void encoder_ButtonHandler(void)
{
	debounce();
	uint32_t button = IO002_ReadPin(IO002_Handle2);
	if(!button)
	{
		input = BUTTON_PUSH	;
	}
}


void encoder_TurnHandler(void)
{
	uint32_t enc2 = IO004_ReadPin(IO004_Handle8);
	debounce();
	uint32_t enc1 = IO002_ReadPin(IO002_Handle0);
	if(!enc1)
	{
		if(enc2)
		{
			input = CLOCKWISE;
		}else
		{
			input = COUNTERCLOCKWISE;
		}
	}
}
