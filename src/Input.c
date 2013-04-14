#include "includes.h"

int JoyStickEnabled=0;

int Player1Keyboard[12];
int Player2Keyboard[12];
JoyButton Player1Joystick[12];
JoyButton Player2Joystick[12];
JoyAxe Player1JoyAxes[12];
JoyAxe Player2JoyAxes[12];

void LoadInput(){
    Player1Keyboard[UP]=KEY_UP;
    Player1Keyboard[DOWN]=KEY_DOWN;
    Player1Keyboard[LEFT]=KEY_LEFT;
    Player1Keyboard[RIGHT]=KEY_RIGHT;
    Player1Keyboard[ENTER]=KEY_ENTER;
    Player1Keyboard[RETURN]=KEY_ESC;
    Player1Keyboard[PUNCH]=KEY_W;
    Player1Keyboard[KICK]=KEY_X;


    Player2Joystick[ENTER].JoyNumber=0;
    Player2Joystick[RETURN].JoyNumber=0;
    Player2Joystick[PUNCH].JoyNumber=0;
    Player2Joystick[KICK].JoyNumber=0;

    Player2Joystick[ENTER].InUse=1;
    Player2Joystick[RETURN].InUse=1;
    Player2Joystick[PUNCH].InUse=1;
    Player2Joystick[KICK].InUse=1;

    Player2Joystick[ENTER].ButtonNumber=9;
    Player2Joystick[RETURN].ButtonNumber=8;
    Player2Joystick[PUNCH].ButtonNumber=2;
    Player2Joystick[KICK].ButtonNumber=3;

    Player2JoyAxes[UP].InUse=1;
    Player2JoyAxes[DOWN].InUse=1;
    Player2JoyAxes[LEFT].InUse=1;
    Player2JoyAxes[RIGHT].InUse=1;

    Player2JoyAxes[UP].StickNumber=0;
    Player2JoyAxes[DOWN].StickNumber=0;
    Player2JoyAxes[LEFT].StickNumber=0;
    Player2JoyAxes[RIGHT].StickNumber=0;

    Player2JoyAxes[UP].direction=UP;
    Player2JoyAxes[DOWN].direction=DOWN;
    Player2JoyAxes[LEFT].direction=LEFT;
    Player2JoyAxes[RIGHT].direction=RIGHT;

}

int IsKeyPressed(int player, ACTIONS action)
{

    switch(player)
    {
    case 1:
        return key[Player1Keyboard[action]] ||
                (JoyStickEnabled &&(
                (Player1Joystick[action].InUse && joy[Player1Joystick[action].JoyNumber].button[Player1Joystick[action].ButtonNumber].b) ||
                (Player1JoyAxes[action].InUse && JoyAxeMoved(Player1JoyAxes[action].JoyNumber,Player1JoyAxes[action].StickNumber,Player1JoyAxes[action].direction))
                 ));
               break;

    case 2:
        return key[Player2Keyboard[action]] ||
                (JoyStickEnabled &&(
                (Player2Joystick[action].InUse && joy[Player2Joystick[action].JoyNumber].button[Player2Joystick[action].ButtonNumber].b) ||
                (Player2JoyAxes[action].InUse && JoyAxeMoved(Player2JoyAxes[action].JoyNumber,Player2JoyAxes[action].StickNumber,Player2JoyAxes[action].direction))
                 ));
               break;
    }
    return 0;
}

int JoyAxeMoved(int joyNumber,int stick, ACTIONS direction){

    if(direction== LEFT){
        return joy[joyNumber].stick[stick].axis[0].d1;
    }
    if(direction== RIGHT){
        return joy[joyNumber].stick[stick].axis[0].d2;
    }
    if(direction== UP){
      return joy[joyNumber].stick[stick].axis[1].d1;
    }
    if(direction== DOWN){
       return joy[joyNumber].stick[stick].axis[1].d2;
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
    int i,j,JoyPressed=0,StickMoved=0;
    JoyButton button;
    JoyAxe axe;

    if(!JoyStickEnabled)
        return 0;


    JoyPressed=0;
    StickMoved=0;
    while(!JoyPressed && !StickMoved)
    {
        poll_joystick();
        for(i=0; i<num_joysticks && (!JoyPressed) && (!StickMoved); i++)
        {
            for(j=0; j<joy[i].num_buttons && (!JoyPressed) && (!StickMoved); j++)
            {
                JoyPressed=joy[i].button[j].b;
                if(JoyPressed)
                {
                    button.JoyNumber=i;
                    button.ButtonNumber=j;
                }
            }
            for(j=0; j<joy[i].num_sticks && (!JoyPressed) && (!StickMoved); j++)
            {
                axe.direction=0;
                if (joy[i].stick[j].axis[0].d1) {
                    axe.direction =  LEFT;
                }
                if (joy[i].stick[j].axis[0].d2) {
                    axe.direction =  RIGHT;
                }
                if (joy[i].stick[j].axis[1].d1) {
                    axe.direction =  UP;
                }
                if (joy[i].stick[j].axis[1].d2) {
                    axe.direction =  DOWN;
                }

                if(axe.direction){
                    StickMoved=1;
                    axe.JoyNumber=i;
                    axe.StickNumber=j;
                }
            }
        }
        rest(10);
    }

//TODO : Handle buttons and Sticks
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
