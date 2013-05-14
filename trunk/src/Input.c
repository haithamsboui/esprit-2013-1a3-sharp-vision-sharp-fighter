#include "includes.h"

int JoyStickEnabled=0;

int Player1Keyboard[13];
int Player2Keyboard[13];
int Player1Joypad[13];
int Player2Joypad[13];

JoyButton Player1Joystick[12];
JoyButton Player2Joystick[12];
JoyAxe Player1JoyAxes[12];
JoyAxe Player2JoyAxes[12];

void LoadInput()
{
    int i,defaultkeyboardP1[]= {KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT,KEY_W,KEY_X,KEY_C,KEY_Q,KEY_F,KEY_S,KEY_D,KEY_ENTER,KEY_ESC},
                               defaultkeyboardP2[]= {KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT,KEY_W,KEY_X,KEY_C,KEY_Q,KEY_F,KEY_S,KEY_D,KEY_ENTER,KEY_ESC},
                                       defaultjoybuttonP2[]= {0,0,0,0,1,2,3,4,5,6,7,9,8},defaultjoybuttonP1[]= {0,0,0,0,1,2,3,4,5,6,7,9,8} ;
    char buffer[50];
    set_config_file("Resources/Setting.cfg");
    for (i=0; i<13; i++)
    {
        sprintf(buffer,"Player1Keyboard[%d]",i);
        Player1Keyboard[i]=get_config_int("input",buffer,defaultkeyboardP1[i]);
        sprintf(buffer,"Player2Keyboard[%d]",i);
        Player2Keyboard[i]=get_config_int("input",buffer,defaultkeyboardP2[i]);

        if(JoyStickEnabled)
        {
            sprintf(buffer,"Player2Joystick[%d].InUse",i);
            Player2Joystick[i].InUse=get_config_int("input",buffer,0);

            sprintf(buffer,"Player2Joystick[%d].JoyNumber",i);
            Player2Joystick[i].JoyNumber=get_config_int("input",buffer,0);

            sprintf(buffer,"Player2Joystick[%d].ButtonNumber",i);
            Player2Joystick[i].ButtonNumber=get_config_int("input",buffer,defaultjoybuttonP2[i]);

            sprintf(buffer,"Player2JoyAxes[%d].InUse",i);
            Player2JoyAxes[i].InUse=get_config_int("input",buffer,0);

            sprintf(buffer,"Player2JoyAxes[%d].JoyNumber",i);
            Player2JoyAxes[i].JoyNumber=get_config_int("input",buffer,0);

            sprintf(buffer,"Player2JoyAxes[%d].StickNumber",i);
            Player2JoyAxes[i].StickNumber=get_config_int("input",buffer,0);

            sprintf(buffer,"Player2JoyAxes[%d].direction",i);
            Player2JoyAxes[i].direction=get_config_int("input",buffer,0);


            sprintf(buffer,"Player1Joystick[%d].InUse",i);
            Player1Joystick[i].InUse=get_config_int("input",buffer,0);

            sprintf(buffer,"Player1Joystick[%d].JoyNumber",i);
            Player1Joystick[i].JoyNumber=get_config_int("input",buffer,1);

            sprintf(buffer,"Player1Joystick[%d].ButtonNumber",i);
            Player1Joystick[i].ButtonNumber=get_config_int("input",buffer,defaultjoybuttonP1[i]);

            sprintf(buffer,"Player1JoyAxes[%d].InUse",i);
            Player1JoyAxes[i].InUse=get_config_int("input",buffer,0);

            sprintf(buffer,"Player1JoyAxes[%d].JoyNumber",i);
            Player1JoyAxes[i].JoyNumber=get_config_int("input",buffer,1);

            sprintf(buffer,"Player1JoyAxes[%d].StickNumber",i);
            Player1JoyAxes[i].StickNumber=get_config_int("input",buffer,0);

            sprintf(buffer,"Player1JoyAxes[%d].direction",i);
            Player1JoyAxes[i].direction=get_config_int("input",buffer,0);

        }
    }

    for(i=0; i<13; i++)
    {
        if(Player1Joystick[i].InUse)
        {
            Player1Joypad[i]=Player1Joystick[i].ButtonNumber;
        }
        if(Player1JoyAxes[i].InUse)
        {
            Player1Joypad[i]=10 + Player1JoyAxes[i].direction;
        }
        if(Player2Joystick[i].InUse)
        {
            Player2Joypad[i]=Player2Joystick[i].ButtonNumber;
        }
        if(Player2JoyAxes[i].InUse)
        {
            Player2Joypad[i]=10 + Player2JoyAxes[i].direction;
        }
    }
}

int AnyKeyPressed(int player)
{
    int i,pressed=0;

    for(i=0; i<ACTIONSCOUNT && !pressed; i++)
    {
        pressed=pressed || IsKeyPressed(player,i);
    }
    return pressed;

}

int IsKeyPressed(int player, ACTIONS action)
{
    int ispressed=0;
    if(player & 1)
    {

        ispressed = key[Player1Keyboard[action]] ||
                    (JoyStickEnabled &&(
                         (Player1Joystick[action].InUse && Player1Joystick[action].JoyNumber<num_joysticks && joy[Player1Joystick[action].JoyNumber].button[Player1Joystick[action].ButtonNumber].b) ||
                         (Player1JoyAxes[action].InUse && Player1JoyAxes[action].JoyNumber<num_joysticks && JoyAxeMoved(Player1JoyAxes[action].JoyNumber,Player1JoyAxes[action].StickNumber,Player1JoyAxes[action].direction))
                     ));
    }

    if(player & 2)
    {
        ispressed =  ispressed || (key[Player2Keyboard[action]] ||
                                   (JoyStickEnabled &&(
                                        (Player2Joystick[action].InUse && Player2Joystick[action].JoyNumber<num_joysticks && joy[Player2Joystick[action].JoyNumber].button[Player2Joystick[action].ButtonNumber].b) ||
                                        (Player2JoyAxes[action].InUse && Player2JoyAxes[action].JoyNumber<num_joysticks && JoyAxeMoved(Player2JoyAxes[action].JoyNumber,Player2JoyAxes[action].StickNumber,Player2JoyAxes[action].direction))
                                    )));


    }

    return ispressed;
}

int JoyAxeMoved(int joyNumber,int stick, ACTIONS direction)
{

    if(direction== LEFT)
    {
        return joy[joyNumber].stick[stick].axis[0].d1;
    }
    if(direction== RIGHT)
    {
        return joy[joyNumber].stick[stick].axis[0].d2;
    }
    if(direction== UP)
    {
        return joy[joyNumber].stick[stick].axis[1].d1;
    }
    if(direction== DOWN)
    {
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
    if(JoyStickEnabled)
    {
        poll_joystick();
    }
}

int ReadKeyboard(int player, ACTIONS action)
{
    char buffer[50];
    int TempKeyRead,KeyExist=0,i,temp;
    set_config_file("Resources/Setting.cfg");
    switch(player)
    {
    case 1:
        TempKeyRead=readkey()>>8;
        for (i=0; i<13; i++)
        {
            if (TempKeyRead==Player1Keyboard[i])
            {
                KeyExist=1;
                break;
            }
        }
        if (KeyExist==1)
        {
            temp=Player1Keyboard[action];
            Player1Keyboard[action]=TempKeyRead;
            Player1Keyboard[i]=temp;
            sprintf(buffer,"Player1Keyboard[%d]",action);
            set_config_int("input",buffer,Player1Keyboard[action]);
            sprintf(buffer,"Player1Keyboard[%d]",i);
            set_config_int("input",buffer,Player1Keyboard[i]);
        }
        else
        {
            Player1Keyboard[action]=TempKeyRead;
            sprintf(buffer,"Player1Keyboard[%d]",action);
            set_config_int("input",buffer,Player1Keyboard[action]);
        }
        break;

    case 2:
        TempKeyRead=readkey()>>8;
        for (i=0; i<13; i++)
        {
            if (TempKeyRead==Player2Keyboard[i])
            {
                KeyExist=1;
            }
        }
        if (KeyExist==1)
        {
            temp=Player1Keyboard[action];
            Player2Keyboard[action]=TempKeyRead;
            Player2Keyboard[i]=temp;
            sprintf(buffer,"Player2Keyboard[%d]",action);
            set_config_int("input",buffer,Player2Keyboard[action]);
            sprintf(buffer,"Player2Keyboard[%d]",i);
            set_config_int("input",buffer,Player2Keyboard[i]);
        }
        else
        {
            Player2Keyboard[action]=TempKeyRead;
            sprintf(buffer,"Player2Keyboard[%d]",action);
            set_config_int("input",buffer,Player2Keyboard[action]);
        }
        break;
    }
    flush_config_file();
    return 1;
}


int ReadJoystick(int player, ACTIONS action)
{
    int i,j,JoyPressed=0,StickMoved=0;
    JoyButton button;
    JoyAxe axe;
    char buffer[50];

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
                    button.InUse=1;
                    button.JoyNumber=i;
                    button.ButtonNumber=j;
                }
            }
            for(j=0; j<joy[i].num_sticks && (!JoyPressed) && (!StickMoved); j++)
            {
                axe.direction=-1;
                if (joy[i].stick[j].axis[0].d1)
                {
                    axe.direction =  LEFT;
                }
                if (joy[i].stick[j].axis[0].d2)
                {
                    axe.direction =  RIGHT;
                }
                if (joy[i].stick[j].axis[1].d1)
                {
                    axe.direction =  UP;
                }
                if (joy[i].stick[j].axis[1].d2)
                {
                    axe.direction =  DOWN;
                }

                if(axe.direction!=-1)
                {
                    StickMoved=1;
                    axe.InUse=1;
                    axe.JoyNumber=i;
                    axe.StickNumber=j;
                }
            }
        }
        rest(10);
    }

    set_config_file("Resources/Setting.cfg");
    switch(player)
    {
    case 1:
        if(JoyPressed)
        {
            sprintf(buffer,"Player1Joystick[%d].InUse",action);
            set_config_int("input",buffer,0);

            Player1Joystick[action]=button;
            Player1Joypad[action]=button.ButtonNumber;

            sprintf(buffer,"Player1Joystick[%d].InUse",action);
            set_config_int("input",buffer,Player1Joystick[action].InUse);
            sprintf(buffer,"Player1Joystick[%d].JoyNumber",action);
            set_config_int("input",buffer,Player1Joystick[action].JoyNumber);
            sprintf(buffer,"Player1Joystick[%d].ButtonNumber",action);
            set_config_int("input",buffer,Player1Joystick[action].ButtonNumber);
        }
        if(StickMoved)
        {
            sprintf(buffer,"Player1JoyAxes[%d].InUse",action);
            set_config_int("input",buffer,0);

            Player1JoyAxes[action]=axe;
            Player1Joypad[action]=10+axe.direction;

            sprintf(buffer,"Player1JoyAxes[%d].InUse",action);
            set_config_int("input",buffer,Player1JoyAxes[action].InUse);
            sprintf(buffer,"Player1JoyAxes[%d].JoyNumber",action);
            set_config_int("input",buffer,Player1JoyAxes[action].JoyNumber);
            sprintf(buffer,"Player1JoyAxes[%d].StickNumber",action);
            set_config_int("input",buffer,Player1JoyAxes[action].StickNumber);
            sprintf(buffer,"Player1JoyAxes[%d].direction",action);
            set_config_int("input",buffer,Player1JoyAxes[action].direction);
        }
        break;

    case 2:
        if(JoyPressed)
        {
            sprintf(buffer,"Player2Joystick[%d].InUse",action);
            set_config_int("input",buffer,0);

            Player2Joystick[action]=button;
            Player2Joypad[action]=button.ButtonNumber;

            sprintf(buffer,"Player2Joystick[%d].InUse",action);
            set_config_int("input",buffer,Player2Joystick[action].InUse);
            sprintf(buffer,"Player2Joystick[%d].JoyNumber",action);
            set_config_int("input",buffer,Player2Joystick[action].JoyNumber);
            sprintf(buffer,"Player2Joystick[%d].ButtonNumber",action);
            set_config_int("input",buffer,Player2Joystick[action].ButtonNumber);
        }
        if(StickMoved)
        {
            sprintf(buffer,"Player2JoyAxes[%d].InUse",action);
            set_config_int("input",buffer,0);

            Player2JoyAxes[action]=axe;
            Player2Joypad[action]=10+axe.direction;

            sprintf(buffer,"Player2JoyAxes[%d].InUse",action);
            set_config_int("input",buffer,Player2JoyAxes[action].InUse);
            sprintf(buffer,"Player2JoyAxes[%d].JoyNumber",action);
            set_config_int("input",buffer,Player2JoyAxes[action].JoyNumber);
            sprintf(buffer,"Player2JoyAxes[%d].StickNumber",action);
            set_config_int("input",buffer,Player2JoyAxes[action].StickNumber);
            sprintf(buffer,"Player2JoyAxes[%d].direction",action);
            set_config_int("input",buffer,Player2JoyAxes[action].direction);
        }

        break;
    }
    flush_config_file();
    rest(25);
    return 1;
}

