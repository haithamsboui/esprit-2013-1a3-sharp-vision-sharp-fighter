#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "includes.h"

int JoyStickEnabled; //Check if Joystick plugged.

typedef enum {UP,DOWN,LEFT,RIGHT,PUNCH,KICK,DEFENCE,FIREBALL,FREEZE,THUNDER,WIND,ENTER,RETURN,ACTIONSCOUNT} ACTIONS;

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


int Player1Keyboard[ACTIONSCOUNT];
int Player2Keyboard[ACTIONSCOUNT];
int Player1Joypad[ACTIONSCOUNT];
int Player2Joypad[ACTIONSCOUNT];

JoyButton Player1Joystick[ACTIONSCOUNT];
JoyButton Player2Joystick[ACTIONSCOUNT];
JoyAxe Player1JoyAxes[ACTIONSCOUNT];
JoyAxe Player2JoyAxes[ACTIONSCOUNT];

void LoadInput();


int IsKeyPressed(int player, ACTIONS action);
int AnyKeyPressed(int player);
int JoyAxeMoved(int joyNumber,int stick, ACTIONS direction);

void ProcessKeys();

int ReadKeyboard(int player, ACTIONS action);
int ReadJoystick(int player, ACTIONS action);

//int KeyAlreadyUsed(ACTIONS)

#endif // INPUT_H_INCLUDED
