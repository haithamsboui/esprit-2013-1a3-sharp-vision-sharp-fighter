#include "includes.h"

#define StableStartW 0
#define StablecountW 3

#define WalkStartW 9
#define WalkcountW 3

#define KickStartW 18
#define KickcountW 3

#define PunchStartW 14
#define PunchcountW 4

#define FireballStartW 30
#define FireballcountW 4

#define FreezeStartW 34
#define FreezecountW 3

#define ThunderStartW 37
#define ThundercountW 4

#define WindStartW 42
#define WindcountW 3

#define DefenceStartW 12
#define DefencecountW 2

#define CrouchStartW 6
#define CrouchcountW 2

#define JumpStartW 3
#define JumpcountW 3

#define FallStartW 21
#define FallcountW 5

#define HitStartW 45
#define HitcountW 2

#define UpStartM 27
#define UpCountM 3

IMAGE *WassimPics[WassimImageCount];

float xW,yW;
float wW,hW;
int directionW;
int PlayerW=0;
EtatPlayer etatW;
int IndexW;


void LoadWassim(int player)
{
    int i;
    char path[255];
    for (i=0; i<WassimImageCount; i++)
    {
        sprintf(path,"Resources/Images/Wassim/Gameplay/%d.png",i);
        WassimPics[i]=load_image(path);
    }

    PlayerW=player;
    etatW=Stable;
    IndexW=0;
    yW=55;
    wW=10;
    hW=40;


    switch(player)
    {
    case 1:
        directionW=0;
        xW=10;
        break;
    case 2:
        directionW=1;
        xW=90;
        break;
    }

}

int iW=1;
void Draw_Wassim()
{
    flip vflip;

    if(directionW)
        vflip=NONE;
    else
        vflip = VERTICAL;

    if(etatW!=Kick && etatW!=Punch && etatW!=Fireball && etatW != Freeze && etatW !=Jump  && etatW !=Wind && etatW !=Thunder &&etatW!=Fall&&etatW!=Hit&&etatW!=Defence&&etatW!=Down)
    {
        if(IsKeyPressed(PlayerW,KICK))
        {
            etatW=Kick;
            IndexW=0;
        }
        else if(IsKeyPressed(PlayerW,PUNCH))
        {
            etatW=Punch;
            IndexW=0;
        }
        else if(IsKeyPressed(PlayerW,RIGHT))
        {
            etatW=Forward;
            xW+=0.2;
        }
        else if (IsKeyPressed(PlayerW,LEFT))
        {
            etatW=Backward;
            xW-=0.2;
        }
        else if (IsKeyPressed(PlayerW,UP))
        {
            if (etatW!=Fall)
            {
                etatW=Jump;
                yW+=0.2;
            }
            else
                etatW=Stable;
        }
        else if (IsKeyPressed(PlayerW,DOWN))
        {
            etatW=Crouch;
            IndexW=0;
        }
        else if (IsKeyPressed(PlayerW,FIREBALL))
        {
            etatW=Fireball;
            IndexW=0;

        }
        else if (IsKeyPressed(PlayerW,FREEZE))
        {
            etatW=Freeze;
            IndexW=0;

        }
        else if (IsKeyPressed(PlayerW,THUNDER))
        {
            etatW=Thunder;
            IndexW=0;

        }
        else if (IsKeyPressed(PlayerW,WIND))
        {
            etatW=Wind;
            IndexW=0;

        }
        else if (IsKeyPressed(PlayerW,DEFENCE))
        {
            etatW=Defence;
            IndexW=0;

        }
        else
            etatW=Stable;
    }



    switch(etatW)
    {
    case Stable:
        if(FrameCount%10==0)
        {
            if(IndexW==0)
                iW=1;
            if(IndexW>=StablecountW-1)
                iW=-1;

            IndexW=IndexW+iW;
        }
        IndexW = Min(IndexW,StablecountW-1);
        wW=(hW/((float)WassimPics[IndexW+StableStartW]->h/(float)WassimPics[IndexW+StableStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+StableStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        break;
    case Forward:
        if(FrameCount%10==0)
        {
            IndexW=((IndexW-1+WalkcountW)%WalkcountW);
        }
        IndexW = Min(IndexW,WalkcountW-1);
        wW=(hW/((float)WassimPics[IndexW+WalkStartW]->h/(float)WassimPics[IndexW+WalkStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+WalkStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        break;

    case Backward:
        if(FrameCount%10==0)
        {
            IndexW=((IndexW+1)%WalkcountW);
        }
        IndexW = Min(IndexW,WalkcountW-1);
        wW=(hW/((float)WassimPics[IndexW+WalkStartW]->h/(float)WassimPics[IndexW+WalkStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+WalkStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        break;

    case Kick:
        wW=(hW/((float)WassimPics[IndexW+KickStartW]->h/(float)WassimPics[IndexW+KickStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+KickStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            if(IndexW==KickcountW)
            {
                etatW=Stable;
            }
        }

        break;

    case Punch:
        wW=(hW/((float)WassimPics[IndexW+PunchStartW]->h/(float)WassimPics[IndexW+PunchStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+PunchStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            if(IndexW==PunchcountW)
            {
                etatW=Stable;
            }
        }
        break;
    case Fireball:
        wW=(hW/((float)WassimPics[IndexW+FireballStartW]->h/(float)WassimPics[IndexW+FireballStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+FireballStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            if(IndexW==FireballcountW)
            {
                etatW=Stable;
            }
        }
        break;
    case Thunder:
        wW=(hW/((float)WassimPics[IndexW+ThunderStartW]->h/(float)WassimPics[IndexW+ThunderStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+ThunderStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            if(IndexW==ThundercountW)
            {
                etatW=Stable;
            }
        }
        break;

    case Wind:
        wW=(hW/((float)WassimPics[IndexW+WindStartW]->h/(float)WassimPics[IndexW+WindStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+WindStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            if(IndexW==WindcountW)
            {
                etatW=Stable;
            }
        }

        break;
    case Freeze:
        wW=(hW/((float)WassimPics[IndexW+FreezeStartW]->h/(float)WassimPics[IndexW+FreezeStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+FreezeStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            if(IndexW==FreezecountW)
            {
                etatW=Stable;
            }
        }

        break;

    case Crouch:
        wW=(hW/((float)WassimPics[IndexW+CrouchStartW]->h/(float)WassimPics[IndexW+CrouchStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+CrouchStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            if(IndexW==CrouchcountW)
            {
                etatW=Stable;
            }
        }
        break;


    case Defence:
        wW=(hW/((float)WassimPics[IndexW+DefenceStartW]->h/(float)WassimPics[IndexW+DefenceStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+DefenceStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            if(IndexW==DefencecountW)
            {
                etatW=Stable;
            }
        }
        break;

    case Fall:
        wW=(hW/((float)WassimPics[IndexW+HitStartW]->h/(float)WassimPics[IndexW+HitStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+HitStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            if(IndexW==HitcountW)
            {
                etatW=Stable;
            }
        }
        break;

    default:
        break;
    }
}


