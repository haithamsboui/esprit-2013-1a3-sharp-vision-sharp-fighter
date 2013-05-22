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
    set_config_file("Resources/Collision.cfg");
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
int CollisionStatS=0;
int SuperPowerS=0;
int iS=1;
void Draw_Salah()
{
    Point ** TAB;
    IMAGE ** Vs;
    int x,y,w,h,IndexVs,VsSuperPower;
    flip vflip;
    EtatPlayer etatVS;
    int jump_stat=1;
    if(directionS)
        vflip=VERTICAL;
    else
        vflip = NONE;


    if (player1==0 || player2==0)
    {
        VsSuperPower=SuperPowerM;
        x=xM;
        y=yM;
        w=wM;
        h=hM;
        TAB=MokhtarCollision;
        Vs=MokhtarPics;
        IndexVs=IndexCollissionM;
        etatVS=etatM;
    }
    if (player1==2 || player2==2)
    {
        VsSuperPower=SuperPowerB;
        x=xB;
        y=yB;
        w=wB;
        h=hB;
        TAB=BrahimCollision;
        Vs=BrahimPics;
        IndexVs=IndexCollissionB;
        etatVS=etatB;
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

    if (PlayerS==1)
    {
        if (Combot1==10)
        {
            SuperPowerS=1;
                  if (FrameCount%2==0)
draw_image_ex(Power1,0,0,100,0,NONE,100);
 if (FrameCount%3==0)
draw_image_ex(Power1,0,0,100,0,NONE,100);
        }
    }
    if (PlayerS==2)
    {
        if (Combot2==10)
        {
            SuperPowerS=1;
                  if (FrameCount%2==0)
draw_image_ex(Power2,0,0,100,0,NONE,100);
 if (FrameCount%3==0)
draw_image_ex(Power2,0,0,100,0,NONE,100);
        }
    }

    switch (etatS)
    {


    case Stable :
        if(PlayerS==2)
            xS-=wS;
        if (PlayerS==1)
            x-=w;
        if(ProcessCollision(SalahPics,IndexCollissionS,SalahCollision,xS,yS,wS,hS,
                            Vs,IndexVs,TAB,x,y,w,h)&& (etatVS==Punch || etatVS==Kick))
        {
            etatS=Hit;
            IndexS=0;
            IndexCollissionS=HitStartS;
            if (PlayerS==2)
            {
                Player2Health-=2.5;
                if (VsSuperPower==0 && Combot1<10)
                    Combot1++;

            }
            if (PlayerS==1)
            {
                Player1Health-=2.5;
                if (VsSuperPower==0 && Combot2<10)
                    Combot2++;

            }
        }
        if(ProcessCollision(SalahPics,IndexCollissionS,SalahCollision,xS,yS,wS,hS,
                            Vs,IndexVs,TAB,x,y,w,h)&& (etatVS==Fireball || etatVS==Freeze || etatVS==Thunder || etatVS==Wind))
        {
            etatS=Fall;
            IndexCollissionS=FallStartS;
            IndexS=0;

        }

        if(PlayerS==2)
            xS+=wS;
        if (PlayerS==1)
            x+=w;
        break;
    }

    if(etatS!=Kick && etatS!=Punch && etatS!=Fireball && etatS != Freeze && etatS !=Jump  && etatS !=Wind && etatS !=Thunder &&etatS!=Fall&&etatS!=Hit&&etatS!=Defence&&etatS!=Up)
    {
        if(PlayerS==2)
            xS-=wS;
        if (PlayerS==1)
            x-=w;
        while( ProcessCollision(SalahPics,IndexCollissionS,SalahCollision,xS,yS,wS,hS,
                                Vs, IndexVs, TAB, x,y,w,h))
        {
            if (PlayerS==2)
                xS+=0.1;
            else
                xS-=0.1;
        }
        if(PlayerS==2)
            xS+=wS;
        if (PlayerS==1)
            x+=w;

        if(IsKeyPressed(PlayerS,KICK))
        {
            etatS=Kick;
            IndexS=0;
            IndexCollissionS=KickStartS;
            CollisionStatS=1;

        }
        else if(IsKeyPressed(PlayerS,PUNCH))
        {
            etatS=Punch;
            IndexS=0;
            IndexCollissionS=PunchStartS;
                    CollisionStatS=1;

        }
        else if(IsKeyPressed(PlayerS,RIGHT))
        {
            etatS=Forward;
            xS+=0.35;
            IndexCollissionS=WalkStartS;
        }
        else if (IsKeyPressed(PlayerS,LEFT))
        {
            etatS=Backward;
            xS-=0.35;
            IndexCollissionS=WalkStartS;
        }
        else if (IsKeyPressed(PlayerS,UP))
        {
            IndexS=0;
            iS=1;
            if (etatS==Stable)
            {
                etatS=Jump;
                IndexCollissionS=JumpStartS;
            }
            if (etatS==Fall)
            {
                etatS=Up;
                IndexCollissionS=StableStartS;
            }
        }
        else if (IsKeyPressed(PlayerS,DOWN))
        {
            etatS=Crouch;
            IndexS=0;
            IndexCollissionS=CrouchStartS;
        }
        else if (IsKeyPressed(PlayerS,FIREBALL)&& SuperPowerS==1)
        {
            etatS=Fireball;
            IndexS=0;
            IndexCollissionS=FireballStartS;
            SuperPowerS=0;
            if (PlayerS==1)
                Combot1=0;
            if (PlayerS==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerS,FREEZE)&& SuperPowerS==1)
        {
            etatS=Freeze;
            IndexS=0;
            IndexCollissionS=FreezeStartS;
            SuperPowerS=0;
            if (PlayerS==1)
                Combot1=0;
            if (PlayerS==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerS,THUNDER)&& SuperPowerS==1)
        {
            etatS=Thunder;
            IndexS=0;
            IndexCollissionS=ThunderStartS;
            SuperPowerS=0;
            if (PlayerS==1)
                Combot1=0;
            if (PlayerS==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerS,WIND)&& SuperPowerS==1)
        {
            etatS=Wind;
            IndexS=0;
            IndexCollissionS=WindStartS;
            SuperPowerS=0;
            if (PlayerS==1)
                Combot1=0;
            if (PlayerS==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerS,DEFENCE))
        {
            etatS=Defence;
            IndexS=0;
            IndexCollissionS=DefenceStartS;
        }
        else
        {
            etatS=Stable;
            IndexCollissionS=StableStartS;
        }
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
            IndexCollissionS+=IndexS;
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
            IndexCollissionS+=IndexS;

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
            IndexCollissionS+=IndexS;

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
            IndexCollissionS+=IndexS;

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
            IndexCollissionS+=IndexS;

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
            IndexCollissionS+=IndexS;

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
                                   if(IndexS<ThunderCountS)
            {
                IndexS++;
                IndexCollissionS++;
            }

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
                                   if(IndexS<WindCountS)
            {
                IndexS++;
                IndexCollissionS++;
            }

            if(IndexS==WindCountS)
            {
                etatS=Stable;
                IndexCollissionS=StableStartS;
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
            IndexCollissionS+=IndexS;

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
            IndexCollissionS+=IndexS;

            if(IndexS==CrouchCountS)
            {
                etatS=Stable;
            }
        }
        break;

    case Up:
        wS=(hS/((float)SalahPics[IndexS+UpStartS]->h/(float)SalahPics[IndexS+UpStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+UpStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            IndexCollissionS+=IndexS;

            if(IndexS==UpCountS)
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
            IndexCollissionS+=IndexS;

            if(IndexS==DefenceCountS)
            {
                etatS=Stable;
            }
        }
        break;

    case Fall:
        wS=(hS/((float)SalahPics[IndexS+FallStartS]->h/(float)SalahPics[IndexS+FallStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+FallStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%10==0)
        {
            IndexS++;
            IndexCollissionS+=IndexS;

            if(IndexS==FallCountS)
            {
                etatS=Stable;
            }
        }
        break;

    case Hit:
        if(FrameCount%10==0)
        {
            IndexS++;
            IndexCollissionS+=IndexS;

            if(IndexS==HitCountS)
            {
                etatS=Stable;
            }
        }
        wS=(hS/((float)SalahPics[IndexS+HitStartS]->h/(float)SalahPics[IndexS+HitStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+HitStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;

        break;

    case Jump:
        if(FrameCount%10==0)
        {
            if(IndexS>=JumpCountS-2)
                etatS=Stable;
            if (IndexS>=2)
                jump_stat=0;
            if (jump_stat==1)
                yS-=10;
            if (jump_stat==0)
                yS+=20;
            IndexS++;
            IndexCollissionS+=IndexS;

        }
        wS=(hS/((float)SalahPics[IndexS+JumpStartS]->h/(float)SalahPics[IndexS+JumpStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+JumpStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        break;

    default:
        break;
    }
}


