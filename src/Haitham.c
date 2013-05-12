#include "includes.h"

#define StableStartH 0
#define StableCountH 4

#define WalkStartH 4
#define WalkCountH 4

#define KickStartH 8
#define KickCountH 4

#define PunchStartH 12
#define PunchCountH 4

#define FireballStartH 33
#define FireballCountH 4

#define FreezeStartH 37
#define FreezeCountH 3

#define ThunderStartH 40
#define ThunderCountH 7

#define WindStartH 47
#define WindCountH 3

#define DefenceStartH 18
#define DefenceCountH 2

#define CrouchStartH 16
#define CrouchCountH 2

#define JumpStartH 29
#define JumpCountH 4

#define FallStartH 20
#define FallCountH 4

#define HitStartH 27
#define HitCountH 2

IMAGE *HaithamPics[HaithamImageCount];

float xH,yH;
float wH,hH;
int directionH;
int PlayerH=0;
EtatPlayer etatH;
int IndexH;


void LoadHaitham(int player)
{
    int i;
    char path[255];
    for (i=0; i<HaithamImageCount; i++)
    {
        sprintf(path,"Resources/Images/Haitham/GamePlay/%d.png",i);
        HaithamPics[i]=load_image(path);
    }

    PlayerH=player;
    etatH=Stable;
    IndexH=0;
    yH=55;
    wH=10;
    hH=40;


    switch(player)
    {
    case 1:
        directionH=0;
        xH=10;
        break;
    case 2:
        directionH=1;
        xH=90;
        break;
    }

}

int iH=1;
void Draw_Haitham()
{
    flip vflip;

    if(directionH)
        vflip=NONE;
    else
        vflip = VERTICAL;

    if(etatH!=Kick && etatH!=Punch && etatH!=Fireball && etatH != Freeze & etatH !=Jump  && etatH !=Wind && etatH !=Thunder &&etatH!=Fall&&etatH!=Hit&&etatH!=Defence&etatH!=Down)
    {
        if(IsKeyPressed(PlayerH,KICK))
        {
            etatH=Kick;
            IndexH=0;
        }
        else if(IsKeyPressed(PlayerH,PUNCH))
        {
            etatH=Punch;
            IndexH=0;
        }
        else if(IsKeyPressed(PlayerH,RIGHT))
        {
            etatH=Forward;
            xH+=0.2;
        }
        else if (IsKeyPressed(PlayerH,LEFT))
        {
            etatH=Backward;
            xH-=0.2;
        }
        else if (IsKeyPressed(PlayerH,UP))
        {
            if (etatH!=Fall)
         {
             etatH=Jump;
            yH+=0.2;
        }
        else
        etatH=Stable;
        }
        else if (IsKeyPressed(PlayerH,DOWN))
        {
            etatH=Crouch;
            IndexH=0;
        }
        else if (IsKeyPressed(PlayerH,FIREBALL))
        {
            etatH=Fireball;
            IndexH=0;

        }
        else if (IsKeyPressed(PlayerH,FREEZE))
        {
            etatH=Freeze;
            IndexH=0;

        }
        else if (IsKeyPressed(PlayerH,THUNDER))
        {
            etatH=Thunder;
            IndexH=0;

        }
        else if (IsKeyPressed(PlayerH,WIND))
        {
            etatH=Wind;
            IndexH=0;

        }
        else
            etatH=Stable;
    }



    switch(etatH)
    {
    case Stable:
        if(FrameCount%10==0)
        {
            if(IndexH==0)
                iH=1;
            if(IndexH>=StableCountH-1)
                iH=-1;

            IndexH=IndexH+iH;
        }
        IndexH = Min(IndexH,StableCountH-1);
        wH=(hH/((float)HaithamPics[IndexH+StableStartH]->h/(float)HaithamPics[IndexH+StableStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+StableStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        break;
    case Forward:
        if(FrameCount%10==0)
        {
            IndexH=((IndexH-1+WalkCountH)%WalkCountH);
        }
        IndexH = Min(IndexH,WalkCountH-1);
        wH=(hH/((float)HaithamPics[IndexH+WalkStartH]->h/(float)HaithamPics[IndexH+WalkStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+WalkStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        break;

    case Backward:
        if(FrameCount%10==0)
        {
            IndexH=((IndexH+1)%WalkCountH);
        }
        IndexH = Min(IndexH,WalkCountH-1);
        wH=(hH/((float)HaithamPics[IndexH+WalkStartH]->h/(float)HaithamPics[IndexH+WalkStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+WalkStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        break;

    case Kick:
        wH=(hH/((float)HaithamPics[IndexH+KickStartH]->h/(float)HaithamPics[IndexH+KickStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+KickStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==KickCountH)
            {
                etatH=Stable;
            }
        }

        break;

    case Punch:
        wH=(hH/((float)HaithamPics[IndexH+PunchStartH]->h/(float)HaithamPics[IndexH+PunchStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+PunchStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==PunchCountH)
            {
                etatH=Stable;
            }
        }
        break;
    case Fireball:
        wH=(hH/((float)HaithamPics[IndexH+FireballStartH]->h/(float)HaithamPics[IndexH+FireballStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+FireballStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==FireballCountH)
            {
                etatH=Stable;
            }
        }
    break;
    case Thunder:
        wH=(hH/((float)HaithamPics[IndexH+ThunderStartH]->h/(float)HaithamPics[IndexH+ThunderStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+ThunderStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==ThunderCountH)
            {
                etatH=Stable;
            }
        }
        break;

    case Wind:
    wH=(hH/((float)HaithamPics[IndexH+WindStartH]->h/(float)HaithamPics[IndexH+WindStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+WindStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==WindCountH)
            {
                etatH=Stable;
            }
        }

    break;
    case Freeze:
    wH=(hH/((float)HaithamPics[IndexH+FreezeStartH]->h/(float)HaithamPics[IndexH+FreezeStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+FreezeStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==FreezeCountH)
            {
                etatH=Stable;
            }
        }

    break;

        case Crouch:
    wH=(hH/((float)HaithamPics[IndexH+CrouchStartH]->h/(float)HaithamPics[IndexH+CrouchStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+CrouchStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==CrouchCountH)
            {
                etatH=Stable;
            }
        }
break;


  case Defence:
    wH=(hH/((float)HaithamPics[IndexH+DefenceStartH]->h/(float)HaithamPics[IndexH+DefenceStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+DefenceStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==DefenceCountH)
            {
                etatH=Stable;
            }
        }
break;

  case Fall:
    wH=(hH/((float)HaithamPics[IndexH+HitStartH]->h/(float)HaithamPics[IndexH+HitStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+HitStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==HitCountH)
            {
                etatH=Stable;
            }
        }
break;
    }
}


