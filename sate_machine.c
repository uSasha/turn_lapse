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
#include "encoder.h"

// states
#define MENU_SET_TIME		0
#define SET_TIME			1
#define MENU_SET_ANGLE		2
#define SET_ANGLE			3
#define MENU_SET_SHOT		4
#define SET_SHOT			5
#define MENU_RUN			6
#define NUMBER_OF_STATES	7


#define MAX_VALUE					100


void menuSetTime(void);
void setTime(void);
void menuSetAngle(void);
void setAngle(void);
void menuSetShot(void);
void setShot(void);
void menuRun(void);
void run(void);
void showMenu(void);



extern uint16_t data;
uint16_t input;
unsigned long state	= MENU_SET_TIME; // index into current state
// globals that rule timelapse behavior
uint32_t lapse_time = 0;
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
{	// output		message 		'CLOCKWISE'			'COUNTERCLOWISE'	'BUTTON_PUSH'
	{&menuSetTime,	"time   ",		{MENU_SET_ANGLE,	MENU_RUN,			SET_TIME		}},
	{&setTime,		"",				{SET_TIME,			SET_TIME,			MENU_SET_TIME	}},
	{&menuSetAngle,	"angle  ",		{MENU_SET_SHOT,		MENU_SET_TIME,		SET_ANGLE		}},
	{&setAngle,		"",				{SET_ANGLE,			SET_ANGLE,			MENU_SET_ANGLE	}},
	{&menuSetShot,	"shot   ",		{MENU_RUN,			MENU_SET_ANGLE,		SET_SHOT		}},
	{&setShot,		"",				{SET_SHOT,			SET_SHOT,			MENU_SET_SHOT	}},
	{&menuRun,		"run    ",		{MENU_SET_TIME,		MENU_SET_SHOT,		MENU_RUN		}}
};

void process_states(void)
{
	input = getInput();						// get input
	if(input != NO_INPUT)
	{
		state = FSM[state].next[input];		// change state
		(FSM[state].CmdPt)();				// call output function
	}
	input = NO_INPUT;						// clear input
}

void state_machine_init(void)
{
	state = MENU_SET_TIME;
	showMenu();
}

void menuSetTime(void)
{
	showMenu();
}

void setTime(void)
{
	if(input == CLOCKWISE && lapse_time < MAX_VALUE)
	{
		lapse_time++;
	}else
	if(input == COUNTERCLOCKWISE && lapse_time > 0)
	{
		lapse_time--;
	}
	showMenu();
}

void menuSetAngle(void)
{
	showMenu();
}

void setAngle(void)
{
	if(input == CLOCKWISE && turn_angle < MAX_VALUE)
	{
		turn_angle++;
	}else
	if(input == COUNTERCLOCKWISE && turn_angle > 0)
	{
		turn_angle--;
	}
	showMenu();
}

void menuSetShot(void)
{
	showMenu();
}

void setShot(void)
{
	if(input == CLOCKWISE && shot_time < MAX_VALUE)
	{
		shot_time++;
	}else
	if(input == COUNTERCLOCKWISE && shot_time > 0)
	{
		shot_time--;
	}
	showMenu();
}

void menuRun(void)
{
	if(input == BUTTON_PUSH)
	{
		uint16_t turn_time = lapse_time / turn_angle;
		if(turn_time < shot_time)
		{
			turn_time = shot_time;
		}

		for(uint16_t i = 0; i < turn_angle; i++)
		{
			camera_shot();
			delay_ms((turn_time - shot_time) * 1000);	//TODO убрать коэфицент, добавить поправку на время поворота платформы
			motor_turn(turn_angle);
			IO004_TogglePin(IO004_Handle6);
		}
	}
	showMenu();
}

void run(void)
{
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
