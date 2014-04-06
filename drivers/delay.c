/*
 * delay.c
 *
 *  Created on: 23.03.2014
 *      Author: Alexander
 */

#include <DAVE3.h>

volatile uint32_t ticks = 0;
extern handle_t delay_TimerId;



void timer_tick(void* Temp)
{
	ticks++;
}


void delayms(uint32_t delay)
{
	ticks = 0;
	SYSTM001_StartTimer(delay_TimerId);
	while( ticks < delay );
	SYSTM001_StopTimer(delay_TimerId);
	ticks = 0;
}
