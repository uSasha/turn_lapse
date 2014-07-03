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
#define NUMBER_OF_STATES	11



void menuSetTime(void);
void setTime(void);
void menuSetAngle(void);
void setAngle(void);
void menuSetShutter(void);
void setShutter(void);
void menuSetTurn(void);
void setTurn(void);
void menuSetShots(void);
void setShots(void);
void menuRun(void);
void run(void);
void showMenu(void);
void setValue(void);
void computeValue(void);

extern uint16_t data;
uint16_t input;
unsigned long state	= MENU_SET_TIME; // index into current state
// globals that rule timelapse behavior
uint32_t time 		= 1;		// minutes
uint32_t angle 		= 90;		// degrees
uint32_t shutter 	= 1;	// seconds / 2
uint32_t turn 		= 1;		// one turn angle degrees
uint32_t shots 		= 1;


// Linked data structure
struct State
{
	void (*CmdPt)(void);
	char str[12];
	unsigned long next[NUMBER_OF_BUTTONS];
	uint32_t *var_ptr;
	uint32_t step;
	uint32_t min;
	uint32_t max;
};

typedef const struct State STyp;

STyp FSM[NUMBER_OF_STATES]=
{	// output			message 		'CLOCKWISE'			'COUNTERCLOWISE'	'BUTTON_PUSH'		variable	step	min		max
	{&menuSetShutter,	"shutter",		{MENU_SET_ANGLE,	MENU_RUN,			SET_SHUTTER},		&shutter,	0,		0,		0	},
	{&setShutter,		"",				{SET_SHUTTER,		SET_SHUTTER,		MENU_SET_SHUTTER},	&shutter,	1,		1,		240	},	// seconds/2
	{&menuSetAngle,		"angle  ",		{MENU_SET_TIME,		MENU_SET_SHUTTER,	SET_ANGLE},			&angle,		0,		0,		0	},
	{&setAngle,			"",				{SET_ANGLE,			SET_ANGLE,			MENU_SET_ANGLE},	&angle,		10,		10,		360	},	// degrees
	{&menuSetTime,		"time   ",		{MENU_SET_TURN,		MENU_SET_ANGLE,		SET_TIME},			&time,		0,		0,		0	},
	{&setTime,			"",				{SET_TIME,			SET_TIME,			MENU_SET_TIME},		&time,		1,		1,		360	},	// minutes
	{&menuSetTurn,		"turn   ",		{MENU_SET_SHOTS,	MENU_SET_TIME,		SET_TURN},			&turn,		0,		0,		0	},
	{&setTurn,			"",				{SET_TURN,			SET_TURN,			MENU_SET_TURN},		&turn,		1,		1,		10	},	// dergees
	{&menuSetShots,		"shots  ",		{MENU_RUN,			MENU_SET_TURN,		SET_SHOTS},			&shots,		0,		0,		0	},
	{&setShots,			"",				{SET_SHOTS,			SET_SHOTS,			MENU_SET_SHOTS},	&shots,		10,		10,		360	},	// number
	{&menuRun,			"run    ",		{MENU_SET_SHUTTER,	MENU_SET_SHOTS,		MENU_RUN},			&shutter,	0,		0,		0	}
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
	setValue();
	computeValue();
	showMenu();
}

void menuSetAngle(void)
{
	showMenu();
}

void setAngle(void)
{
	setValue();
	computeValue();
	showMenu();
}

void menuSetShutter(void)
{
	showMenu();
}

void setShutter(void)
{
	setValue();
	computeValue();
	showMenu();
}


void menuSetTurn(void)
{
	showMenu();
}


void setTurn(void)
{
	setValue();
	computeValue();
	showMenu();
}


void menuSetShots(void)
{
	showMenu();
}


void setShots(void)
{
	setValue();
	computeValue();
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


void showMenu(void)
{
	uint8_t y = 0;
	delay_ms(2);
	display_clear();
	delay_ms(2);
	display_gotoXY(0, 0);
	delay_ms(2);

	for(uint8_t i = 0; i < NUMBER_OF_STATES; i++)
	{
		if(i == state)			// draw cursor near current state name
		{
			display_string(">");
		}else
		{
			display_string(" ");
		}

		display_string(FSM[i].str);
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
			display_string(str);
			y++;					// new line
			delay_ms(2);
			display_gotoXY(0, y);
			delay_ms(2);
		}
		delay_ms(2);
	}
}


void setValue(void)
{
	if(input == CLOCKWISE && *FSM[state].var_ptr < FSM[state].max)
	{
		*FSM[state].var_ptr += FSM[state].step;
	}else
	if(input == COUNTERCLOCKWISE && *FSM[state].var_ptr > FSM[state].min)
	{
		*FSM[state].var_ptr -= FSM[state].step;
	}
}


void computeValue(void)
{
	switch (state)
	{
	case SET_SHUTTER:

	case SET_ANGLE:
		time = shutter * angle / turn / 120;	// seconds/2 -> minutes
		if(time > FSM[SET_TIME].max)
		{
			time = FSM[SET_TIME].max;
		}else
		if(time < FSM[SET_TIME].min)
		{
			time = FSM[SET_TIME].min;
		}
	case SET_TIME:
		turn = angle * shutter / time / 120;	// seconds/2 -> minutes
		if(turn > FSM[SET_TURN].max)
		{
			turn = FSM[SET_TURN].max;
		}else
		if(turn < FSM[SET_TURN].min)
		{
			turn = FSM[SET_TURN].min;
		}

	case SET_TURN:
		shots = angle / turn;
		if(shots > FSM[SET_SHOTS].max)
		{
			shots = FSM[SET_SHOTS].max;
		}else
		if(shots < FSM[SET_SHOTS].min)
		{
			shots = FSM[SET_SHOTS].min;
		}

	case SET_SHOTS:
		break;
	}
}

