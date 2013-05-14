#include "includes.h"

#define StableStartM 0
#define StableCountM 4

#define JumpStartM 4
#define JumpCountM 6

#define CrouchMtartM 9
#define CrouchCountM 1

#define WalkStartM 63
#define WalkCountM 3

#define PunchMtartM 12
#define PunchCountM 3

#define KickStartM 15
#define KickCountM 7

#define FireballStartM 40
#define FireballCountM 9

#define FreezeStartM 49
#define FreezeCountM 5

#define ThunderStartM 59
#define ThunderCountM 4

#define WindStartM 54
#define WindCountM 5

#define DefenceStartM 22
#define DefenceCountM 2

#define FallStartM 25
#define FallCountM 6

#define HitStartM 32
#define HitCountM 4

#define UpStartM 36
#define UpCountM 4

IMAGE *MokhtarPics[MokhtarImageCount];

float xM,yM;
float wM,hM;
int directionM;
int PlayerM=0;
EtatPlayer etatM;
int IndexM;


void LoadMokhtar(int player)
{
    int i;
    char path[255];
    for (i=0; i<MokhtarImageCount; i++)
    {
        sprintf(path,"Resources/Images/Mokhtar/Gamplay/%d.png",i);
        MokhtarPics[i]=load_image(path);
    }

    PlayerM=player;
    etatM=Stable;
    IndexM=0;
    yM=55;
    wM=10;
    hM=40;


    switch(player)
    {
    case 1:
        directionM=0;
        xM=10;
        break;
    case 2:
        directionM=1;
        xM=90;
        break;
    }

}

int iM=1;
void Draw_Mokhtar()
{
    flip vflip;

    if(directionM)
        vflip=NONE;
    else
        vflip = VERTICAL;

    if(etatM!=Kick && etatM!=Punch && etatM!=Fireball && etatM != Freeze && etatM !=Jump  && etatM !=Wind && etatM !=Thunder &&etatM!=Fall&&etatM!=Hit&&etatM!=Defence&&etatM!=Down)
    {
        if(IsKeyPressed(PlayerM,KICK))
        {
            etatM=Kick;
            IndexM=0;
        }
        else if(IsKeyPressed(PlayerM,PUNCH))
        {
            etatM=Punch;
            IndexM=0;
        }
        else if(IsKeyPressed(PlayerM,RIGHT))
        {
            etatM=Forward;
            xM+=0.2;
        }
        else if (IsKeyPressed(PlayerM,LEFT))
        {
            etatM=Backward;
            xM-=0.2;
        }
        else if (IsKeyPressed(PlayerM,UP))
        {
            if (etatM!=Fall)
            {
                etatM=Jump;
                yM+=0.2;
            }
            else
                etatM=Stable;
        }
        else if (IsKeyPressed(PlayerM,DOWN))
        {
            etatM=Crouch;
            IndexM=0;
        }
        else if (IsKeyPressed(PlayerM,FIREBALL))
        {
            etatM=Fireball;
            IndexM=0;

        }
        else if (IsKeyPressed(PlayerM,FREEZE))
        {
            etatM=Freeze;
            IndexM=0;

        }
        else if (IsKeyPressed(PlayerM,THUNDER))
        {
            etatM=Thunder;
            IndexM=0;

        }
        else if (IsKeyPressed(PlayerM,WIND))
        {
            etatM=Wind;
            IndexM=0;

        }
        else if (IsKeyPressed(PlayerM,DEFENCE))
        {
            etatM=Defence;
            IndexM=0;

        }
        else
            etatM=Stable;
    }



    switch(etatM)
    {
    case Stable:
        if(FrameCount%10==0)
        {
            if(IndexM==0)
                iM=1;
            if(IndexM>=StableCountM-1)
                iM=-1;

            IndexM=IndexM+iM;
        }
        IndexM = Min(IndexM,StableCountM-1);
        wM=(hM/((float)MokhtarPics[IndexM+StableStartM]->h/(float)MokhtarPics[IndexM+StableStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+StableStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        break;
    case Forward:
        if(FrameCount%10==0)
        {
            IndexM=((IndexM-1+WalkCountM)%WalkCountM);
        }
        IndexM = Min(IndexM,WalkCountM-1);
        wM=(hM/((float)MokhtarPics[IndexM+WalkStartM]->h/(float)MokhtarPics[IndexM+WalkStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+WalkStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        break;

    case Backward:
        if(FrameCount%10==0)
        {
            IndexM=((IndexM+1)%WalkCountM);
        }
        IndexM = Min(IndexM,WalkCountM-1);
        wM=(hM/((float)MokhtarPics[IndexM+WalkStartM]->h/(float)MokhtarPics[IndexM+WalkStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+WalkStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        break;

    case Kick:
        wM=(hM/((float)MokhtarPics[IndexM+KickStartM]->h/(float)MokhtarPics[IndexM+KickStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+KickStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            if(IndexM==KickCountM)
            {
                etatM=Stable;
            }
        }

        break;

    case Punch:
        wM=(hM/((float)MokhtarPics[IndexM+PunchMtartM]->h/(float)MokhtarPics[IndexM+PunchMtartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+PunchMtartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            if(IndexM==PunchCountM)
            {
                etatM=Stable;
            }
        }
        break;
    case Fireball:
        wM=(hM/((float)MokhtarPics[IndexM+FireballStartM]->h/(float)MokhtarPics[IndexM+FireballStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+FireballStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            if(IndexM==FireballCountM)
            {
                etatM=Stable;
            }
        }
        break;
    case Thunder:
        wM=(hM/((float)MokhtarPics[IndexM+ThunderStartM]->h/(float)MokhtarPics[IndexM+ThunderStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+ThunderStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            if(IndexM==ThunderCountM)
            {
                etatM=Stable;
            }
        }
        break;

    case Wind:
        wM=(hM/((float)MokhtarPics[IndexM+WindStartM]->h/(float)MokhtarPics[IndexM+WindStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+WindStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            if(IndexM==WindCountM)
            {
                etatM=Stable;
            }
        }

        break;
    case Freeze:
        wM=(hM/((float)MokhtarPics[IndexM+FreezeStartM]->h/(float)MokhtarPics[IndexM+FreezeStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+FreezeStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            if(IndexM==FreezeCountM)
            {
                etatM=Stable;
            }
        }

        break;

    case Crouch:
        wM=(hM/((float)MokhtarPics[IndexM+CrouchMtartM]->h/(float)MokhtarPics[IndexM+CrouchMtartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+CrouchMtartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            if(IndexM==CrouchCountM)
            {
                etatM=Stable;
            }
        }
        break;


    case Defence:
        wM=(hM/((float)MokhtarPics[IndexM+DefenceStartM]->h/(float)MokhtarPics[IndexM+DefenceStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+DefenceStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            if(IndexM==DefenceCountM)
            {
                etatM=Stable;
            }
        }
        break;

    case Fall:
        wM=(hM/((float)MokhtarPics[IndexM+HitStartM]->h/(float)MokhtarPics[IndexM+HitStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+HitStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            if(IndexM==HitCountM)
            {
                etatM=Stable;
            }
        }
        break;
    default:
        break;
    }
}


