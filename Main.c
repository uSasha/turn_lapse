/*
 * Main.c
 *
 *  Created on: 20.03.2014
 *      Author: Alexander
 */





#include <DAVE3.h>			//Declarations from DAVE3 Code Generation (includes SFR declaration)
#include "display_5110.h"
#include "delay.h"
#include "state_machine.h"

handle_t delay_TimerId;
uint16_t data = 0xAAAA;

int main(void)
{
	DAVE_Init();			// Initialization of DAVE Apps
	for(;;)
	{
		IO004_SetPin(IO004_Handle4);
//		delay_us(1);
		IO004_ResetPin(IO004_Handle4);
	}
	delay_TimerId = SYSTM001_CreateTimer(1,SYSTM001_PERIODIC,timer_tick,NULL);
	display_init();


	LCDClear();
	LCDString("Hello World!");

	while(1)
	{
	    if((UART001_GetFlagStatus (&UART001_Handle0,UART001_FIFO_STD_RECV_BUF_FLAG))==UART001_SET)
		{
	    	UART001_ClearFlag(&UART001_Handle0,UART001_FIFO_STD_RECV_BUF_FLAG);
			data = UART001_ReadData(UART001_Handle0);
			UART001_WriteData(UART001_Handle0,data);
		}

	    process_states();
	    delay_ms(100);
	}
	return 0;
}

