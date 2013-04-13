#include "includes.h"

int JoyStickEnabled=0;

int Player1Keyboard[12];
int Player2Keyboard[12];
JoyButton Player1Joystick[12];
JoyButton Player2Joystick[12];

int IsKeyPressed(int player, ACTIONS action)
{

    switch(player)
    {
    case 1:
        return key[Player1Keyboard[action]] || (JoyStickEnabled && joy[Player1Joystick[action].JoyNumber].button[Player1Joystick[action].ButtonNumber].b);
               break;

    case 2:
        return key[Player2Keyboard[action]] || (JoyStickEnabled && joy[Player2Joystick[action].JoyNumber].button[Player2Joystick[action].ButtonNumber].b);
               break;
    }
    return 0;
}

void ProcessKeys()
{
    if(keyboard_needs_poll())
    {
        poll_keyboard();
    }
    if(JoyStickEnabled){
        poll_joystick();
    }
}

int ReadKeyboard(int player, ACTIONS action)
{
    switch(player)
    {
    case 1:
        Player1Keyboard[action]=readkey();
        break;

    case 2:
        Player2Keyboard[action]=readkey();
        break;
    }
    return 1;
}

int ReadJoystick(int player, ACTIONS action)
{
    int i,j,JoyPressed=0;
    JoyButton button;

    if(!JoyStickEnabled)
        return 0;


    while(!JoyPressed)
    {
        poll_joystick();
        for(i=0; i<num_joysticks && (!JoyPressed); i++)
        {
            for(j=0; j<joy[i].num_buttons && (!JoyPressed); j++)
            {
                JoyPressed=joy[i].button[j].b;
                if(JoyPressed)
                {
                    button.JoyNumber=i;
                    button.ButtonNumber=j;
                }
            }
        }
        rest(10);
    }


    switch(player)
    {
    case 1:
        Player1Joystick[action]=button;
        break;

    case 2:
        Player2Joystick[action]=button;
        break;
    }
    return 1;
}
