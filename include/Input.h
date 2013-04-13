#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "includes.h"

int JoyStickEnabled; //Check if Joystick plugged.

typedef enum {UP,DOWN,LEFT,RIGHT,PUNCH,KICK,FIREBALL,FREEZE,THUNDER,WIND,ENTER,RETURN} ACTIONS;

typedef struct {
    int JoyNumber;
    int ButtonNumber;
} JoyButton;


int Player1Keyboard[12];
int Player2Keyboard[12];
JoyButton Player1Joystick[12];
JoyButton Player2Joystick[12];

int IsKeyPressed(int player, ACTIONS action);

void ProcessKeys();

int ReadKeyboard(int player, ACTIONS action);
int ReadJoystick(int player, ACTIONS action);

//int KeyAlreadyUsed(ACTIONS)

#endif // INPUT_H_INCLUDED
