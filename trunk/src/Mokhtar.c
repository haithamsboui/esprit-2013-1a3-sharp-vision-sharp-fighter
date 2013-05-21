#include "includes.h"

#define StableStartM 0
#define StableCountM 4

#define JumpStartM 4
#define JumpCountM 6

#define CrouchStartM 9
#define CrouchCountM 1

#define WalkStartM 63
#define WalkCountM 3

#define PunchStartM 12
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
int CollisionStatM=0;
int SuperPowerM=0;

void Draw_Mokhtar()
{
    Point ** TAB;
    IMAGE ** Vs;
    int x,y,w,h,IndexVs,VsSuperPower;
    flip vflip;
    EtatPlayer etatVS;
    int jump_stat=1;
    if(directionM)
        vflip=NONE;
    else
        vflip = VERTICAL;


    if (player1==4 || player2==4)
    {
        VsSuperPower=SuperPowerW;
        x=xW;
        y=yW;
        w=wW;
        h=hW;
        TAB=WassimCollision;
        Vs=WassimPics;
        IndexVs=IndexCollissionW;
        etatVS=etatW;
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
    if (player1==3 || player2==3)
    {
        VsSuperPower=SuperPowerS;
        x=xS;
        y=yS;
        w=wS;
        h=hS;
        TAB=SalahCollision;
        Vs=SalahPics;
        IndexVs=IndexCollissionS;
        etatVS=etatS;
    }
    if (player1==1 || player2==1)
    {
        VsSuperPower=SuperPowerH;
        x=xH;
        y=yH;
        w=wH;
        h=hH;
        TAB=HaithamCollision;
        Vs=HaithamPics;
        IndexVs=IndexCollissionH;
        etatVS=etatH;
    }

    if (PlayerM==1)
    {
        if (Combot1==10)
        {
            SuperPowerM=1;
        }
    }
    if (PlayerM==2)
    {
        if (Combot2==10)
        {
            SuperPowerM=1;
        }
    }

    switch (etatM)
    {

    case Stable :
        if(PlayerM==2)
            xM-=wM;
        if (PlayerM==1)
            x-=w;
        if(ProcessCollision(MokhtarPics,IndexCollissionM,MokhtarCollision,xM,yM,wM,hM,
                            Vs,IndexVs,TAB,x,y,w,h)&& (etatVS==Punch || etatVS==Kick))
        {

            etatM=Hit;
            IndexM=0;
            IndexCollissionM=HitStartM;
            if (PlayerM==2)
            {
                Player2Health-=2.5;
                if (VsSuperPower==0 && Combot1<10)

                    Combot1++;

            }
            if (PlayerM==1)
            {
                Player1Health-=2.5;
                if (VsSuperPower==0 && Combot2<10)

                    Combot2++;

            }

        }
        if(ProcessCollision(MokhtarPics,IndexCollissionM,MokhtarCollision,xM,yM,wM,hM,
                            Vs,IndexVs,TAB,x,y,w,h)&& (etatVS==Fireball || etatVS==Freeze ||etatM==Thunder || etatM==Wind))
        {

            etatM=Fall;
            IndexM=0;
            IndexCollissionM=FallStartM;
        }
        if(PlayerM==2)
            xM+=wM;
        if (PlayerM==1)
            x+=w;
        break;

    }

    if(etatM!=Kick && etatM!=Punch && etatM!=Fireball && etatM != Freeze && etatM !=Jump  && etatM !=Wind && etatM !=Thunder &&etatM!=Fall&&etatM!=Hit&&etatM!=Defence&&etatM!=Up)
    {
        if(PlayerM==2)
            xM-=wM;
        if (PlayerM==1)
            x-=w;
        while(ProcessCollision(MokhtarPics,IndexCollissionM,MokhtarCollision,xM,yM,wM,hM,
                               Vs,IndexVs,TAB,x,y,w,h))
        {
            if (PlayerM==2)
                xM+=0.1;
            else
                xM-=0.1;
        }
        if(PlayerM==2)
            xM+=wM;
        if (PlayerM==1)
            x+=w;

        if(IsKeyPressed(PlayerM,KICK))
        {
            etatM=Kick;
            IndexM=0;
            IndexCollissionM=KickStartM;
            CollisionStatM==1;
        }
        else if(IsKeyPressed(PlayerM,PUNCH))
        {
            etatM=Punch;
            IndexM=0;
            IndexCollissionM=PunchStartM;
            CollisionStatM==1;
        }
        else if(IsKeyPressed(PlayerM,RIGHT))
        {
            etatM=Forward;
            xM+=0.35;
            IndexCollissionM=WalkStartM;
        }
        else if (IsKeyPressed(PlayerM,LEFT))
        {
            etatM=Backward;
            xM-=0.35;
            IndexCollissionM=WalkStartM;
        }
        else if (IsKeyPressed(PlayerM,UP))
        {
            IndexM=0;
            iM=1;
            if (etatM==Stable)
            {
                etatM=Jump;
                IndexCollissionM=JumpStartM;
            }
            if (etatM==Fall)
            {
                etatM=Up;
                IndexCollissionM=FallStartM;
            }
        }
        else if (IsKeyPressed(PlayerM,DOWN))
        {
            etatM=Crouch;
            IndexM=0;
            IndexCollissionM=CrouchStartM;
        }
        else if (IsKeyPressed(PlayerM,FIREBALL)&& SuperPowerM==1)
        {
            etatM=Fireball;
            IndexM=0;
            IndexCollissionM=FireballStartM;
            SuperPowerM=0;
            if (PlayerM==1)
                Combot1=0;
            if (PlayerM==2)
                Combot2=0;

        }
        else if (IsKeyPressed(PlayerM,FREEZE)&& SuperPowerM==1)
        {
            etatM=Freeze;
            IndexM=0;
            IndexCollissionM=FreezeStartM;
            SuperPowerM=0;
            if (PlayerM==1)
                Combot1=0;
            if (PlayerM==2)
                Combot2=0;

        }
        else if (IsKeyPressed(PlayerM,THUNDER)&& SuperPowerM==1)
        {
            etatM=Thunder;
            IndexM=0;
            IndexCollissionM=ThunderStartM;
            SuperPowerM=0;
            if (PlayerM==1)
                Combot1=0;
            if (PlayerM==2)
                Combot2=0;

        }
        else if (IsKeyPressed(PlayerM,WIND)&& SuperPowerM==1)
        {
            etatM=Wind;
            IndexM=0;
            IndexCollissionM=WindStartM;
            SuperPowerM=0;
            if (PlayerM==1)
                Combot1=0;
            if (PlayerM==2)
                Combot2=0;

        }
        else if (IsKeyPressed(PlayerM,DEFENCE))
        {
            etatM=Defence;
            IndexM=0;
            IndexCollissionM=DefenceStartM;
        }
        else
        {
            etatM=Stable;
            IndexCollissionM=StableStartM;
        }
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
            IndexCollissionM+=IndexM;
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
            IndexCollissionM+=IndexM;

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
            IndexCollissionM+=IndexM;

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
            IndexCollissionM+=IndexM;

            if(IndexM==KickCountM)
            {
                etatM=Stable;
            }
        }

        break;

    case Punch:
        wM=(hM/((float)MokhtarPics[IndexM+PunchStartM]->h/(float)MokhtarPics[IndexM+PunchStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+PunchStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            IndexCollissionM+=IndexM;

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
            IndexCollissionM+=IndexM;

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
            IndexCollissionM+=IndexM;

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
            IndexCollissionM+=IndexM;

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
            IndexCollissionM+=IndexM;

            if(IndexM==FreezeCountM)
            {
                etatM=Stable;
            }
        }

        break;

    case Crouch:
        wM=(hM/((float)MokhtarPics[IndexM+CrouchStartM]->h/(float)MokhtarPics[IndexM+CrouchStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+CrouchStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            IndexCollissionM+=IndexM;

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
            IndexCollissionM+=IndexM;

            if(IndexM==DefenceCountM)
            {
                etatM=Stable;
            }
        }
        break;

    case Hit:
        wM=(hM/((float)MokhtarPics[IndexM+HitStartM]->h/(float)MokhtarPics[IndexM+HitStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+HitStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            IndexCollissionM+=IndexM;

            if(IndexM==HitCountM)
            {
                etatM=Stable;
            }
        }
        break;

    case Fall:
        wM=(hM/((float)MokhtarPics[IndexM+FallStartM]->h/(float)MokhtarPics[IndexM+FallStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+FallStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            IndexCollissionM+=IndexM;

            if(IndexM==FallCountM)
            {
                etatM=Stable;
            }
        }
        break;

    case Up:
        wM=(hM/((float)MokhtarPics[IndexM+UpStartM]->h/(float)MokhtarPics[IndexM+UpStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+UpStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%10==0)
        {
            IndexM++;
            IndexCollissionM+=IndexM;

            if(IndexM==UpCountM)
            {
                etatM=Stable;
            }
        }
        break;

    case Jump:
        if(FrameCount%10==0)
        {
            if(IndexM>=JumpCountM-1)
            {
                etatM=Stable;
            }

            if (IndexM>=3)
                jump_stat=0;

            if (jump_stat==1)
            {

                yM-=6.5;
            }
            if (jump_stat==0)
            {

                yM+=6.5;
            }

            IndexM++;
            IndexCollissionM+=IndexM;

        }
        wM=(hM/((float)MokhtarPics[IndexM+JumpStartM]->h/(float)MokhtarPics[IndexM+JumpStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexH+JumpStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;

        break;


    default:
        break;
    }
}


