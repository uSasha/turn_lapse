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
#define MENU_SET_SHUTTER	0
#define SET_SHUTTER			1
#define MENU_SET_ANGLE		2
#define SET_ANGLE			3
#define MENU_SET_TIME		4
#define SET_TIME			5
#define MENU_SET_TURN		6
#define SET_TURN			7
#define MENU_SET_SHOTS		8
#define SET_SHOTS			9
#define MENU_RUN			10

//#define NUMBER_OF_STATES	7
#define NUMBER_OF_STATES	11

#define MAX_VALUE					100


void menuSetTime(void);
void setTime(void);
void menuSetAngle(void);
void setAngle(void);
void menuSetShutter(void);
void setShutter(void);
void menuRun(void);
void run(void);
void showMenu(void);
void menuSetTurn(void);
void setTurn(void);
void menuSetShots(void);
void setShots(void);
//void (void);


extern uint16_t data;
uint16_t input;
unsigned long state	= MENU_SET_TIME; // index into current state
// globals that rule timelapse behavior
uint32_t time = 0;
uint32_t angle = 0;
uint32_t shutter = 0;
uint32_t turn = 0;
uint32_t shots = 0;


// Linked data structure
struct State
{
	void (*CmdPt)(void);
	char str[12];
	unsigned long next[NUMBER_OF_STATES];
};

typedef const struct State STyp;

STyp FSM[NUMBER_OF_STATES]=
{	// output			message 		'CLOCKWISE'			'COUNTERCLOWISE'	'BUTTON_PUSH'
	{&menuSetShutter,	"shutter",		{MENU_SET_ANGLE,	MENU_RUN,			SET_SHUTTER			}},
	{&setShutter,		"",				{SET_SHUTTER,		SET_SHUTTER,		MENU_SET_SHUTTER	}},
	{&menuSetAngle,		"angle  ",		{MENU_SET_TIME,		MENU_SET_SHUTTER,	SET_ANGLE			}},
	{&setAngle,			"",				{SET_ANGLE,			SET_ANGLE,			MENU_SET_ANGLE		}},
	{&menuSetTime,		"time   ",		{MENU_SET_TURN,		MENU_SET_ANGLE,		SET_TIME			}},
	{&setTime,			"",				{SET_TIME,			SET_TIME,			MENU_SET_TIME		}},
	{&menuSetTurn,		"turn   ",		{MENU_SET_SHOTS,	MENU_SET_TIME,		SET_TURN			}},
	{&setTurn,			"",				{SET_TURN,			SET_TURN,			MENU_SET_TURN		}},
	{&menuSetShots,		"shots  ",		{MENU_RUN,			MENU_SET_TURN,		SET_SHOTS			}},
	{&setShots,			"",				{SET_SHOTS,			SET_SHOTS,			MENU_SET_SHOTS		}},
	{&menuRun,			"run    ",		{MENU_SET_SHUTTER,	MENU_SET_SHOTS,		MENU_RUN			}}
};
/*
STyp FSM[NUMBER_OF_STATES]=
{	// output		message 		'CLOCKWISE'			'COUNTERCLOWISE'	'BUTTON_PUSH'
	{&menuSetTime,	"time   ",		{MENU_SET_ANGLE,	MENU_RUN,			SET_TIME		}},
	{&setTime,		"",				{SET_TIME,			SET_TIME,			MENU_SET_TIME	}},
	{&menuSetAngle,	"angle  ",		{MENU_SET_SHOT,		MENU_SET_TIME,		SET_ANGLE		}},
	{&setAngle,		"",				{SET_ANGLE,			SET_ANGLE,			MENU_SET_ANGLE	}},
	{&menuSetShot,	"shot   ",		{MENU_RUN,			MENU_SET_ANGLE,		SET_SHOT		}},
	{&setShutter,		"",				{SET_SHUTTER,			SET_SHUTTER,			MENU_SET_SHUTTER	}},
	{&menuRun,		"run    ",		{MENU_SET_TIME,		MENU_SET_SHUTTER,		MENU_RUN		}}
};
*/

void process_states(void)
{
	input = encoder_getInput();						// get input
	if(input != NO_INPUT)
	{
		state = FSM[state].next[input];		// change state
		(FSM[state].CmdPt)();				// call output function
	}
	input = NO_INPUT;						// clear input
}

void state_machine_init(void)
{
	state = MENU_SET_SHUTTER;
	showMenu();
}

void menuSetTime(void)
{
	showMenu();
}

void setTime(void)
{
	if(input == CLOCKWISE && time < MAX_VALUE)
	{
		time++;
	}else
	if(input == COUNTERCLOCKWISE && time > 0)
	{
		time--;
	}
	showMenu();
}

void menuSetAngle(void)
{
	showMenu();
}

void setAngle(void)
{
	if(input == CLOCKWISE && angle < MAX_VALUE)
	{
		angle++;
	}else
	if(input == COUNTERCLOCKWISE && angle > 0)
	{
		angle--;
	}
	showMenu();
}

void menuSetShutter(void)
{
	showMenu();
}

void setShutter(void)
{
	if(input == CLOCKWISE && shutter < MAX_VALUE)
	{
		shutter++;
	}else
	if(input == COUNTERCLOCKWISE && shutter > 0)
	{
		shutter--;
	}
	showMenu();
}

void menuRun(void)
{
	if(input == BUTTON_PUSH)
	{
		uint16_t turn_time = time / angle;
		if(turn_time < shutter)
		{
			turn_time = shutter;
		}

		for(uint16_t i = 0; i < angle; i++)
		{
			camera_shot();
			delay_ms((turn_time - shutter) * 1000);	//TODO убрать коэфицент, добавить поправку на время поворота платформы
			motor_turn(angle);
			IO004_TogglePin(IO004_Handle6);
		}
	}
	showMenu();
}

void menuSetTurn(void)
{
	showMenu();
}
void setTurn(void)
{
	if(input == CLOCKWISE && time < MAX_VALUE)
	{
		turn += 10;
	}else
	if(input == COUNTERCLOCKWISE && time > 0)
	{
		turn -= 10;
	}
	showMenu();
}
void menuSetShots(void)
{
	showMenu();
}
void setShots(void)
{
	if(input == CLOCKWISE && time < MAX_VALUE)
	{
		shots++;
	}else
	if(input == COUNTERCLOCKWISE && time > 0)
	{
		shots--;
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
					sprintf(str, "%d", (int)time);
					break;
				case SET_ANGLE:
					sprintf(str, "%d", (int)angle);
					break;
				case SET_SHUTTER:
					sprintf(str, "%d", (int)shutter);
					break;
				case SET_TURN:
					sprintf(str, "%d", (int)turn);
					break;
				case SET_SHOTS:
					sprintf(str, "%d", (int)shots);
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
