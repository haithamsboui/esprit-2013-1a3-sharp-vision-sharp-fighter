#include "includes.h"

#define StableStartS 0
#define StableCountS 3

#define WalkStartS 9
#define WalkCountS 4

#define KickStartS 19
#define KickCountS 4

#define PunchStartS 14
#define PunchCountS 5

IMAGE *SalahPics[51];

float x,y;
float w,h;
int direction;
int Player=0;
EtatPlayer etat;
int Index;

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
            if(Index>=StableCountS-1)
                i=-1;

            Index=Index+i;
        }
        Index = Min(Index,StableCountS-1);
        w=(h/((float)SalahPics[Index+StableStartS]->h/(float)SalahPics[Index+StableStartS]->w))/AspectRatio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+StableStartS],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        break;
    case Forward:
        if(FrameCount%10==0)
        {
            Index=((Index-1+WalkCountS)%WalkCountS);
        }
        Index = Min(Index,WalkCountS-1);
        w=(h/((float)SalahPics[Index+WalkStartS]->h/(float)SalahPics[Index+WalkStartS]->w))/AspectRatio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+WalkStartS],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        break;

    case Backward:
        if(FrameCount%10==0)
        {
            Index=((Index+1)%WalkCountS);
        }
        Index = Min(Index,WalkCountS-1);
        w=(h/((float)SalahPics[Index+WalkStartS]->h/(float)SalahPics[Index+WalkStartS]->w))/AspectRatio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+WalkStartS],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        break;

    case Kick:
        w=(h/((float)SalahPics[Index+KickStartS]->h/(float)SalahPics[Index+KickStartS]->w))/AspectRatio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+KickStartS],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        if(FrameCount%10==0)
        {
            Index++;
            if(Index==KickCountS)
            {
                etat=Stable;
            }
        }

        break;

    case Punch:
        w=(h/((float)SalahPics[Index+PunchStartS]->h/(float)SalahPics[Index+PunchStartS]->w))/AspectRatio;
        if(Player==2) x-=w;
        draw_image_ex(SalahPics[Index+PunchStartS],x,y,w,h,vflip,100);
        if(Player==2) x+=w;
        if(FrameCount%10==0)
        {
            Index++;
            if(Index==PunchCountS)
            {
                etat=Stable;
            }
        }
        break;
    }
}

