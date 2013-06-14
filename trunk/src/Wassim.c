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
    yW=45;
    wW=20;
    hW=50;

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
int effW=0;
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
    if (PlayerW==2)
    {
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
    case Forward :
    case Backward :
    case Crouch :

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
                if (Player2Health<5)
              {
                     etatW=Fall;
IndexW=0;
IndexCollissionW=FallStartW;
              }
            }
            if (PlayerW==1)
            {
                Player1Health-=2.5;

                if (VsSuperPower==0 && Combot2<10)
                    Combot2++;
                if (Player1Health<5)
{
                    etatW=Fall;
 IndexW=0;
IndexCollissionW=FallStartW;
}
            }

        }
        if(PlayerW==2)
            xW+=wW;
        if (PlayerW==1)
            x+=w;
        break;

    }
    if (OnAttack==1)
    {
        etatW=Fall;
        OnAttack=0;
        IndexW=0;
        IndexCollissionW=FallStartW;
    }
    if(etatW!=Kick && etatW!=Punch && etatW!=Fireball && etatW != Freeze && etatW !=Jump  && etatW !=Wind && etatW !=Thunder &&etatW!=Fall&&etatW!=Hit&&etatW!=Defence&&etatW!=Up && etatW!=Crouch)
    {
        while (xW>99.0)
            xW--;
        while (xW<1.0)
            xW++;
        if(PlayerW==2)
            xW-=wW;
        if (PlayerW==1)
            x-=w;
        while(ProcessCollision(WassimPics,IndexCollissionW,WassimCollision,xW,yW,wW,hW,
                               Vs,IndexVs,TAB,x,y,w,h) )
        {
            if (PlayerW==2)
                xW+=0.05;
            else
                xW-=0.05;
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
        else if(IsKeyPressed(PlayerW,RIGHT) && xW<99.0)
        {
            etatW=Forward;
            xW+=0.50;
            IndexCollissionW=WalkStartW;

        }
        else if (IsKeyPressed(PlayerW,LEFT)&& xW>1.0)
        {
            etatW=Backward;
            xW-=0.50;
            IndexCollissionW=WalkStartW;
        }
        else if (IsKeyPressed(PlayerW,UP))
        {

            IndexW=0;
            iW=1;

            etatW=Jump;
            IndexCollissionW=JumpStartW;

        }
        else if (IsKeyPressed(PlayerW,DOWN))
        {
            etatW=Crouch;
            IndexW=0;
            IndexCollissionW=CrouchStartW;
        }
        else if (IsKeyPressed(PlayerW,FIREBALL)&& SuperPowerW==1 && FireW==1)
        {
            effW=0;
            etatW=Fireball;
            IndexW=0;
            IndexCollissionW=FireballStartW;
            SuperPowerW=0;
            if (PlayerW==1)
            {
                Combot1=0;
            }
            if (PlayerW==2)
            {
                Combot2=0;
            }
        }
        else if (IsKeyPressed(PlayerW,FREEZE)&& SuperPowerW==1&& FreezeW==1)
        {
            effW=0;
            etatW=Freeze;
            IndexW=0;
            IndexCollissionW=FreezeStartW;
            SuperPowerW=0;
            if (PlayerW==1)
            {
                Combot1=0;
            }
            if (PlayerW==2)
            {
                Combot2=0;
            }
        }
        else if (IsKeyPressed(PlayerW,THUNDER) && SuperPowerW==1&&ThunderW==1)
        {
            effW=0;
            etatW=Thunder;
            IndexW=0;
            IndexCollissionW=ThunderStartW;
            SuperPowerW=0;
            if (PlayerW==1)
            {
                Combot1=0;
            }
            if (PlayerW==2)
            {
                Combot2=0;
            }
        }
        else if (IsKeyPressed(PlayerW,WIND) && SuperPowerW==1&& WindW==1)
        {
            effW=0;
            etatW=Wind;
            IndexW=0;
            IndexCollissionW=WindStartW;
            SuperPowerW=0;
            if (PlayerW==1)
            {
                Combot1=0;
            }
            if (PlayerW==2)
            {
                Combot2=0;
            }
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
        if(FrameCount%9==0)
        {
            IndexW++;
            IndexCollissionW+=IndexW;
            if(IndexW==KickcountW)
            {
                etatW=Stable;
         IndexW=0;
         IndexCollissionW=StableStartW;
            }
        }

        break;

    case Punch:
        wW=(hW/((float)WassimPics[IndexW+PunchStartW]->h/(float)WassimPics[IndexW+PunchStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+PunchStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%8==0)
        {
            IndexW++;
            IndexCollissionW+=IndexW;
            if(IndexW==PunchcountW)
            {
                etatW=Stable;
         IndexW=0;
         IndexCollissionW=StableStartW;
            }
        }
        break;
    case Fireball:
        wW=(hW/((float)WassimPics[IndexW+FireballStartW]->h/(float)WassimPics[IndexW+FireballStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+FireballStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if (effW<50 && IndexW>=FireballcountW-1)
        {
            if (PlayerW==1)
            {
                draw_image_ex(FireEffet[effW],xW+10+((x-xW-20)/50)*effW,55,5+effW/5,0,NONE,100);
            }
            if (PlayerW==2)
            {
                draw_image_ex(FireEffet[effW],xW-15-((xW-x-12)/50)*effW,55,5+effW/5,0,NONE,100);
            }
            effW++;

        }

        if(FrameCount%10==0)
        {
            if(IndexW<FireballcountW-1)
            {
                IndexW++;
                IndexCollissionW++;
            }
            if(IndexW>=FireballcountW-1 && effW>=50)
            {
                OnAttack=1;

                etatW=Stable;
                         IndexW=0;
         IndexCollissionW=StableStartW;
                if (PlayerW==1)
                {
                    Player2Health-=20;
                }
                if (PlayerW==2)
                {
                    Player1Health-=20;

                }
            }
        }
        break;
    case Thunder:

        wW=(hW/((float)WassimPics[IndexW+ThunderStartW]->h/(float)WassimPics[IndexW+ThunderStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+ThunderStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if (effW<50 &&IndexW>=ThundercountW-1)
        {
            if (PlayerW==1)
            {
                draw_image_ex(ThunderEffet[effW],xW-25+((x-xW-20)/50)*effW,-7+effW/3,70+effW/4,100,NONE,100);
            }
            if (PlayerW==2)
            {
                draw_image_ex(ThunderEffet[effW],xW-30+((x-xW)/50)*effW,-7+effW/3,70+effW/4,100,NONE,100);
            }
            effW++;

        }


        if(FrameCount%10==0)
        {
            if(IndexW<ThundercountW-1)
            {
                IndexW++;
                IndexCollissionW++;
            }

            if(IndexW==ThundercountW-1 && effW>=50)
            {
                OnAttack=1;

                etatW=Stable;
                         IndexW=0;
         IndexCollissionW=StableStartW;
                if (PlayerW==1)
                {
                    Player2Health-=20;
                }
                if (PlayerW==2)
                {
                    Player1Health-=20;

                }
            }
        }

        break;

    case Wind:
        wW=(hW/((float)WassimPics[IndexW+WindStartW]->h/(float)WassimPics[IndexW+WindStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+WindStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if (effW<50 &&IndexW>=WindcountW-1)
        {
            if (PlayerW==1)
            {
                draw_image_ex(WindEffet[effW],xW+10+((x-xW-20)/50)*effW,50-effW/3,20+effW,30+effW,NONE,100);
            }
            if (PlayerW==2)
            {
                draw_image_ex(WindEffet[effW],xW-15+((x-xW)/50)*effW,50-effW/3,20+effW,30+effW,NONE,100);
            }

            effW++;

        }


        if(FrameCount%10==0)
        {
            if(IndexW<WindcountW-1)
            {
                IndexW++;
                IndexCollissionW++;
            }

            if(IndexW>=WindcountW-1 && effW>=50)
            {
                OnAttack=1;

                etatW=Stable;
                         IndexW=0;
         IndexCollissionW=StableStartW;
                if (PlayerW==1)
                {
                    Player2Health-=20;
                }
                if (PlayerW==2)
                {
                    Player1Health-=20;

                }
            }
        }

        break;
    case Freeze:
        wW=(hW/((float)WassimPics[IndexW+FreezeStartW]->h/(float)WassimPics[IndexW+FreezeStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+FreezeStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if ( IndexW>=FreezecountW-1)
        {
            if (PlayerW==1)
            {
                draw_image_ex(FreezeEffet[1],x-15,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-15,35,20,0,NONE,100);
            }
            if (PlayerW==2)
            {
                draw_image_ex(FreezeEffet[1],x-5,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-5,35,20,0,NONE,100);
            }
        }
        if(FrameCount%10==0)
        {
            if(IndexW<FreezecountW-1)
            {
                IndexW++;
                IndexCollissionW++;
            }
            if(IndexW>=FreezecountW-1 && FrameCount%120==0)
            {
                OnAttack=1;

                etatW=Stable;
                         IndexW=0;
         IndexCollissionW=StableStartW;
                if (PlayerW==1)
                {
                    Player2Health-=20;
                }
                if (PlayerW==2)
                {
                    Player1Health-=20;

                }
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
         IndexW=0;
         IndexCollissionW=StableStartW;
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
            IndexCollissionW++;
            if(IndexW>=UpCountW)
            {
                etatW=Stable;
                         IndexW=0;
         IndexCollissionW=StableStartW;
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
                         IndexW=0;
         IndexCollissionW=StableStartW;
            }
        }
        break;

    case Fall:
        wW=(hW/((float)WassimPics[IndexW+FallStartW]->h/(float)WassimPics[IndexW+FallStartW]->w))/AspectRatio;
        if(PlayerW==2) xW-=wW;
        draw_image_ex(WassimPics[IndexW+FallStartW],xW,yW,wW,hW,vflip,100);
        if(PlayerW==2) xW+=wW;
        if(FrameCount%10==0  )
        {
            IndexW++;
            IndexCollissionW++;
            if (IndexW>=FallcountW)
            {

                if (PlayerW==1 && Player1Health<5)
                    Player1Health=0;
                if (PlayerW==2 && Player2Health<5)
                    Player2Health=0;
                if (PlayerW==1 && Player1Health>5)
                    {etatW=Up;
                    IndexW=0;
                    IndexCollissionW=FallStartW;
                    }
                if (PlayerW==2 && Player2Health>5)
                    {etatW=Up;
                    IndexW=0;
                    IndexCollissionW=FallStartW;
                    }
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
                         IndexW=0;
         IndexCollissionW=StableStartW;
            }
        }
        break;

    case Jump:
        if(FrameCount%10==0)
        {
            if(IndexW>=JumpcountW-1)
                {
                etatW=Stable;
                     IndexW=0;
         IndexCollissionW=StableStartW;
            yW=65;
            }
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



