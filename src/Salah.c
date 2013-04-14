#include "includes.h"

#define StableStart 0
#define StableCount 3

#define WalkStart 9
#define WalkCount 4

#define KickStart 19
#define KickCount 4

#define PunchStart 14
#define PunchCount 5

IMAGE *SalahPics[51];

float x,y;
float w,h;
int direction;
int Player=0;
EtatSalah etat;
int Index;
float screen_ratio;

void LoadSalah(int player)
{
    int i;
    char path[255];
    for (i=0; i<51; i++)
    {
        sprintf(path,"Resources/Images/Salah/GamePlay/%d.png",i);
        SalahPics[i]=load_image(path);
    }

    Player=player;
    etat=Stable;
    Index=0;
    y=55;
    w=10;
    h=40;


    switch(player)
    {
    case 1:
        direction=1;
        x=10;
        break;
    case 2:
        direction=0;
        x=70;
        break;
    }
    screen_ratio=(float)SCREEN_W/(float)SCREEN_H;
}

int i=1;
void Draw_Salah()
{
    flip vflip;

    if(direction)
        vflip=NONE;
    else
        vflip = VERTICAL;

    if(etat!=Kick && etat!=Punch)
    {
        if(IsKeyPressed(Player,KICK))
        {
            etat=Kick;
            Index=0;
        }
        else if(IsKeyPressed(Player,PUNCH))
        {
            etat=Punch;
            Index=0;
        }
        else if(IsKeyPressed(Player,RIGHT))
        {
            etat=Forward;
            x+=0.2;
        }
        else if (IsKeyPressed(Player,LEFT))
        {
            etat=Backward;
            x-=0.2;
        }
        else
            etat=Stable;
    }


    switch(etat)
    {
    case Stable:
        if(FrameCount%13==0)
        {
            if(Index==0)
                i=1;
            if(Index>=StableCount-1)
                i=-1;

            Index=Index+i;
        }
        Index = Min(Index,StableCount-1);
        w=(h/((float)SalahPics[Index+StableStart]->h/(float)SalahPics[Index+StableStart]->w))/screen_ratio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+StableStart],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        break;
    case Forward:
        if(FrameCount%10==0)
        {
            Index=((Index-1+WalkCount)%WalkCount);
        }
        Index = Min(Index,WalkCount-1);
        w=(h/((float)SalahPics[Index+WalkStart]->h/(float)SalahPics[Index+WalkStart]->w))/screen_ratio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+WalkStart],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        break;

    case Backward:
        if(FrameCount%10==0)
        {
            Index=((Index+1)%WalkCount);
        }
        Index = Min(Index,WalkCount-1);
        w=(h/((float)SalahPics[Index+WalkStart]->h/(float)SalahPics[Index+WalkStart]->w))/screen_ratio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+WalkStart],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        break;

    case Kick:
        w=(h/((float)SalahPics[Index+KickStart]->h/(float)SalahPics[Index+KickStart]->w))/screen_ratio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+KickStart],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        if(FrameCount%10==0)
        {
            Index++;
            if(Index==KickCount)
            {
                etat=Stable;
            }
        }

        break;

    case Punch:
        w=(h/((float)SalahPics[Index+PunchStart]->h/(float)SalahPics[Index+PunchStart]->w))/screen_ratio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+PunchStart],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        if(FrameCount%10==0)
        {
            Index++;
            if(Index==PunchCount)
            {
                etat=Stable;
            }
        }
        break;
    }
}

