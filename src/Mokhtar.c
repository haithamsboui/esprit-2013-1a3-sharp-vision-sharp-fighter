#include "includes.h"


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
    IndexCollissionM=StableStartM;
    PlayerM=player;
    etatM=Stable;
    IndexM=0;
    yM=45;
    wM=20;
    hM=50;


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
int effM=0;

void Draw_Mokhtar(int CPU )
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
            if (FrameCount%2==0)
                draw_image_ex(Power1,0,0,100,0,NONE,100);
            if (FrameCount%3==0)
                draw_image_ex(Power1,0,0,100,0,NONE,100);
        }
    }
    if (PlayerM==2)
    {
        if (Combot2==10)
        {
            SuperPowerM=1;
            if (FrameCount%2==0)
                draw_image_ex(Power2,0,0,100,0,NONE,100);
            if (FrameCount%3==0)
                draw_image_ex(Power2,0,0,100,0,NONE,100);
        }
    }

    switch (etatM)
    {

    case Stable :
    case Forward :
    case Backward :
    case Crouch :
        if(PlayerM==2)
            xM-=wM;
        if (PlayerM==1)
            x-=w;
        if(ProcessCollision(MokhtarPics,IndexCollissionM,MokhtarCollision,xM,yM,wM,hM,
                            Vs,IndexVs,TAB,x,y,w,h)&& (etatVS==Punch || etatVS==Kick))
        {

            if (etatVS==Punch)
                ComboPunch=1;
            if (etatVS==Kick)
                Combokick=1;
            etatM=Hit;
            IndexM=0;
            IndexCollissionM=HitStartM;
            if (PlayerM==2)
            {
                Player2Health-=2.5;
                if (VsSuperPower==0 && Combot1<10)

                    Combot1++;
                if (Player2Health<5)
                {
                    etatM=Fall;
                    IndexM=0;
                    IndexCollissionM=FallStartM;
                }

            }
            if (PlayerM==1)
            {
                Player1Health-=2.5;
                if (VsSuperPower==0 && Combot2<10)
                    Combot2++;
                if (Player1Health<5)
                {
                    etatM=Fall;
                    IndexM=0;
                    IndexCollissionM=FallStartM;
                }
            }

        }

        if(PlayerM==2)
            xM+=wM;
        if (PlayerM==1)
            x+=w;
        break;

    }

    if (OnAttack==1)
    {
        etatM=Fall;
        OnAttack=0;
        IndexM=0;
        IndexCollissionM=FallStartM;
    }

       while (xM>99.0)
                xM--;
            while (xM<1.0)
                xM++;
            if(PlayerM==2)
                xM-=wM;
            if (PlayerM==1)
                x-=w;
            while(ProcessCollision(MokhtarPics,IndexCollissionM,MokhtarCollision,xM,yM,wM,hM,
                                   Vs,IndexVs,TAB,x,y,w,h))
            {
                if (PlayerM==2)
                    xM+=0.05;
                else
                    xM-=0.05;
            }
            if(PlayerM==2)
                xM+=wM;
            if (PlayerM==1)
                x+=w;

    if (CPU==0)
    {
        if(etatM!=Kick && etatM!=Punch && etatM!=Fireball && etatM != Freeze&& etatM != Fall && etatM !=Jump  && etatM !=Wind && etatM !=Thunder && etatM!=Hit &&etatM!=Defence && etatM!=Up &&etatM!=Crouch)
        {

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
            else if(IsKeyPressed(PlayerM,RIGHT) && xM<99.0 )
            {

                etatM=Forward;
                xM+=0.50;
                IndexCollissionM=WalkStartM;
            }
            else if (IsKeyPressed(PlayerM,LEFT) && xM> 1.0 )
            {


                etatM=Backward;
                xM-=0.50;
                IndexCollissionM=WalkStartM;


            }
            else if (IsKeyPressed(PlayerM,UP))
            {
                IndexM=0;
                iM=1;

                etatM=Jump;
                IndexCollissionM=JumpStartM;

            }
            else if (IsKeyPressed(PlayerM,DOWN))
            {
                etatM=Crouch;
                IndexM=0;
                IndexCollissionM=CrouchStartM;
            }
            else if (IsKeyPressed(PlayerM,FIREBALL) && SuperPowerM==1/* && FireM==1*/)
            {
                effM=0;
                etatM=Fireball;
                IndexM=0;
                IndexCollissionM=FireballStartM;
                SuperPowerM=0;

                if (PlayerM==1)
                {
                    Combot1=0;
                }
                if (PlayerM==2)
                {
                    Combot2=0;
                }

            }
            else if (IsKeyPressed(PlayerM,FREEZE) && SuperPowerM==1 /* && FreezeM==1*/)
            {
                effM=0;
                etatM=Freeze;
                IndexM=0;
                IndexCollissionM=FreezeStartM;
                SuperPowerM=0;
                if (PlayerM==1)
                {
                    Combot1=0;
                }
                if (PlayerM==2)
                {
                    Combot2=0;
                }

            }
            else if (IsKeyPressed(PlayerM,THUNDER) && SuperPowerM==1 /*&& ThunderM==1*/)
            {
                effM=0;
                etatM=Thunder;
                IndexM=0;
                IndexCollissionM=ThunderStartM;
                SuperPowerM=0;
                if (PlayerM==1)
                {
                    Combot1=0;
                }
                if (PlayerM==2)
                {
                    Combot2=0;
                }

            }
            else if (IsKeyPressed(PlayerM,WIND)&& SuperPowerM==1 /*&& WindM==1*/)
            {
                effM=0;

                etatM=Wind;
                IndexM=0;
                IndexCollissionM=WindStartM;
                SuperPowerM=0;
                if (PlayerM==1)
                {
                    Combot1=0;
                }
                if (PlayerM==2)
                {
                    Combot2=0;
                }

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
            IndexCollissionM=((IndexCollissionM+1)%WalkCountM);
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
            IndexCollissionM=((IndexCollissionM+1)%WalkCountM);

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
        if(FrameCount%5==0)
        {
            IndexM++;
            IndexCollissionM+=IndexM;

            if(IndexM==KickCountM)
            {
                etatM=Stable;
                IndexM=0;
                IndexCollissionM=StableStartM;
            }
        }

        break;

    case Punch:
        wM=(hM/((float)MokhtarPics[IndexM+PunchStartM]->h/(float)MokhtarPics[IndexM+PunchStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+PunchStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%9==0)
        {
            IndexM++;
            IndexCollissionM+=IndexM;

            if(IndexM==PunchCountM)
            {
                etatM=Stable;
                IndexM=0;
                IndexCollissionM=StableStartM;
            }
        }
        break;
    case Fireball:
        wM=(hM/((float)MokhtarPics[IndexM+FireballStartM]->h/(float)MokhtarPics[IndexM+FireballStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+FireballStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if (effM<50 && IndexM>=FireballCountM-1)
        {
            if (PlayerM==1)
            {
                draw_image_ex(FireEffet[effM],xM+10+((x-xM-20)/50)*effM,55,5+effM/5,0,NONE,100);
            }
            if (PlayerM==2)
            {
                draw_image_ex(FireEffet[effM],xM-15-((xM-x-12)/50)*effM,55,5+effM/5,0,NONE,100);
            }
            effM++;

        }

        if(FrameCount%10==0)
        {
            if(IndexM<FireballCountM-1)
            {
                IndexM++;
                IndexCollissionM++;
            }
            if(IndexM>=FireballCountM-1 && effM>=50)
            {
                OnAttack=1;

                etatM=Stable;
                IndexM=0;
                IndexCollissionM=StableStartM;
                if (PlayerM==1)
                {
                    Player2Health-=20;
                }
                if (PlayerM==2)
                {
                    Player1Health-=20;

                }
            }
        }
        break;
    case Thunder:

        wM=(hM/((float)MokhtarPics[IndexM+ThunderStartM]->h/(float)MokhtarPics[IndexM+ThunderStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+ThunderStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;

        if (effM<50 &&IndexM>=ThunderCountM-1)
        {
            if (PlayerM==1)
            {
                draw_image_ex(ThunderEffet[effM],xM-25+((x-xM-20)/50)*effM,-7+effM/3,70+effM/4,100,NONE,100);
            }
            if (PlayerM==2)
            {
                draw_image_ex(ThunderEffet[effM],xM-30+((x-xM)/50)*effM,-7+effM/3,70+effM/4,100,NONE,100);
            }
            effM++;

        }


        if(FrameCount%10==0)
        {
            if(IndexM<ThunderCountM-1)
            {
                IndexM++;
                IndexCollissionM++;
            }

            if(IndexM==ThunderCountM-1 && effM>=50)
            {
                OnAttack=1;

                etatM=Stable;
                IndexM=0;
                IndexCollissionM=StableStartM;
                if (PlayerM==1)
                {
                    Player2Health-=20;
                }
                if (PlayerM==2)
                {
                    Player1Health-=20;

                }
            }
        }
        break;

    case Wind:
        wM=(hM/((float)MokhtarPics[IndexM+WindStartM]->h/(float)MokhtarPics[IndexM+WindStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+WindStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if (effM<50 &&IndexM>=WindCountM-1)
        {
            if (PlayerM==1)
            {
                draw_image_ex(WindEffet[effM],xM+10+((x-xM-20)/50)*effM,50-effM/3,20+effM,30+effM,NONE,100);
            }
            if (PlayerM==2)
            {
                draw_image_ex(WindEffet[effM],xM-15+((x-xM)/50)*effM,50-effM/3,20+effM,30+effM,NONE,100);
            }

            effM++;

        }


        if(FrameCount%10==0)
        {
            if(IndexM<WindCountM-1)
            {
                IndexM++;
                IndexCollissionM++;
            }

            if(IndexM>=WindCountM-1 && effM>=50)
            {
                OnAttack=1;

                etatM=Stable;
                IndexM=0;
                IndexCollissionM=StableStartM;
                if (PlayerM==1)
                {
                    Player2Health-=20;
                }
                if (PlayerM==2)
                {
                    Player1Health-=20;

                }
            }
        }


        break;
    case Freeze:
        wM=(hM/((float)MokhtarPics[IndexM+FreezeStartM]->h/(float)MokhtarPics[IndexM+FreezeStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+FreezeStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if ( IndexM>=FreezeCountM-1)
        {
            if (PlayerM==1)
            {
                draw_image_ex(FreezeEffet[1],x-15,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-15,35,20,0,NONE,100);
            }
            if (PlayerM==2)
            {
                draw_image_ex(FreezeEffet[1],x-5,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-5,35,20,0,NONE,100);
            }
        }
        if(FrameCount%10==0)
        {
            if(IndexM<FreezeCountM-1)
            {
                IndexM++;
                IndexCollissionM++;
            }
            if(IndexM>=FreezeCountM-1 && FrameCount%120==0)
            {
                OnAttack=1;

                etatM=Stable;
                IndexM=0;
                IndexCollissionM=StableStartM;
                if (PlayerM==1)
                {
                    Player2Health-=20;
                }
                if (PlayerM==2)
                {
                    Player1Health-=20;

                }
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
            IndexCollissionM++;

            if(IndexM>=CrouchCountM)
            {
                etatM=Stable;
                IndexM=0;
                IndexCollissionM=StableStartM;
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

            if(IndexM>=DefenceCountM)
            {
                etatM=Stable;
                IndexM=0;
                IndexCollissionM=StableStartM;
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
                IndexM=0;
                IndexCollissionM=StableStartM;
            }
        }
        break;

    case Fall:
        wM=(hM/((float)MokhtarPics[IndexM+FallStartM]->h/(float)MokhtarPics[IndexM+FallStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+FallStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;
        if(FrameCount%15==0  )
        {
            IndexM++;
            IndexCollissionM++;
            if (IndexM>=FallCountM)
            {

                if (PlayerM==1 && Player1Health<5)
                    Player1Health=0;
                if (PlayerM==2 && Player2Health<5)
                    Player2Health=0;
                if (PlayerM==1 && Player1Health>5)
                {
                    etatM=Up;
                    IndexM=0;
                    IndexCollissionM=UpStartM;
                }
                if (PlayerM==2 && Player2Health>5)
                {
                    etatM=Up;
                    IndexM=0;
                    IndexCollissionM=UpStartM;
                }
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
                IndexM=0;
                IndexCollissionM=StableStartM;
            }
        }
        break;

    case Jump:

        if(FrameCount%7==0)
        {
            if(IndexM>=JumpCountM-1)
            {
                etatM=Stable;
                IndexM=0;
                IndexCollissionM=StableStartM;
                yM=52;
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
            IndexCollissionM++;
        }
        wM=(hM/((float)MokhtarPics[IndexM+JumpStartM]->h/(float)MokhtarPics[IndexM+JumpStartM]->w))/AspectRatio;
        if(PlayerM==2) xM-=wM;
        draw_image_ex(MokhtarPics[IndexM+JumpStartM],xM,yM,wM,hM,vflip,100);
        if(PlayerM==2) xM+=wM;

        break;


    default:
        break;
    }
}


