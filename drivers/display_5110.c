/*
 * display_5110.c
 *
 *  Created on: 23.03.2014
 *      Author: Alexander
 */
#include "fonts.h"
#include "display_5110.h"
#include "delay.h"


void display_init(void)
{
	uint16_t SendData = 0x00;

	IO004_ResetPin(IO004_Handle1);	// RST low

	SPI001_WriteData(&SPI001_Handle0,&SendData,SPI001_STANDARD);

	delayms(2);
	IO004_SetPin(IO004_Handle1);	// RST high
	delayms(10);					// 10 ms
	IO004_ResetPin(IO004_Handle1);	// RST low
	delayms(100);					// 100 ms
	IO004_SetPin(IO004_Handle1);	// RST high
	delayms(10);

	IO004_ResetPin(IO004_Handle0);	// send command

	delayms(1);						// TODO redo
	SendData = 0x21;	// horizontal addressing, extended instruction set
	SPI001_WriteData(&SPI001_Handle0,&SendData,SPI001_STANDARD);
	SendData = 0xB1;	// ??
	SPI001_WriteData(&SPI001_Handle0,&SendData,SPI001_STANDARD);
//	SendData = 0x04;	// temp coef
	SendData = 0xB8;	// temp coef
	SPI001_WriteData(&SPI001_Handle0,&SendData,SPI001_STANDARD);
	SendData = 0x14;	// bias system 2
	SPI001_WriteData(&SPI001_Handle0,&SendData,SPI001_STANDARD);
	SendData = 0x20;	// horizontal addressing, basic instruction set
	SPI001_WriteData(&SPI001_Handle0,&SendData,SPI001_STANDARD);
	SendData = 0x0C;	// normal mode
	SPI001_WriteData(&SPI001_Handle0,&SendData,SPI001_STANDARD);
}


void LCDWrite(uint16_t data_or_command, uint16_t data)
{
	IO004_SetOutputValue(IO004_Handle0, data_or_command);
	while(SPI001_WriteData(&SPI001_Handle0,&data,SPI001_STANDARD) == 0)
	{}
}


void gotoXY(int x, int y)
{
	x = x % 84;		// TODO check values
	y = y % 48;		// TODO check values
	LCDWrite(LCD_COMMAND, 0x80 | x);  // Column.
	LCDWrite(LCD_COMMAND, 0x40 | y);  // Row.  ?
}


//Clears the LCD by writing zeros to the entire screen
void LCDClear(void)
{
	delayms(1);		// TODO find why this is necessary for proper data transfer
//	gotoXY(0, 0);
//	for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
	for (int index = 0 ; index <= (LCD_X * LCD_Y / 8) ; index++)
	{
		LCDWrite(LCD_DATA, 0x00);
		for(int i = 100; i; i--);
	}
//	gotoXY(0, 0); //After we clear the display, return to the home position
}


void LCDCharacter(char character)
{
	LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding

	for (int index = 0 ; index < 5 ; index++)
	LCDWrite(LCD_DATA, ASCII[character - 0x20][index]);
	//0x20 is the ASCII character for Space (' '). The font table starts with this character

	LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding
}


//Given a string of characters, one by one is passed to the LCD
void LCDString(char *characters)
{
	while (*characters)
	{
		LCDCharacter(*characters++);
	}
}


void LCDBitmap(char my_array[])
{
	for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
	{
		LCDWrite(LCD_DATA, my_array[index]);
	}
}


void display_showLogo(void)
{
	LCDBitmap(SFEFlameBubble);
	for(int i = 0; i < LCD_X; i++)
	{
//		LCDWrite(LCD_DATA, 0x05);
	}
}

