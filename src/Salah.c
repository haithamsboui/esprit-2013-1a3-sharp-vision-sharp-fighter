#include "includes.h"

#define StableStartS 0
#define StableCountS 3

#define JumpStartS 3
#define JumpCountS 4

#define CrouchStartS 7
#define CrouchCountS 2

#define WalkStartS 9
#define WalkCountS 3

#define PunchStartS 14
#define PunchCountS 5

#define KickStartS 19
#define KickCountS 4

#define FireballStartS 33
#define FireballCountS 5

#define FreezeStartS 38
#define FreezeCountS 4

#define ThunderStartS 42
#define ThunderCountS 5

#define WindStartS 47
#define WindCountS 4

#define DefenceStartS 12
#define DefenceCountS 2

#define FallStartS 26
#define FallCountS 4

#define HitStartS 23
#define HitCountS 2

#define UpStartS 30
#define UpCountS 3

IMAGE *SalahPics[SalahImageCount];

float xS,yS;
float wS,hS;
int directionS;
int PlayerS=0;
EtatPlayer etatS;
int IndexS;


void LoadSalah(int player)
{
    int i;
    char path[255];
    for (i=0; i<SalahImageCount; i++)
    {
        sprintf(path,"Resources/Images/Salah/GamePlay/%d.png",i);
        SalahPics[i]=load_image(path);
    }

    PlayerS=player;
    etatS=Stable;
    IndexS=0;
    yS=55;
    wS=10;
    hS=40;


    switch(player)
    {
    case 1:
        directionS=0;
        xS=10;
        break;
    case 2:
        directionS=1;
        xS=90;
        break;
    }

}

int iS=1;
void Draw_Salah()
{
    flip vflip;

    if(directionS)
        vflip=VERTICAL;
    else
        vflip = NONE;

    if(etatS!=Kick && etatS!=Punch && etatS!=Fireball && etatS != Freeze && etatS !=Jump  && etatS !=Wind && etatS !=Thunder &&etatS!=Fall&&etatS!=Hit&&etatS!=Defence&&etatS!=Down)
    {
        if(IsKeyPressed(PlayerS,KICK))
        {
            etatS=Kick;
            IndexS=0;
        }
        else if(IsKeyPressed(PlayerS,PUNCH))
        {
            etatS=Punch;
            IndexS=0;
        }
        else if(IsKeyPressed(PlayerS,RIGHT))
        {
            etatS=Forward;
            xS+=0.2;
        }
        else if (IsKeyPressed(PlayerS,LEFT))
        {
            etatS=Backward;
            xS-=0.2;
        }
        else if (IsKeyPressed(PlayerS,UP))
        {
            if (etatS!=Fall)
            {
                etatS=Jump;
                yS+=0.2;
            }
            else
                etatS=Stable;
        }
        else if (IsKeyPressed(PlayerS,DOWN))
        {
            etatS=Crouch;
            IndexS=0;
        }
        else if (IsKeyPressed(PlayerS,FIREBALL))
        {
            etatS=Fireball;
            IndexS=0;

        }
        else if (IsKeyPressed(PlayerS,FREEZE))
        {
            etatS=Freeze;
            IndexS=0;

        }
        else if (IsKeyPressed(PlayerS,THUNDER))
        {
            etatS=Thunder;
            IndexS=0;

        }
        else if (IsKeyPressed(PlayerS,WIND))
        {
            etatS=Wind;
            IndexS=0;

        }
        else if (IsKeyPressed(PlayerS,DEFENCE))
        {
            etatS=Defence;
            IndexS=0;

        }
        else
            etatS=Stable;
    }



    switch(etatS)
    {
    case Stable:
        if(FrameCount%10==0)
        {
            if(IndexS==0)
                iS=1;
            if(IndexS>=StableCountS-1)
                iS=-1;

            IndexS=IndexS+iS;
        }
        IndexS = Min(IndexS,StableCountS-1);
        wS=(hS/((float)SalahPics[IndexS+StableStartS]->h/(float)SalahPics[IndexS+StableStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+StableStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        break;
    case Forward:
        if(FrameCount%10==0)
        {
            IndexS=((IndexS-1+WalkCountS)%WalkCountS);
        }
        IndexS = Min(IndexS,WalkCountS-1);
        wS=(hS/((float)SalahPics[IndexS+WalkStartS]->h/(float)SalahPics[IndexS+WalkStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+WalkStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        break;

    case Backward:
        if(FrameCount%10==0)
        {
            IndexS=((IndexS+1)%WalkCountS);
        }
        IndexS = Min(IndexS,WalkCountS-1);
        wS=(hS/((float)SalahPics[IndexS+WalkStartS]->h/(float)SalahPics[IndexS+WalkStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+WalkStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        break;

    case Kick:
        wS=(hS/((float)SalahPics[IndexS+KickStartS]->h/(float)SalahPics[IndexS+KickStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+KickStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            if(IndexS==KickCountS)
            {
                etatS=Stable;
            }
        }

        break;

    case Punch:
        wS=(hS/((float)SalahPics[IndexS+PunchStartS]->h/(float)SalahPics[IndexS+PunchStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+PunchStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            if(IndexS==PunchCountS)
            {
                etatS=Stable;
            }
        }
        break;
    case Fireball:
        wS=(hS/((float)SalahPics[IndexS+FireballStartS]->h/(float)SalahPics[IndexS+FireballStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+FireballStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            if(IndexS==FireballCountS)
            {
                etatS=Stable;
            }
        }
        break;
    case Thunder:
        wS=(hS/((float)SalahPics[IndexS+ThunderStartS]->h/(float)SalahPics[IndexS+ThunderStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+ThunderStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            if(IndexS==ThunderCountS)
            {
                etatS=Stable;
            }
        }
        break;

    case Wind:
        wS=(hS/((float)SalahPics[IndexS+WindStartS]->h/(float)SalahPics[IndexS+WindStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+WindStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            if(IndexS==WindCountS)
            {
                etatS=Stable;
            }
        }

        break;
    case Freeze:
        wS=(hS/((float)SalahPics[IndexS+FreezeStartS]->h/(float)SalahPics[IndexS+FreezeStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+FreezeStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            if(IndexS==FreezeCountS)
            {
                etatS=Stable;
            }
        }

        break;

    case Crouch:
        wS=(hS/((float)SalahPics[IndexS+CrouchStartS]->h/(float)SalahPics[IndexS+CrouchStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+CrouchStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            if(IndexS==CrouchCountS)
            {
                etatS=Stable;
            }
        }
        break;


    case Defence:
        wS=(hS/((float)SalahPics[IndexS+DefenceStartS]->h/(float)SalahPics[IndexS+DefenceStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+DefenceStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            if(IndexS==DefenceCountS)
            {
                etatS=Stable;
            }
        }
        break;

    case Fall:
        wS=(hS/((float)SalahPics[IndexS+HitStartS]->h/(float)SalahPics[IndexS+HitStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+HitStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            if(IndexS==HitCountS)
            {
                etatS=Stable;
            }
        }
        break;
    default:
        break;
    }
}


