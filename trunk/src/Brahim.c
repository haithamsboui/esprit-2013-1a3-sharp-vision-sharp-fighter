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
#define FallCountB 6

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
    yB=45;
    wB=20;
    hB=50;


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
int effB=0;

void Draw_Brahim()
{
    Point ** TAB;
    IMAGE ** Vs;
    int x,y,w,h,IndexVs,VsSuperPower;
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
    case Forward :
    case Backward :
    case Crouch :
        if(PlayerB==2)
            xB-=wB;
        if (PlayerB==1)
            x-=w;
        if(ProcessCollision(BrahimPics,IndexCollissionB,BrahimCollision,xB,yB,wB,hB,
                            Vs,IndexVs,TAB,x,y,w,h) && (etatVS==Punch || etatVS==Kick))
        {

if (etatVS==Punch)
    ComboPunch=1;
if (etatVS==Kick)
    Combokick=1;
            etatB=Hit;
            IndexB=0;
            IndexCollissionB=HitStartB;
            if (PlayerB==2)
            {
                Player2Health-=2.5;
                if (VsSuperPower==0 && Combot1<10)
                    Combot1++;
                if (Player2Health<5)
                {
                    etatB=Fall;
                    IndexB=0;
                    IndexCollissionB=FallStartB;
                }
            }
            if (PlayerB==1)
            {
                Player1Health-=2.5;
                if (VsSuperPower==0 && Combot2<10)
                    Combot2++;
                if (Player1Health<5)
                {
                    etatB=Fall;
                    IndexB=0;
                    IndexCollissionB=FallStartB;

                }
            }
        }

        if(PlayerB==2)
            xB+=wB;
        if (PlayerB==1)
            x+=w;
        break;

    }

    if(etatB!=Kick && etatB!=Punch && etatB!=Fireball && etatB != Freeze && etatB !=Jump  && etatB !=Wind && etatB !=Thunder &&etatB!=Hit&&etatB!=Defence&&etatB!=Up &&etatB!=Crouch && etatB!=Fall)
    {
        while (xB>99.0)
            xB--;
        while (xB<1.0)
            xB++;
        if(PlayerB==2)
            xB-=wB;
        if (PlayerB==1)
            x-=w;
        while(ProcessCollision(BrahimPics,IndexCollissionB,BrahimCollision,xB,yB,wB,hB,
                               Vs,IndexVs,TAB,x,y,w,h))
        {
            if (PlayerB==2 )
                xB+=0.05;
            if (PlayerB==1 )

                xB-=0.05;
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
        else if(IsKeyPressed(PlayerB,RIGHT) && xB<99.0)
        {
            etatB=Forward;
            xB+=0.50;
            IndexCollissionB=WalkStartB;
        }
        else if (IsKeyPressed(PlayerB,LEFT)&& xB>1.0)
        {
            etatB=Backward;
            xB-=0.50;
            IndexCollissionB=WalkStartB;
        }
        else if (IsKeyPressed(PlayerB,UP))
        {
            IndexB=0;
            iB=1;
            etatB=Jump;
            IndexCollissionB=JumpStartB;


        }
        else if (IsKeyPressed(PlayerB,DOWN))
        {
            etatB=Crouch;
            IndexB=0;
            IndexCollissionB=CrouchStartB;
        }
        else if (IsKeyPressed(PlayerB,FIREBALL)&& SuperPowerB==1 && FireB==1)
        {
            effB=0;
            etatB=Fireball;
            IndexB=0;
            IndexCollissionB=FireballStartB;
            SuperPowerB=0;
            if (PlayerB==1)
            {
                Combot1=0;
            }
            if (PlayerB==2)
            {
                Combot2=0;
            }
        }
        else if (IsKeyPressed(PlayerB,FREEZE)&& SuperPowerB==1&& FreezeB==1)
        {
            effB=0;
            etatB=Freeze;
            IndexB=0;
            IndexCollissionB=FreezeStartB;
            SuperPowerB=0;
            if (PlayerB==1)
            {
                Combot1=0;
            }
            if (PlayerB==2)
            {
                Combot2=0;
            }
        }
        else if (IsKeyPressed(PlayerB,THUNDER)&& SuperPowerB==1&& ThunderB==1)
        {
            effB=0;
            etatB=Thunder;
            IndexB=0;
            IndexCollissionB=ThunderStartB;
            SuperPowerB=0;
            if (PlayerB==1)
            {
                Combot1=0;
            }
            if (PlayerB==2)
            {
                Combot2=0;
            }
        }
        else if (IsKeyPressed(PlayerB,WIND)&& SuperPowerB==1&& WindB==1)
        {
            etatB=Wind;
            IndexB=0;
            effB=0;
            IndexCollissionB=WindStartB;
            SuperPowerB=0;
            if (PlayerB==1)
            {
                Combot1=0;
            }
            if (PlayerB==2)
            {
                Combot2=0;
            }
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

    if (OnAttack==1)
    {
        etatB=Fall;
        OnAttack=0;
        IndexB=0;
        IndexCollissionB=FallStartB;
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
        if(FrameCount%7==0)
        {
            IndexB++;
            IndexCollissionB+=IndexB;

            if(IndexB==KickCountB)
            {
                etatB=Stable;
                IndexB=0;
                IndexCollissionB=StableStartB;
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
                IndexB=0;
                IndexCollissionB=StableStartB;

            }
        }
        break;
    case Fireball:
        wB=(hB/((float)BrahimPics[IndexB+FireballStartB]->h/(float)BrahimPics[IndexB+FireballStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+FireballStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;
        if (effB<50 && IndexB>=FireballCountB-1)
        {
            if (PlayerB==1)
            {
                draw_image_ex(FireEffet[effB],xB+10+((x-xB-20)/50)*effB,55,5+effB/5,0,NONE,100);
            }
            if (PlayerB==2)
            {
                draw_image_ex(FireEffet[effB],xB-15-((xB-x-12)/50)*effB,55,5+effB/5,0,NONE,100);
            }
            effB++;
        }
        if(FrameCount%10==0)
        {
            if(IndexB<FireballCountB-1)
            {
                IndexB++;
                IndexCollissionB+=IndexB;
            }
            if(IndexB>=FireballCountB-1 && effB>=50)
            {
                OnAttack=1;
                etatB=Stable;
                IndexB=0;
                IndexCollissionB=StableStartB;
                if (PlayerB==1)
                {
                    Player2Health-=20;
                }
                if (PlayerB==2)
                {
                    Player1Health-=20;

                }
            }
        }
        break;
    case Thunder:

        wB=(hB/((float)BrahimPics[IndexB+ThunderStartB]->h/(float)BrahimPics[IndexB+ThunderStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+ThunderStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;

        if (effB<50 &&IndexB>=ThunderCountB-1)
        {
            if (PlayerB==1)
            {
                draw_image_ex(ThunderEffet[effB],xB-25+((x-xB-20)/50)*effB,-7+effB/3,70+effB/4,100,NONE,100);
            }
            if (PlayerB==2)
            {
                draw_image_ex(ThunderEffet[effB],xB-30+((x-xB)/50)*effB,-7+effB/3,70+effB/4,100,NONE,100);
            }
            effB++;

        }


        if(FrameCount%10==0)
        {
            if(IndexB<ThunderCountB-1)
            {
                IndexB++;
                IndexCollissionB++;
            }

            if(IndexB==ThunderCountB-1 && effB>=50)
            {
                OnAttack=1;

                etatB=Stable;
                IndexB=0;
                IndexCollissionB=StableStartB;
                if (PlayerB==1)
                {
                    Player2Health-=20;
                }
                if (PlayerB==2)
                {
                    Player1Health-=20;

                }
            }
        }
        break;

    case Wind:
        wB=(hB/((float)BrahimPics[IndexB+WindStartB]->h/(float)BrahimPics[IndexB+WindStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+WindStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;

        if (effB<50 &&IndexB>=WindCountB-1)
        {
            if (PlayerB==1)
            {
                draw_image_ex(WindEffet[effB],xB+10+((x-xB-20)/50)*effB,50-effB/3,20+effB,30+effB,NONE,100);
            }
            if (PlayerB==2)
            {
                draw_image_ex(WindEffet[effB],xB-15+((x-xB)/50)*effB,50-effB/3,20+effB,30+effB,NONE,100);
            }

            effB++;

        }


        if(FrameCount%10==0)
        {
            if(IndexB<WindCountB-1)
            {
                IndexB++;
                IndexCollissionB++;
            }

            if(IndexB>=WindCountB-1 && effB>=50)
            {
                OnAttack=1;

                etatB=Stable;
                IndexB=0;
                IndexCollissionB=StableStartB;
                if (PlayerB==1)
                {
                    Player2Health-=20;
                }
                if (PlayerB==2)
                {
                    Player1Health-=20;

                }
            }
        }

        break;
    case Freeze:
        wB=(hB/((float)BrahimPics[IndexB+FreezeStartB]->h/(float)BrahimPics[IndexB+FreezeStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+FreezeStartB],xB,yB,wB,0,vflip,100);
        if(PlayerB==2) xB+=wB;
        if ( IndexB>=FreezeCountB-1)
        {
            if (PlayerB==1)
            {
                draw_image_ex(FreezeEffet[1],x-15,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-15,35,20,0,NONE,100);
            }
            if (PlayerB==2)
            {
                draw_image_ex(FreezeEffet[1],x-5,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-5,35,20,0,NONE,100);
            }
        }
        if(FrameCount%10==0)
        {
            if(IndexB<FreezeCountB-1)
            {
                IndexB++;
                IndexCollissionB++;
            }
            if(IndexB>=FreezeCountB-1 && FrameCount%120==0)
            {
                OnAttack=1;

                etatB=Stable;
                IndexB=0;
                IndexCollissionB=StableStartB;
                if (PlayerB==1)
                {
                    Player2Health-=20;
                }
                if (PlayerB==2)
                {
                    Player1Health-=20;

                }
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
                IndexB=0;
                IndexCollissionB=StableStartB;
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
            IndexCollissionB++;

            if(IndexB>=UpCountB-1)
            {
                etatB=Stable;
                IndexB=0;
                IndexCollissionB=StableStartB;
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
                IndexB=0;
                IndexCollissionB=StableStartB;
            }
        }
        break;

    case Fall:
        wB=(hB/((float)BrahimPics[IndexB+FallStartB]->h/(float)BrahimPics[IndexB+FallStartB]->w))/AspectRatio;
        if(PlayerB==2) xB-=wB;
        draw_image_ex(BrahimPics[IndexB+FallStartB],xB,yB,wB,hB,vflip,100);
        if(PlayerB==2) xB+=wB;

        if(FrameCount%15==0  )
        {
            IndexB++;
            IndexCollissionB++;

          if (IndexB>=FallCountB)
            {

                if (PlayerB==1 && Player1Health<5)
                    Player1Health=0;
                if (PlayerB==2 && Player2Health<5)
                    Player2Health=0;
                if (PlayerB==1 && Player1Health>5)
                {
                    etatB=Up;
                    IndexB=0;
                    IndexCollissionB=UpStartB;
                }
                if (PlayerB==2 && Player2Health>5)
                {
                    etatB=Up;
                    IndexB=0;
                    IndexCollissionB=UpStartB;
                }
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
                IndexB=0;
            }
        }
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
                IndexB=0;
                IndexCollissionB=StableStartB;
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
            IndexB++ ;
            IndexCollissionB++;
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




