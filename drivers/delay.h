/*
 * delay.h
 *
 *  Created on: 23.03.2014
 *      Author: Alexander
 */

#ifndef DELAY_H_
#define DELAY_H_

#define delay_7300US 	for(int i = 0; i < 10450; i++)
#define delay_11US		for(int i = 0; i < 18; i++)

void delay_ms(uint32_t delay);
void delay_us(uint32_t delay);
void timer_tick(void* Temp);


#endif /* DELAY_H_ */
