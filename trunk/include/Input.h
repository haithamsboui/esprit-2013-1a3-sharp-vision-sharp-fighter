#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "includes.h"

int JoyStickEnabled; //Check if Joystick plugged.

typedef enum {UP,DOWN,LEFT,RIGHT,PUNCH,KICK,FIREBALL,FREEZE,THUNDER,WIND,ENTER,RETURN} ACTIONS;

typedef struct {
    int InUse;
    int JoyNumber;
    int ButtonNumber;
} JoyButton;

typedef struct {
    int InUse;
    int JoyNumber;
    int StickNumber;
    ACTIONS direction;
} JoyAxe;


int Player1Keyboard[12];
int Player2Keyboard[12];
int Player1Joypad[12];
int Player2Joypad[12];

JoyButton Player1Joystick[12];
JoyButton Player2Joystick[12];
JoyAxe Player1JoyAxes[12];
JoyAxe Player2JoyAxes[12];

void LoadInput();


int IsKeyPressed(int player, ACTIONS action);
int JoyAxeMoved(int joyNumber,int stick, ACTIONS direction);

void ProcessKeys();

int ReadKeyboard(int player, ACTIONS action);
int ReadJoystick(int player, ACTIONS action);

//int KeyAlreadyUsed(ACTIONS)

#endif // INPUT_H_INCLUDED
