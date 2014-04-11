/*
 * sate_machine.c
 *
 *  Created on: 24.03.2014
 *      Author: Alexander
 */
#include <DAVE3.h>
#include <stdio.h>
#include "display_5110.h"
#include "delay.h"
#include "camera.h"
#include "motor.h"

// states
#define MENU_SET_TIME		0
#define SET_TIME			1
#define MENU_SET_ANGLE		2
#define SET_ANGLE			3
#define MENU_SET_SHOT		4
#define SET_SHOT			5
#define MENU_RUN			6
#define RUN					7
#define NUMBER_OF_STATES	8


void menuSetTime(void);
void setTime(void);
void menuSetAngle(void);
void setAngle(void);
void menuSetShot(void);
void setShot(void);
void menuRun(void);
void run(void);
void showMenu(void);


extern 	uint16_t data;
uint16_t input;
unsigned long state	= MENU_SET_TIME; // index into current state
// globals that rule timelapse behavior
uint32_t lapse_time = 0;		// TODO clean
uint32_t turn_angle = 0;
uint32_t shot_time = 0;


// Linked data structure
struct State
{
	void (*CmdPt)(void);
	char str[12];
	unsigned long next[NUMBER_OF_STATES];
};

typedef const struct State STyp;

STyp FSM[NUMBER_OF_STATES]=
{	// output		message 		'0'					'1'
	{&menuSetTime,	"time   ",		{MENU_SET_ANGLE,	SET_TIME		}},
	{&setTime,		"",				{SET_TIME,			MENU_SET_TIME	}},
	{&menuSetAngle,	"angle  ",		{MENU_SET_SHOT,		SET_ANGLE		}},
	{&setAngle,		"",				{SET_ANGLE,			MENU_SET_ANGLE	}},
	{&menuSetShot,	"shot   ",		{MENU_RUN,			SET_SHOT		}},
	{&setShot,		"",				{SET_SHOT,			MENU_SET_SHOT	}},
	{&menuRun,		"run    ",		{MENU_SET_TIME,		RUN				}},
	{&run,			"",				{RUN,				MENU_RUN		}}
};


uint16_t getSensors(void)
{
	data -= '0';		// atoi conversion
	return data;
	/*
	if(data == '0')
		return 0;
	if(data == '1')
		return 1;
	return 2;
	*/
}

void process_states(void)
{
	input = getSensors();					// get input
	if(input < NUMBER_OF_STATES)
	{
		state = FSM[state].next[input];		// change state
		(FSM[state].CmdPt)();				// call output function
	}
	input = NUMBER_OF_STATES;				// clear input
}


void menuSetTime(void)
{
	showMenu();
}

void setTime(void)
{
	if(input == 0)
	{
		lapse_time++;
	}

	showMenu();
}

void menuSetAngle(void)
{
	showMenu();
}

void setAngle(void)
{
	if(input == 0)
	{
		turn_angle++;
	}

	showMenu();
}

void menuSetShot(void)
{
	showMenu();
}

void setShot(void)
{
	if(input == 0)
	{
		shot_time++;
	}

	showMenu();
}

void menuRun(void)
{
	showMenu();
}

void run(void)
{
	uint16_t turn_time = lapse_time / turn_angle;

	for(uint16_t i = 0; i < turn_angle; i++)
	{
		camera_shot();
		delay_ms((turn_time - shot_time) * 1000 - turn_angle);	//TODO убрать коэфицент
		motor_turn(turn_angle);
	}
}

void showMenu(void)
{
	uint8_t y = 0;
	delay_ms(2);
	LCDClear();
	delay_ms(2);
	gotoXY(0, 0);
	delay_ms(2);

	for(uint8_t i = 0; i < NUMBER_OF_STATES; i++)
	{
		if(i == state)			// draw cursor near current state name
		{
			LCDString(">");
		}else
		{
			LCDString(" ");
		}

		LCDString(FSM[i].str);
		if(i % 2)		//  TODO redo
		{
			char str[4];
			switch (i)
			{
				case SET_TIME:
					sprintf(str, "%d", (int)lapse_time);
					break;
				case SET_ANGLE:
					sprintf(str, "%d", (int)turn_angle);
					break;
				case SET_SHOT:
					sprintf(str, "%d", (int)shot_time);
					break;
				case RUN:
					sprintf(str, " ");
					break;
			}
			LCDString(str);
			y++;					// new line
			delay_ms(2);
			gotoXY(0, y);
			delay_ms(2);
		}
		delay_ms(2);
	}
}
