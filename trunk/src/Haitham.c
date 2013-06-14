#include "includes.h"


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
    yH=45;
    wH=20;
    hH=50;


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
int effH=0;

void Draw_Haitham()
{
    int x,y,w,h,IndexVs,VsSuperPower;

    flip vflip;
    Point ** TAB;
    IMAGE ** Vs;
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
            if (FrameCount%2==0)
                draw_image_ex(Power1,0,0,100,0,NONE,100);
            if (FrameCount%3==0)
                draw_image_ex(Power1,0,0,100,0,NONE,100);
        }
    }
    if (PlayerH==2)
    {
        if (Combot2==10)
        {
            SuperPowerH=1;
            if (FrameCount%2==0)
                draw_image_ex(Power2,0,0,100,0,NONE,100);
            if (FrameCount%3==0)
                draw_image_ex(Power2,0,0,100,0,NONE,100);
        }
    }
    switch (etatH)
    {
    case Stable :
    case Forward :
    case Backward :
    case Crouch :

        if(PlayerH==2)
            xH-=wH;
        if (PlayerH==1)
            x-=w;
        if(ProcessCollision(HaithamPics,IndexCollissionH,HaithamCollision,xH,yH,wH,hH,
                            Vs,IndexVs,TAB,x,y,w,h) && (EtatVS==Punch || EtatVS==Kick))
        {
           if (EtatVS==Punch)
    ComboPunch=1;
if (EtatVS==Kick)
    Combokick=1;
            etatH=Hit;
            IndexH=0;
            IndexCollissionH=HitStartH;
            if (PlayerH==2 )
            {
                Player2Health-=2.5;
                if (VsSuperPower==0 && Combot1<10)
                    Combot1++;
                if (Player2Health<5)
                   {
                       etatH=Fall;
IndexH=0;
IndexCollissionH=FallStartH;
            }
                   }
            if (PlayerH==1 )
            {
                Player1Health-=2.5;
                if (VsSuperPower==0 && Combot2<10)
                    Combot2++;
                if (Player1Health<5)
        {
etatH=Fall;
IndexH=0;
IndexCollissionH=FallStartH;
        }
        }
        }
        if(PlayerH==2)
            xH+=wH;
        if (PlayerH==1)
            x+=w;

        break;
    }

    if (OnAttack==1)
    {
        etatH=Fall;
        OnAttack=0;
        IndexH=0;
IndexCollissionH=FallStartH;
    }
    if(etatH!=Kick && etatH!=Punch && etatH!=Fireball && etatH != Freeze && etatH !=Jump  && etatH !=Wind && etatH !=Thunder &&etatH!=Fall&&etatH!=Hit&&etatH!=Defence&&etatH!=Up &&etatH!=Crouch)
    {
        while (xH>99.0)
            xH--;
        while (xH<1.0)
            xH++;

        if(PlayerH==2)
            xH-=wH;
        if (PlayerH==1)
            x-=w;

        while(ProcessCollision(HaithamPics,IndexCollissionH,HaithamCollision,xH,yH,wH,hH,
                               Vs,IndexVs,TAB,x,y,w,h) )
        {
            if (PlayerH==2 )
                xH+=0.05;
            if (PlayerH==1 )
                xH-=0.05;
        }
        if(PlayerH==2 )
            xH+=wH;
        if (PlayerH==1)
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
        else if(IsKeyPressed(PlayerH,RIGHT) &&xH<99.0)
        {
            etatH=Forward;
            xH+=0.50;
            IndexCollissionH=WalkStartH;

        }
        else if (IsKeyPressed(PlayerH,LEFT) && xH>1.0)
        {
            etatH=Backward;
            xH-=0.50;
            IndexCollissionH=WalkStartH;
        }
        else if (IsKeyPressed(PlayerH,UP))
        {
            IndexH=0;
            iH=1;
            etatH=Jump;
            IndexCollissionH=JumpStartH;
        }
        else if (IsKeyPressed(PlayerH,DOWN))
        {
            etatH=Crouch;
            IndexH=0;
            IndexCollissionH=CrouchStartH;
        }
        else if (IsKeyPressed(PlayerH,FIREBALL)&& SuperPowerH==1 /*&& FireH==1*/)
        {
            effH=0;
            etatH=Fireball;
            IndexH=0;
            IndexCollissionH=FireballStartH;
            SuperPowerH=0;
            if (PlayerH==1)
            {
                Combot1=0;
            }
            if (PlayerH==2)
            {
                Combot2=0;
            }
        }
        else if (IsKeyPressed(PlayerH,FREEZE)&& SuperPowerH==1/* && FreezeH==1*/)
        {
            effH=0;
            etatH=Freeze;
            IndexH=0;
            IndexCollissionH=FreezeStartH;
            SuperPowerH=0;
            if (PlayerH==1)
            {
                Combot1=0;
            }
            if (PlayerH==2)
            {
                Combot2=0;
            }
        }
        else if (IsKeyPressed(PlayerH,THUNDER)&& SuperPowerH==1 /*&& ThunderH==1*/)
        {
            effH=0;
            etatH=Thunder;
            IndexH=0;
            IndexCollissionH=ThunderStartH;
            SuperPowerH=0;
            if (PlayerH==1)
            {
                Combot1=0;
            }
            if (PlayerH==2)
            {
                Combot2=0;
            }
        }
        else if (IsKeyPressed(PlayerH,WIND) && SuperPowerH==1 /*&& WindH==1*/)
        {
            effH=0;
            etatH=Wind;
            IndexH=0;
            IndexCollissionH=WindStartH;
            SuperPowerH=0;
            if (PlayerH==1)
            {
                Combot1=0;
            }
            if (PlayerH==2)
            {
                Combot2=0;
            }
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
          IndexH=0;
IndexCollissionH=StableStartH;
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
        if(FrameCount%8==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=PunchCountH)
            {
                etatH=Stable;
          IndexH=0;
IndexCollissionH=StableStartH;
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

        if (effH<50 && IndexH>=FireballCountH-1)
        {
            if (PlayerH==1)
            {
                draw_image_ex(FireEffet[effH],xH+10+((x-xH-20)/50)*effH,55,5+effH/5,0,NONE,100);
            }
            if (PlayerH==2)
            {
                draw_image_ex(FireEffet[effH],xH-15-((xH-x-12)/50)*effH,55,5+effH/5,0,NONE,100);
            }
            effH++;

        }

        if(FrameCount%10==0)
        {
            if(IndexH<FireballCountH-1)
            {
                IndexH++;
                IndexCollissionH++;
            }
            if(IndexH>=FireballCountH-1 && effH>=50)
            {                OnAttack=1;

                etatH=Stable;
                          IndexH=0;
IndexCollissionH=StableStartH;
                if (PlayerH==1)
                {
                    Player2Health-=20;
                }
                if (PlayerH==2)
                {
                    Player1Health-=20;

                }
            }
        }
    }
    break;
    case Thunder:


        wH=(hH/((float)HaithamPics[IndexH+ThunderStartH]->h/(float)HaithamPics[IndexH+ThunderStartH]->w))/AspectRatio;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+ThunderStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;

        if (effH<50 &&IndexH>=ThunderCountH-1)
        {
            if (PlayerH==1)
            {
                draw_image_ex(ThunderEffet[effH],xH-25+((x-xH-20)/50)*effH,-7+effH/3,70+effH/4,100,NONE,100);
            }
            if (PlayerH==2)
            {
                draw_image_ex(ThunderEffet[effH],xH-30+((x-xH)/50)*effH,-7+effH/3,70+effH/4,100,NONE,100);
            }
            effH++;

        }


        if(FrameCount%10==0)
        {
            if(IndexH<ThunderCountH-1)
            {
                IndexH++;
                IndexCollissionH++;
            }

            if(IndexH==ThunderCountH-1 && effH>=50)
            {                OnAttack=1;

                etatH=Stable;
                          IndexH=0;
IndexCollissionH=StableStartH;
                if (PlayerH==1)
                {
                    Player2Health-=20;
                }
                if (PlayerH==2)
                {
                    Player1Health-=20;

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

        if (effH<50 &&IndexH>=WindCountH-1)
        {
            if (PlayerH==1)
            {
                draw_image_ex(WindEffet[effH],xH+10+((x-xH-20)/50)*effH,50-effH/3,20+effH,30+effH,NONE,100);
            }
            if (PlayerH==2)
            {
                draw_image_ex(WindEffet[effH],xH-15+((x-xH)/50)*effH,50-effH/3,20+effH,30+effH,NONE,100);
            }

            effH++;

        }


        if(FrameCount%10==0)
        {
            if(IndexH<WindCountH-1)
            {
                IndexH++;
                IndexCollissionH++;
            }

            if(IndexH>=WindCountH-1 && effH>=50)
            {                OnAttack=1;

                etatH=Stable;
                          IndexH=0;
IndexCollissionH=StableStartH;
                if (PlayerH==1)
                {
                    Player2Health-=20;
                }
                if (PlayerH==2)
                {
                    Player1Health-=20;

                }
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
        if ( IndexH>=FreezeCountH-1)
        {
            if (PlayerH==1)
            {
                draw_image_ex(FreezeEffet[1],x-15,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-15,35,20,0,NONE,100);
            }
            if (PlayerH==2)
            {
                draw_image_ex(FreezeEffet[1],x-5,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-5,35,20,0,NONE,100);
            }
        }
        if(FrameCount%10==0)
        {
            if(IndexH<FreezeCountH-1)
            {
                IndexH++;
                IndexCollissionH++;
            }
            if(IndexH>=FreezeCountH-1 && FrameCount%120==0)
            {                OnAttack=1;

                etatH=Stable;
                          IndexH=0;
IndexCollissionH=StableStartH;
                if (PlayerH==1)
                {
                    Player2Health-=20;
                }
                if (PlayerH==2)
                {
                    Player1Health-=20;

                }
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
            if(IndexH==CrouchCountH)
            {
                etatH=Stable;
                          IndexH=0;
IndexCollissionH=StableStartH;
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
        if(FrameCount%15==0)
        {
            IndexH++;
            IndexCollissionH+=IndexH;

            if(IndexH>=UpCountH)
            {
                etatH=Stable;
                          IndexH=0;
IndexCollissionH=StableStartH;
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
                          IndexH=0;
IndexCollissionH=StableStartH;
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
        if(FrameCount%20==0  )
        {
            IndexH++;
            IndexCollissionH++;
            if (IndexH>=FallCountH)
            {

                if (PlayerH==1 && Player1Health<5)
                    Player1Health=0;
                if (PlayerH==2 && Player2Health<5)
                    Player2Health=0;
                if (PlayerH==1 && Player1Health>5)
                    {etatH=Up;
                    IndexH=0;
                    IndexCollissionH=StableStartH;
                    }
                if (PlayerH==2 && Player2Health>5)
                    {etatH=Up;
                    IndexH=0;
                    IndexCollissionH=StableStartH;
                    }
                    }
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
          IndexH=0;
IndexCollissionH=StableStartH;
yH=55;
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










