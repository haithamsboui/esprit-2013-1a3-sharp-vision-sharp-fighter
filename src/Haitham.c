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

#define UpStartH 24
#define UpCountH 3

IMAGE *HaithamPics[HaithamImageCount];

float xH,yH;
float wH,hH;
int directionH;
int PlayerH=0;
EtatPlayer etatH;
int IndexH;


void LoadHaitham(int player)
{
    char path[255];

    int i;
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
int CollisionStatH=0;
int SuperPowerH=0;

void Draw_Haitham()
{
    flip vflip;
    Point ** TAB;
    IMAGE ** Vs;
    int x,y,w,h,IndexVs,xh,VsSuperPower;
    EtatPlayer EtatVS;
    int jump_stat=1;

    if(directionH)
        vflip=NONE;
    else
        vflip = VERTICAL;

    if (player1==0 || player2==0)
    {
        VsSuperPower=SuperPowerM;
        EtatVS=etatM;
        x=xM;
        y=yM;
        w=wM;
        h=hM;
        TAB=MokhtarCollision;
        Vs=MokhtarPics;
        IndexVs=IndexCollissionM;
    }

    if (player1==2 || player2==2)
    {
        VsSuperPower=SuperPowerB;
        EtatVS=etatB;
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
        EtatVS=etatS;
        x=xS;
        y=yS;
        w=wS;
        h=hS;
        TAB=SalahCollision;
        Vs=SalahPics;
        IndexVs=IndexCollissionS;
    }

    if (player1==4 || player2==4)
    {
                VsSuperPower=SuperPowerW;
        EtatVS=etatW;
        x=xW;
        y=yW;
        w=wW;
        h=hW;
        TAB=WassimCollision;
        Vs=WassimPics;
        IndexVs=IndexCollissionW;
    }

    if (PlayerH==1)
    {
        if (Combot1==10)
        {
            SuperPowerH=1;
        }
    }
    if (PlayerH==2)
    {
        if (Combot2==10)
        {
            SuperPowerH=1;
        }
    }

    switch (etatH)
    {
    case Stable :

        if(PlayerH==2)
            xH-=wH;
        if (PlayerH==1)
            x-=w;
        if(ProcessCollision(HaithamPics,IndexCollissionH,HaithamCollision,xH,yH,wH,hH,
                            Vs,IndexVs,TAB,x,y,w,h) && (EtatVS==Punch || EtatVS==Kick))
        {
            etatH=Hit;
            IndexH=0;
            IndexCollissionH=HitStartH;
            if (PlayerH==2)
            {
                Player2Health-=2.5;
                if (VsSuperPower==0 && Combot1<10)
                    Combot1++;
            }
            if (PlayerH==1)
            {
                Player1Health-=2.5;
                if (VsSuperPower==0 && Combot2<10)
                    Combot2++;
            }
        }

        if(ProcessCollision(HaithamPics,IndexCollissionH,HaithamCollision,xH,yH,wH,hH,
                            Vs,IndexVs,TAB,x,y,w,h) && (EtatVS==Fireball || EtatVS==Thunder || EtatVS == Wind || EtatVS == Freeze))
        {
            etatH=Fall;
            IndexH=0;
            IndexCollissionH=FallStartH;
        }

        if(PlayerH==2)
            xH+=wH;
        if (PlayerH==1)
            x+=w;

        break;
    }



    if(etatH!=Kick && etatH!=Punch && etatH!=Fireball && etatH != Freeze && etatH !=Jump  && etatH !=Wind && etatH !=Thunder &&etatH!=Fall&&etatH!=Hit&&etatH!=Defence&&etatH!=Up)
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

        if(IsKeyPressed(PlayerH,KICK))
        {
            etatH=Kick;
            IndexH=0;
            IndexCollissionH=KickStartH;
            CollisionStatH=1;

        }
        else if(IsKeyPressed(PlayerH,PUNCH))
        {
            etatH=Punch;
            IndexH=0;
            IndexCollissionH=PunchStartH;
            CollisionStatH=1;

        }
        else if(IsKeyPressed(PlayerH,RIGHT))
        {
            etatH=Forward;
            xH+=0.35;
            IndexCollissionH=WalkStartH;

        }
        else if (IsKeyPressed(PlayerH,LEFT))
        {
            etatH=Backward;
            xH-=0.35;
            IndexCollissionH=WalkStartH;
        }
        else if (IsKeyPressed(PlayerH,UP))
        {
            IndexH=0;
            iH=1;
            if (etatH==Stable)
            {
                etatH=Jump;
                IndexCollissionH=JumpStartH;
            }
            if (etatH==Fall)
            {
                etatH=Up;
                IndexCollissionH=StableStartH;
            }
        }
        else if (IsKeyPressed(PlayerH,DOWN))
        {
            etatH=Crouch;
            IndexH=0;
            IndexCollissionH=CrouchStartH;
        }
        else if (IsKeyPressed(PlayerH,FIREBALL)&& SuperPowerH==1)
        {
            etatH=Fireball;
            IndexH=0;
            IndexCollissionH=FireballStartH;
            SuperPowerH=0;
            if (PlayerH==1)
                Combot1=0;
            if (PlayerH==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerH,FREEZE)&& SuperPowerH==1)
        {
            etatH=Freeze;
            IndexH=0;
            IndexCollissionH=FreezeStartH;
            SuperPowerH=0;
            if (PlayerH==1)
                Combot1=0;
            if (PlayerH==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerH,THUNDER)&& SuperPowerH==1)
        {
            etatH=Thunder;
            IndexH=0;
            IndexCollissionH=ThunderStartH;
            SuperPowerH=0;
            if (PlayerH==1)
                Combot1=0;
            if (PlayerH==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerH,WIND) && SuperPowerH==1)
        {
            etatH=Wind;
            IndexH=0;
            IndexCollissionH=WindStartH;
            SuperPowerH=0;
            if (PlayerH==1)
                Combot1=0;
            if (PlayerH==2)
                Combot2=0;
        }
        else if (IsKeyPressed(PlayerH,DEFENCE))
        {
            etatH=Defence;
            IndexH=0;
            IndexCollissionH=DefenceStartH;

        }
        else
        {

            etatH=Stable;
            IndexCollissionH=StableStartH;
        }
    }



    switch(etatH)
    {
    case Stable:
    {
        if(FrameCount%10==0)
        {
            if(IndexH==0)
                iH=1;
            if(IndexH>=StableCountH-1)
                iH=-1;

            IndexH=IndexH+iH;
            IndexCollissionH+=IndexH;
        }
        IndexH = Min(IndexH,StableCountH-1);
        wH=(hH/((float)HaithamPics[IndexH+StableStartH]->h/(float)HaithamPics[IndexH+StableStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+StableStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
    }
    break;
    case Forward:
    {
        if(FrameCount%10==0)
        {
            IndexH=((IndexH-1+WalkCountH)%WalkCountH);
            IndexCollissionH+=IndexH;

        }
        IndexH = Min(IndexH,WalkCountH-1);
        wH=(hH/((float)HaithamPics[IndexH+WalkStartH]->h/(float)HaithamPics[IndexH+WalkStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+WalkStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
    }
    break;

    case Backward:
    {
        if(FrameCount%10==0)
        {
            IndexH=((IndexH+1)%WalkCountH);
            IndexCollissionH+=IndexH;

        }
        IndexH = Min(IndexH,WalkCountH);
        wH=(hH/((float)HaithamPics[IndexH+WalkStartH]->h/(float)HaithamPics[IndexH+WalkStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+WalkStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
    }
    break;

    case Kick:


    {
        wH=(hH/((float)HaithamPics[IndexH+KickStartH]->h/(float)HaithamPics[IndexH+KickStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+KickStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=KickCountH)
            {
                etatH=Stable;
            }

        }

    }
    break;

    case Punch:

    {
        wH=(hH/((float)HaithamPics[IndexH+PunchStartH]->h/(float)HaithamPics[IndexH+PunchStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+PunchStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=PunchCountH)
            {
                etatH=Stable;
            }
        }

    }
    break;
    case Fireball:
    {
        wH=(hH/((float)HaithamPics[IndexH+FireballStartH]->h/(float)HaithamPics[IndexH+FireballStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+FireballStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=FireballCountH)
            {
                etatH=Stable;
            }
        }
    }
    break;
    case Thunder:
    {
        wH=(hH/((float)HaithamPics[IndexH+ThunderStartH]->h/(float)HaithamPics[IndexH+ThunderStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+ThunderStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=ThunderCountH)
            {
                etatH=Stable;
            }
        }
    }
    break;

    case Wind:
    {
        wH=(hH/((float)HaithamPics[IndexH+WindStartH]->h/(float)HaithamPics[IndexH+WindStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+WindStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=WindCountH)
            {
                etatH=Stable;
            }
        }

    }
    break;
    case Freeze:
    {
        wH=(hH/((float)HaithamPics[IndexH+FreezeStartH]->h/(float)HaithamPics[IndexH+FreezeStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+FreezeStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=FreezeCountH)
            {
                etatH=Stable;
            }
        }

    }
    break;

    case Crouch:

    {
        wH=(hH/((float)HaithamPics[IndexH+CrouchStartH]->h/(float)HaithamPics[IndexH+CrouchStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+CrouchStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=CrouchCountH)
            {
                etatH=Stable;
            }
        }
    }
    break;

    case Up:

    {
        wH=(hH/((float)HaithamPics[IndexH+UpStartH]->h/(float)HaithamPics[IndexH+UpStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+UpStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=UpCountH)
            {
                etatH=Stable;
            }
        }
    }
    break;
    case Defence:
    {
        wH=(hH/((float)HaithamPics[IndexH+DefenceStartH]->h/(float)HaithamPics[IndexH+DefenceStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+DefenceStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=DefenceCountH)
            {
                etatH=Stable;
            }
        }
    }
    break;

    case Hit:
    {
        wH=(hH/((float)HaithamPics[IndexH+HitStartH]->h/(float)HaithamPics[IndexH+HitStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+HitStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=HitCountH)
            {
                etatH=Stable;
            }
        }
    }
    break;

    case Fall:
    {
        wH=(hH/((float)HaithamPics[IndexH+FallStartH]->h/(float)HaithamPics[IndexH+FallStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+FallStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0 && IndexH<=FallCountH)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

        }

    }
    break;

    case Jump:
    {
        if(FrameCount%10==0)
        {
            if(IndexH>=JumpCountH-1)
            {
                etatH=Stable;
            }

            if (IndexH>=2)
                jump_stat=0;

            if (jump_stat==1)
            {

                yH-=10;
            }
            if (jump_stat==0)
            {

                yH+=10;
            }

            IndexH++;
            IndexCollissionH+=IndexH;

        }

        wH=(hH/((float)HaithamPics[IndexH+JumpStartH]->h/(float)HaithamPics[IndexH+JumpStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+JumpStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;

    }
    break;
    default:
        break;
    }
}








