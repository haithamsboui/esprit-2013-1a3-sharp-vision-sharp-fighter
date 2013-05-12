#include "includes.h"

#define StableStartB 0
#define StableCountB 4

#define WalkStartB 4
#define WalkCountB 4

#define KickStartB 8
#define KickCountB 5

#define PunchStartB 13
#define PunchCountB 3

#define FireballStartB 16
#define FireballCountB 5

#define FreezeStartB 21
#define FreezeCountB 4

#define ThunderStartB 25
#define ThunderCountB 4

#define WindStartB 29
#define WindCountB 4

#define DefenceStartB 33
#define DefenceCountB 3

#define CrouchStartB 36
#define CrouchCountB 2

#define JumpStartB 38
#define JumpCountB 5

#define FallStartB 43
#define FallCountB 9

#define HitStartB 52
#define HitCountB 4

IMAGE *BrahimPics[BrahimImageCount];

float xB,yB;
float wB,hB;
int directionB;
int PlayerB=0;
EtatPlayer etatB;
int IndexB;


void LoadBrahim(int player)
{
    int i;
    char path[255];
    for (i=0; i<BrahimImageCount; i++)
    {
        sprintf(path,"Resources/Images/Brahim/Gameplay/%d.png",i);
        BrahimPics[i]=load_image(path);
    }

    PlayerB=player;
    etatB=Stable;
    IndexB=0;
    yB=55;
    wB=10;
    hB=40;


    switch(player)
    {
    case 1:
        directionB=0;
        xB=10;
        break;
    case 2:
        directionB=1;
        xB=90;
        break;
    }

}

int iB=1;

void Draw_Brahim()
{
    flip vflip;

    if(directionB)
        vflip=NONE;
    else
        vflip = VERTICAL;
    printf("111");
    printf("**%d",IndexB);
    if(etatB!=Kick && etatB!=Punch && etatB!=Fireball && etatB != Freeze && etatB !=Jump  && etatB !=Wind && etatB !=Thunder &&etatB!=Fall&&etatB!=Hit&&etatB!=Defence&&etatB!=Down)
    {
        if(IsKeyPressed(PlayerB,KICK))
        {
            etatB=Kick;
            IndexB=0;
        }
        else if(IsKeyPressed(PlayerB,PUNCH))
        {
            etatB=Punch;
            IndexB=0;
        }
        else if(IsKeyPressed(PlayerB,RIGHT))
        {
            etatB=Forward;
            xB+=0.2;
        }
        else if (IsKeyPressed(PlayerB,LEFT))
        {
            etatB=Backward;
            xB-=0.2;
        }
        else if (IsKeyPressed(PlayerB,UP))
        {
            if (etatB!=Fall)
            {
                etatB=Jump;
                yB+=0.2;
            }
            else
                etatB=Stable;
        }
        else if (IsKeyPressed(PlayerB,DOWN))
        {
            etatB=Crouch;
            IndexB=0;
        }
        else if (IsKeyPressed(PlayerB,FIREBALL))
        {
            etatB=Fireball;
            IndexB=0;

        }
        else if (IsKeyPressed(PlayerB,FREEZE))
        {
            etatB=Freeze;
            IndexB=0;

        }
        else if (IsKeyPressed(PlayerB,THUNDER))
        {
            etatB=Thunder;
            IndexB=0;

        }
        else if (IsKeyPressed(PlayerB,WIND))
        {
            etatB=Wind;
            IndexB=0;

        }
        else
            etatB=Stable;
    }


    switch(etatB)
    {
    case Stable:
        if(FrameCount%10==0)
        {
            if(IndexB==0)
                iB=1;
            if(IndexB>=StableCountB-1)
                iB=-1;

            IndexB=IndexB+iB;
        }

        IndexB = Min(IndexB,StableCountB-1);
        wB=(hB/((float)BrahimPics[IndexB]->h/(float)BrahimPics[IndexB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        break;
    case Forward:
        if(FrameCount%10==0)
        {
            IndexB=((IndexB-1+WalkCountB)%WalkCountB);
        }
        IndexB = Min(IndexB,WalkCountB-1);
        wB=(hB/((float)BrahimPics[IndexB+WalkStartB]->h/(float)BrahimPics[IndexB+WalkStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+WalkStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        break;

    case Backward:
        if(FrameCount%10==0)
        {
            IndexB=((IndexB+1)%WalkCountB);
        }
        IndexB = Min(IndexB,WalkCountB-1);
        wB=(hB/((float)BrahimPics[IndexB+WalkStartB]->h/(float)BrahimPics[IndexB+WalkStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+WalkStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        break;

    case Kick:
        wB=(hB/((float)BrahimPics[IndexB+KickStartB]->h/(float)BrahimPics[IndexB+KickStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+KickStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            if(IndexB==KickCountB)
            {
                etatB=Stable;
            }
        }

        break;

    case Punch:
        wB=(hB/((float)BrahimPics[IndexB+PunchStartB]->h/(float)BrahimPics[IndexB+PunchStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+PunchStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            if(IndexB==PunchCountB)
            {
                etatB=Stable;
            }
        }
        break;
    case Fireball:
        wB=(hB/((float)BrahimPics[IndexB+FireballStartB]->h/(float)BrahimPics[IndexB+FireballStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+FireballStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            if(IndexB==FireballCountB)
            {
                etatB=Stable;
            }
        }
        break;
    case Thunder:
        wB=(hB/((float)BrahimPics[IndexB+ThunderStartB]->h/(float)BrahimPics[IndexB+ThunderStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+ThunderStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            if(IndexB==ThunderCountB)
            {
                etatB=Stable;
            }
        }
        break;

    case Wind:
        wB=(hB/((float)BrahimPics[IndexB+WindStartB]->h/(float)BrahimPics[IndexB+WindStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+WindStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            if(IndexB==WindCountB)
            {
                etatB=Stable;
            }
        }

        break;
    case Freeze:
        wB=(hB/((float)BrahimPics[IndexB+FreezeStartB]->h/(float)BrahimPics[IndexB+FreezeStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+FreezeStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            if(IndexB==FreezeCountB)
            {
                etatB=Stable;
            }
        }

        break;

    case Crouch:
        wB=(hB/((float)BrahimPics[IndexB+CrouchStartB]->h/(float)BrahimPics[IndexB+CrouchStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+CrouchStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            if(IndexB==CrouchCountB)
            {
                etatB=Stable;
            }
        }
        break;


    case Defence:
        wB=(hB/((float)BrahimPics[IndexB+DefenceStartB]->h/(float)BrahimPics[IndexB+DefenceStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+DefenceStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            if(IndexB==DefenceCountB)
            {
                etatB=Stable;
            }
        }
        break;

    case Fall:
        wB=(hB/((float)BrahimPics[IndexB+HitStartB]->h/(float)BrahimPics[IndexB+HitStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+HitStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            if(IndexB==HitCountB)
            {
                etatB=Stable;
            }
        }
        break;
    default:
        break;
    }
}


