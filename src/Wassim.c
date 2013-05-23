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

#define HitStartW 21
#define HitcountW 3

#define UpStartW 27
#define UpCountW 3

IMAGE *WassimPics[WassimImageCount];

float xW,yW;
float wW,hW;
int directionW;
int PlayerW=0;
EtatPlayer etatW;
int IndexW;
int FireW;
int ThunderW;
int WindW;
int FreezeW;

void LoadWassim(int player)
{
    char path[255];
    int i;
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
int CollisionStatW=0;
int SuperPowerW=0;

void Draw_Wassim()
{
    flip vflip;
    int jump_stat=1;
    Point ** TAB;
    IMAGE ** Vs;
    EtatPlayer etatVS;

    int x,y,w,h,IndexVs,VsSuperPower;
    if(directionW)
        vflip=NONE;
    else
        vflip = VERTICAL;

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
        etatVS=etatB;
VsSuperPower=SuperPowerB;
        x=xB;
        y=yB;
        w=wB;
        h=hB;
        TAB=BrahimCollision;
        Vs=BrahimPics;
        IndexVs=IndexCollissionB;

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

if (PlayerW==1)
{
    if (Combot1==10)
    {
        SuperPowerW=1;
              if (FrameCount%2==0)
draw_image_ex(Power1,0,0,100,0,NONE,100);
 if (FrameCount%3==0)
draw_image_ex(Power1,0,0,100,0,NONE,100);
    }
}
if (PlayerW==2){
     if (Combot2==10)
    {
        SuperPowerW=1;
              if (FrameCount%2==0)
draw_image_ex(Power2,0,0,100,0,NONE,100);
 if (FrameCount%3==0)
draw_image_ex(Power2,0,0,100,0,NONE,100);
    }
}
    switch (etatW)
    {

    case Stable :

        if(PlayerW==2)
            xW-=wW;
        if (PlayerW==1)
            x-=w;
        if(ProcessCollision(WassimPics,IndexCollissionW,WassimCollision,xW,yW,wW,hW,
                            Vs,IndexVs,TAB,x,y,w,h)&& (etatVS==Punch || etatVS==Kick))
        {
            etatW=Hit;
            IndexCollissionW=HitStartW;
            IndexW=0;
            if (PlayerW==2)
            {
                Player2Health-=2.5;

                 if (VsSuperPower==0 && Combot1<10)
               Combot1++;

            }
            if (PlayerW==1)
            {
                Player1Health-=2.5;

                                if (VsSuperPower==0 && Combot2<10)

                Combot2++;

            }

        }
        printf("Index COllision : %d\n",IndexCollissionW);
        if(ProcessCollision(WassimPics,IndexCollissionW,WassimCollision,xW,yW,wW,hW,
                            Vs,IndexVs,TAB,x,y,w,h)&& (etatVS==Fireball || etatVS==Freeze || etatVS==Thunder || etatVS==Wind))
        {
            etatW=Fall;
            IndexCollissionW=FallStartW;
            IndexW=0;
        }

        if(PlayerW==2)
            xW+=wW;
        if (PlayerW==1)
            x+=w;
        break;

    }

    if(etatW!=Kick && etatW!=Punch && etatW!=Fireball && etatW != Freeze && etatW !=Jump  && etatW !=Wind && etatW !=Thunder &&etatW!=Fall&&etatW!=Hit&&etatW!=Defence&&etatW!=Up)
    {
        if(PlayerW==2)
            xW-=wW;
        if (PlayerW==1)
            x-=w;
        while(ProcessCollision(WassimPics,IndexCollissionW,WassimCollision,xW,yW,wW,hW,
                               Vs,IndexVs,TAB,x,y,w,h))
        {
            if (PlayerW==2)
                xW+=0.1;
            else
                xW-=0.1;
        }
        if(PlayerW==2)
            xW+=wW;
        if (PlayerW==1)
            x+=w;

        if(IsKeyPressed(PlayerW,KICK))
        {
            etatW=Kick;
            IndexW=0;
            IndexCollissionW=KickStartW;
            CollisionStatW=1;

        }
        else if(IsKeyPressed(PlayerW,PUNCH))
        {
            etatW=Punch;
            IndexW=0;
            IndexCollissionW=PunchStartW;
            CollisionStatW=1;

        }
        else if(IsKeyPressed(PlayerW,RIGHT))
        {
            etatW=Forward;
            xW+=0.35;
            IndexCollissionW=WalkStartW;

        }
        else if (IsKeyPressed(PlayerW,LEFT))
        {
            etatW=Backward;
            xW-=0.35;
            IndexCollissionW=WalkStartW;
        }
        else if (IsKeyPressed(PlayerW,UP))
        {

            IndexW=0;
            iW=1;
            if (etatW==Stable)
            {
                etatW=Jump;
                IndexCollissionW=JumpStartW;
            }
            if (etatW==Fall)
            {
                etatW=Up;
                IndexCollissionW=FallStartW;
            }
        }
        else if (IsKeyPressed(PlayerW,DOWN))
        {
            etatW=Crouch;
            IndexW=0;
            IndexCollissionW=CrouchStartW;
        }
        else if (IsKeyPressed(PlayerW,FIREBALL)&& SuperPowerW==1)
        {
            etatW=Fireball;
            IndexW=0;
            IndexCollissionW=FireballStartW;
               SuperPowerW=0;
            if (PlayerW==1)
                Combot1=0;
            if (PlayerW==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerW,FREEZE)&& SuperPowerW==1)
        {
            etatW=Freeze;
            IndexW=0;
            IndexCollissionW=FreezeStartW;
        SuperPowerW=0;
            if (PlayerW==1)
                Combot1=0;
            if (PlayerW==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerW,THUNDER) && SuperPowerW==1)
        {
            etatW=Thunder;
            IndexW=0;
            IndexCollissionW=ThunderStartW;
        SuperPowerW=0;
            if (PlayerW==1)
                Combot1=0;
            if (PlayerW==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerW,WIND) && SuperPowerW==1)
        {
            etatW=Wind;
            IndexW=0;
            IndexCollissionW=WindStartW;
        SuperPowerW=0;
            if (PlayerW==1)
                Combot1=0;
            if (PlayerW==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerW,DEFENCE))
        {
            etatW=Defence;
            IndexW=0;
            IndexCollissionW=DefenceStartW;
        }
        else
        {
            etatW=Stable;
            IndexCollissionW=StablecountW;

        }
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
            IndexCollissionW+=IndexW;
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
            IndexCollissionW+=IndexW;
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
            IndexCollissionW+=IndexW;
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
            IndexCollissionW+=IndexW;
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
            IndexCollissionW+=IndexW;
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
            IndexCollissionW+=IndexW;
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
                                 if(IndexW<ThundercountW)
            {
                IndexW++;
                IndexCollissionW++;
            }
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
                                 if(IndexW<WindcountW)
            {
                IndexW++;
                IndexCollissionW++;
            }
            if(IndexW==WindcountW)
            {
                etatW=Stable;
                            IndexCollissionW=StableStartW;
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
            IndexCollissionW+=IndexW;
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
            IndexCollissionW+=IndexW;
            if(IndexW==CrouchcountW)
            {
                etatW=Stable;
            }
        }
        break;

    case Up:
        wW=(hW/((float)WassimPics[IndexW+UpStartW]->h/(float)WassimPics[IndexW+UpStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+UpStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            IndexCollissionW+=IndexW;
            if(IndexW==UpCountW)
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
            IndexCollissionW+=IndexW;
            if(IndexW==DefencecountW)
            {
                etatW=Stable;
            }
        }
        break;

    case Fall:
        wW=(hW/((float)WassimPics[IndexW+FallStartW]->h/(float)WassimPics[IndexW+FallStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+FallStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            IndexCollissionW+=IndexW;
            if(IndexW==FallcountW)
            {
                etatW=Stable;
            }
        }
        break;


    case Hit:
        wW=(hW/((float)WassimPics[IndexW+HitStartW]->h/(float)WassimPics[IndexW+HitStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+HitStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0)
        {
            IndexW++;
            IndexCollissionW+=IndexW;
            if(IndexW==HitcountW)
            {
                etatW=Stable;
            }
        }
        break;

    case Jump:
        if(FrameCount%10==0)
        {
            if(IndexW>=JumpcountW-1)
                etatW=Stable;
            if (IndexW>=1)
                jump_stat=0;
            if (jump_stat==1)
                yW-=20;
            if (jump_stat==0)
                yW+=10;
            IndexW++;
            IndexCollissionW+=IndexW;
        }

        wW=(hW/((float)WassimPics[IndexW+JumpStartW]->h/(float)WassimPics[IndexW+JumpStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+JumpStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        break;

    default:
        break;
    }
}



