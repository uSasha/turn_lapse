/*
 * encoder.h
 *
 *  Created on: 14.04.2014
 *      Author: Alexander
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#define NO_INPUT 			3
#define CLOCKWISE			0
#define COUNTERCLOCKWISE	1
#define BUTTON_PUSH			2
#define NUMBER_OF_BUTTONS	3

uint16_t encoder_getInput(void);

#endif /* ENCODER_H_ */
