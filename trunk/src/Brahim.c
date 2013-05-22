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

#define UpStartB 49
#define UpCountB 3

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
int CollisionStatB=0;
int SuperPowerB=0;

void Draw_Brahim()
{
    Point ** TAB;
    IMAGE ** Vs;
    int x,y,w,h,IndexVs,xb,VsSuperPower;
    EtatPlayer etatVS;
    flip vflip;
    int jump_stat=1;
    if(directionB)
        vflip=NONE;
    else
        vflip = VERTICAL;

    if (player1==0 || player2==0)
    {
        VsSuperPower=SuperPowerM;
        etatVS=etatM;
        x=xM;
        y=yM;
        w=wM;
        h=hM;
        TAB=MokhtarCollision;
        Vs=MokhtarPics;
        IndexVs=IndexCollissionM;
    }

    if (player1==4 || player2==4)
    {
        VsSuperPower=SuperPowerW;
        etatVS=etatW;
        x=xW;
        y=yW;
        w=wW;
        h=hW;
        TAB=WassimCollision;
        Vs=WassimPics;
        IndexVs=IndexCollissionW;
    }

    if (player1==3 || player2==3)
    {
        VsSuperPower=SuperPowerS;
        etatVS=etatS;
        x=xS;
        y=yS;
        w=wS;
        h=hS;
        TAB=SalahCollision;
        Vs=SalahPics;
        IndexVs=IndexCollissionS;
    }

    if (player1==1 || player2==1)
    {
        VsSuperPower=SuperPowerH;
        etatVS=etatH;
        x=xH;
        y=yH;
        w=wH;
        h=hH;
        TAB=HaithamCollision;
        Vs=HaithamPics;
        IndexVs=IndexCollissionH;
    }

    if (PlayerB==1)
    {
        if (Combot1==10)
        {
            SuperPowerB=1;

            if (FrameCount%2==0)
                draw_image_ex(Power1,0,0,100,0,NONE,100);
            if (FrameCount%3==0)
                draw_image_ex(Power1,0,0,100,0,NONE,100);
        }
    }
    if (PlayerB==2)
    {
        if (Combot2==10)
        {
            SuperPowerB=1;
            if (FrameCount%2==0)
                draw_image_ex(Power2,0,0,100,0,NONE,100);
            if (FrameCount%3==0)
                draw_image_ex(Power2,0,0,100,0,NONE,100);

        }
    }


    switch (etatB)
    {

    case Stable :
        if(PlayerB==2)
            xB-=wB;
        if (PlayerB==1)
            x-=w;
        if(ProcessCollision(BrahimPics,IndexCollissionB,BrahimCollision,xB,yB,wB,hB,
                            Vs,IndexVs,TAB,x,y,w,h) && (etatVS==Punch || etatVS==Kick))
        {
            etatB=Hit;
            IndexB=0;
            IndexCollissionB=HitStartB;
            if (PlayerB==2)
            {
                Player2Health-=2.5;
                if (VsSuperPower==0 && Combot1<10)
                    Combot1++;

            }
            if (PlayerB==1)
            {
                Player1Health-=2.5;
                if (VsSuperPower==0 && Combot2<10)
                    Combot2++;
            }
        }


        if(ProcessCollision(BrahimPics,IndexCollissionB,BrahimCollision,xB,yB,wB,hB,
                            Vs,IndexVs,TAB,x,y,w,h) && (etatVS==Fireball || etatVS==Freeze || etatVS==Thunder ||etatVS==Wind))
        {
            etatB=Fall;
            IndexB=0;
            IndexCollissionB=FallStartB;
        }

        if(PlayerB==2)
            xB+=wB;
        if (PlayerB==1)
            x+=w;
        break;


    }
    if(etatB!=Kick && etatB!=Punch && etatB!=Fireball && etatB != Freeze && etatB !=Jump  && etatB !=Wind && etatB !=Thunder &&etatB!=Fall&&etatB!=Hit&&etatB!=Defence&&etatB!=Up)
    {
        if(PlayerB==2)
            xB-=wB;
        if (PlayerB==1)
            x-=w;
        while(ProcessCollision(BrahimPics,IndexCollissionB,BrahimCollision,xB,yB,wB,hB,
                               Vs,IndexVs,TAB,x,y,w,h))
        {
            if (PlayerB==2)
                xB+=0.1;
            else
                xB-=0.1;
        }
        if(PlayerB==2)
            xB+=wB;
        if (PlayerB==1)
            x+=w;
        if(IsKeyPressed(PlayerB,KICK))
        {
            etatB=Kick;
            IndexB=0;
            IndexCollissionB=KickStartB;
            CollisionStatB=1;
        }
        else if(IsKeyPressed(PlayerB,PUNCH))
        {
            etatB=Punch;
            IndexB=0;
            IndexCollissionB=PunchStartB;
            CollisionStatB=1;
        }
        else if(IsKeyPressed(PlayerB,RIGHT))
        {
            etatB=Forward;
            xB+=0.35;
            IndexCollissionB=WalkStartB;
        }
        else if (IsKeyPressed(PlayerB,LEFT))
        {
            etatB=Backward;
            xB-=0.35;
            IndexCollissionB=WalkStartB;
        }
        else if (IsKeyPressed(PlayerB,UP))
        {
            IndexB=0;
            iB=1;
            if (etatB==Stable)
            {
                etatB=Jump;
                IndexCollissionB=JumpStartB;
            }
            if (etatB==Fall)
            {
                etatB=Up;
                IndexCollissionB=FallStartB;
            }
        }
        else if (IsKeyPressed(PlayerB,DOWN))
        {
            etatB=Crouch;
            IndexB=0;
            IndexCollissionB=CrouchStartB;
        }
        else if (IsKeyPressed(PlayerB,FIREBALL)&& SuperPowerB==1)
        {
            etatB=Fireball;
            IndexB=0;
            IndexCollissionB=FireballStartB;
            SuperPowerB=0;
            if (PlayerB==1)
                Combot1=0;
            if (PlayerB==2)
                Combot2=0;

        }
        else if (IsKeyPressed(PlayerB,FREEZE)&& SuperPowerB==1)
        {
            etatB=Freeze;
            IndexB=0;
            IndexCollissionB=FreezeStartB;
            SuperPowerB=0;
            if (PlayerB==1)
                Combot1=0;
            if (PlayerB==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerB,THUNDER)&& SuperPowerB==1)
        {
            etatB=Thunder;
            IndexB=0;
            IndexCollissionB=ThunderStartB;
            SuperPowerB=0;
            if (PlayerB==1)
                Combot1=0;
            if (PlayerB==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerB,WIND)&& SuperPowerB==1)
        {
            etatB=Wind;
            IndexB=0;
            IndexCollissionB=WindStartB;
            SuperPowerB=0;
            if (PlayerB==1)
                Combot1=0;
            if (PlayerB==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerB,DEFENCE))
        {
            etatB=Defence;
            IndexB=0;
            IndexCollissionB=DefenceStartB;
        }
        else
        {
            etatB=Stable;
            IndexCollissionB=StableStartB;
        }
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
            IndexCollissionB+=IndexB;
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
            IndexCollissionB+=IndexB;

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
            IndexCollissionB+=IndexB;

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
            IndexCollissionB+=IndexB;

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
            IndexCollissionB+=IndexB;

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
            IndexCollissionB+=IndexB;

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
            if(IndexB<ThunderCountB)
            {

                IndexB++;
                IndexCollissionB++;

            }


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
            if(IndexB<WindCountB)
            {

                IndexB++;
                IndexCollissionB++;

            }

            if(IndexB==WindCountB)
            {
                etatB=Stable;
            }
        }

        break;
    case Freeze:
        wB=(hB/((float)BrahimPics[IndexB+FreezeStartB]->h/(float)BrahimPics[IndexB+FreezeStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+FreezeStartB],xB,yB,wB,0,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            if(IndexB<WindCountB)
            {
                IndexB++;
                IndexCollissionB++;
            }
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
            IndexCollissionB+=IndexB;

            if(IndexB==CrouchCountB)
            {
                etatB=Stable;
            }
        }
        break;

    case Up:
        wB=(hB/((float)BrahimPics[IndexB+UpStartB]->h/(float)BrahimPics[IndexB+UpStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+UpStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            IndexCollissionB+=IndexB;

            if(IndexB==UpCountB)
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
            IndexCollissionB+=IndexB;

            if(IndexB==DefenceCountB)
            {
                etatB=Stable;
            }
        }
        break;

    case Fall:
        wB=(hB/((float)BrahimPics[IndexB+FallStartB]->h/(float)BrahimPics[IndexB+FallStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+FallStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if(FrameCount%10==0)
        {
            IndexB++;
            IndexCollissionB+=IndexB;

            if(IndexB==FallCountB)
            {
                etatB=Stable;
            }
        }
        break;

    case Hit:
        if(FrameCount%10==0)
        {
            IndexCollissionB+=IndexB;
            IndexB++;

            if(IndexB>=HitCountB-1)
            {
                etatB=Stable;
                IndexCollissionB=StableStartB;
            }
        }
        printf ("%d\n",IndexB+HitStartB);
        wB=(hB/((float)BrahimPics[IndexB+HitStartB]->h/(float)BrahimPics[IndexB+HitStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+HitStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;

        break;
    case Jump:
        if(FrameCount%10==0)
        {
            if(IndexB>=JumpCountB-1)
            {
                etatB=Stable;
            }
            if (IndexB>=2)
                jump_stat=0;

            if (jump_stat==1)
            {
                yB-=10;
            }
            if (jump_stat==0)
            {
                yB+=6.667;
            }
            IndexB++;
            IndexCollissionB+=IndexB;
        }
        wB=(hB/((float)BrahimPics[IndexB+JumpStartB]->h/(float)BrahimPics[IndexB+JumpStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+JumpStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        break;

    default:
        break;
    }
}




