/*
 * display_5110.h
 *
 *  Created on: 23.03.2014
 *      Author: Alexander
 */

#ifndef DISPLAY_5110_H_
#define DISPLAY_5110_H_

#define LCD_COMMAND 0
#define LCD_DATA  1
#define LCD_X     84
#define LCD_Y     48


void LCDClear(void);
void LCDString(char *characters);
void LCDBitmap(char my_array[]);
void display_init(void);
void display_showLogo(void);
void gotoXY(int x, int y);

#endif /* DISPLAY_5110_H_ */
