#include "includes.h"


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
    IndexCollissionS=StableStartS;
    PlayerS=player;
    etatS=Stable;
    IndexS=0;
    yS=45;
    wS=20;
    hS=50;
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
int CollisionStatS=StableStartS;
int SuperPowerS=0;
int iS=1;
int effS=0;
void Draw_Salah(int CPU)
{
     EtatPlayer Def[]= {Defence,Crouch,Stable},Attack[]= {Punch,Kick,Stable},Spower[]= {Fireball,Freeze,Thunder,Wind},Mov[]= {Forward,Backward,Stable};
    int def,att,spow,mov;
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
        if (Combot1>=10)
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
        if (Combot2>=10)
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
    case Forward :
    case Backward :
    case Crouch :
        if(PlayerS==2)
            xS-=wS;
        if (PlayerS==1)
            x-=w;
        if(ProcessCollision(SalahPics,IndexCollissionS,SalahCollision,xS,yS,wS,hS,
                            Vs,IndexVs,TAB,x,y,w,h)&& (etatVS==Punch || etatVS==Kick))
        {
            if (etatVS==Punch)
                ComboPunch=1;
            if (etatVS==Kick)
                Combokick=1;
            etatS=Hit;
            IndexS=0;
            IndexCollissionS=HitStartS;
            if (PlayerS==2)
            {
                Player2Health-=2.5;

                if (VsSuperPower==0 && Combot1<10)
                    Combot1++;

                if (Player2Health<5)
                {
                    etatS=Fall;
                    IndexS=0;
                    IndexCollissionS=FallStartS;
                }

            }
            if (PlayerS==1)
            {
                Player1Health-=2.5;

                if (VsSuperPower==0 && Combot2<10)
                    Combot2++;

                if (Player1Health<5)
                {
                    etatS=Fall;
                    IndexS=0;
                    IndexCollissionS=FallStartS;
                }
            }
        }


        if(PlayerS==2)
            xS+=wS;
        if (PlayerS==1)
            x+=w;
        break;
    }

    if (OnAttack==1)
    {
        etatS=Fall;
        OnAttack=0;
        IndexS=0;
        IndexCollissionS;
    }

    while (xS>99.0)
        xS--;
    while (xS<1.0)
        xS++;
    if(PlayerS==2)
        xS-=wS;
    if (PlayerS==1)
        x-=w;
    while( ProcessCollision(SalahPics,IndexCollissionS,SalahCollision,xS,yS,wS,hS,
                            Vs, IndexVs, TAB, x,y,w,h))
    {
        if (PlayerS==2)
            xS+=0.05;
        else
            xS-=0.05;
    }
    if(PlayerS==2)
        xS+=wS;
    if (PlayerS==1)
        x+=w;
    if(etatS!=Kick && etatS!=Punch && etatS!=Fireball && etatS != Freeze && etatS !=Jump  && etatS !=Wind && etatS !=Thunder &&etatS!=Hit&&etatS!=Defence&&etatS!=Up && etatS!=Crouch && etatS!=Fall)
    {
        if (CPU==0)
        {


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
            else if(IsKeyPressed(PlayerS,RIGHT) && xS<99.0)
            {
                etatS=Forward;
                xS+=0.50;
                IndexCollissionS=WalkStartS;
            }
            else if (IsKeyPressed(PlayerS,LEFT) && xS>1.0)
            {
                etatS=Backward;
                xS-=0.50;
                IndexCollissionS=WalkStartS;
            }
            else if (IsKeyPressed(PlayerS,UP))
            {
                IndexS=0;
                iS=1;
                etatS=Jump;
                IndexCollissionS=JumpStartS;


            }
            else if (IsKeyPressed(PlayerS,DOWN))
            {
                etatS=Crouch;
                IndexS=0;
                IndexCollissionS=CrouchStartS;
            }
            else if (IsKeyPressed(PlayerS,FIREBALL)&& SuperPowerS==1/*&& FireS==1*/)
            {
                effS=0;

                etatS=Fireball;
                IndexS=0;
                IndexCollissionS=FireballStartS;
                SuperPowerS=0;
                if (PlayerS==1)
                {
                    Combot1=0;
                }
                if (PlayerS==2)
                {
                    Combot2=0;
                }
            }
            else if (IsKeyPressed(PlayerS,FREEZE)&& SuperPowerS==1 /*&& FreezeS==1*/)
            {
                effS=0;

                etatS=Freeze;
                IndexS=0;
                IndexCollissionS=FreezeStartS;
                SuperPowerS=0;
                if (PlayerS==1)
                {
                    Combot1=0;
                }
                if (PlayerS==2)
                {
                    Combot2=0;
                }
            }
            else if (IsKeyPressed(PlayerS,THUNDER)&& SuperPowerS==1/*&& ThunderS==1*/)
            {
                effS=0;
                etatS=Thunder;
                IndexS=0;
                IndexCollissionS=ThunderStartS;
                SuperPowerS=0;
                if (PlayerS==1)
                {
                    Combot1=0;
                }
                if (PlayerS==2)
                {
                    Combot2=0;
                }
            }
            else if (IsKeyPressed(PlayerS,WIND)&& SuperPowerS==1/*&& WindS==1*/)
            {
                effS=0;

                etatS=Wind;
                IndexS=0;
                IndexCollissionS=WindStartS;
                SuperPowerS=0;
                if (PlayerS==1)
                {
                    Combot1=0;
                }
                if (PlayerS==2)
                {
                    Combot2=0;
                }
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



        if (CPU==1)
        {
            switch (etatVS)
            {

            case Fireball:
            case Freeze :
            case Thunder :
            case Wind :
                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;
                break;
            case Punch :
            case Kick :
                if (-x+xS<5)
                    def=Random(0,2);

                switch (def)
                {
                case 0 :
                    IndexS=0;
                    IndexCollissionS=DefenceStartS;
                    etatS=Defence;
                    break;

                case 2 :
                    etatS=Stable;
                    IndexS=0;
                    IndexCollissionS=StableStartS;
                    break;
                }

                break;

            case Stable :
            case Crouch :
            case Forward:
            case Backward :
                if(xS-x>20)
                {
                    mov=Random(0,2);
                    switch (mov)
                    {
                    case 0 :
                        if (xS<99)
                        {
                            xS+=0.50;
                            IndexCollissionS=WalkStartS;
                            etatS=Forward;
                        }
                        break;
                    case 1 :
                        if (xS>=x)
                        {
                            etatS=Backward;
                            xS-=0.50;
                            IndexCollissionS=WalkStartS;
                        }
                        break;
                    case 2 :
                        etatS=Stable;
                        IndexS=0;
                        IndexCollissionS=StableStartS;
                        break;
                    }
                }

                if(xS-x<35)
                {
                    if (SuperPowerS==0)
                    {
                        att=Random(0,2);
                        switch (att)
                        {
                        case 0 :
                            etatS=Punch;
                            IndexS=0;
                            IndexCollissionS=PunchStartS;
                            CollisionStatS=1;
                            break;
                        case 1 :
                            etatS=Kick;
                            IndexS=0;
                            IndexCollissionS=KickStartS;
                            CollisionStatS=1;
                            break;
                        case 2 :
                            etatS=Stable;
                            IndexS=0;
                            IndexCollissionS=StableStartS;
                            break;
                        }
                    }
                    else
                    {
                        spow=Random(0,3);
                        switch (spow)
                        {
                        case 0 :
                            etatS=Fireball;
                            effS=0;
                            IndexS=0;
                            IndexCollissionS=FireballStartS;
                            SuperPowerS=0;
                            Combot2=0;

                            break;
                        case 1 :
                            etatS=Freeze;
                            effS=0;
                            IndexS=0;
                            IndexCollissionS=FreezeStartS;
                            SuperPowerS=0;
                            Combot2=0;
                            break;
                        case 2 :
                            etatS=Thunder;
                            effS=0;
                            IndexS=0;
                            IndexCollissionS=ThunderStartS;
                            SuperPowerS=0;
                            Combot2=0;

                            break;
                        case 3 :
                            etatS=Wind;
                            effS=0;
                            IndexS=0;
                            IndexCollissionS=WindStartS;
                            SuperPowerS=0;
                            Combot2=0;

                            break;
                        }
                    }
                }
                break;
            default:
                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;
                break;
            }
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
        if(FrameCount%9==0)
        {
            IndexS++;
            IndexCollissionS+=IndexS;

            if(IndexS==KickCountS)
            {
                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;
            }
        }

        break;

    case Punch:
        wS=(hS/((float)SalahPics[IndexS+PunchStartS]->h/(float)SalahPics[IndexS+PunchStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+PunchStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%8==0)
        {
            IndexS++;
            IndexCollissionS++;

            if(IndexS==PunchCountS)
            {
                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;
            }
        }
        break;
    case Fireball:
        wS=(hS/((float)SalahPics[IndexS+FireballStartS]->h/(float)SalahPics[IndexS+FireballStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+FireballStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;

        if (effS<50 && IndexS>=FireballCountS-1)
        {
            if (PlayerS==1)
            {
                draw_image_ex(FireEffet[effS],xS+10+((x-xS-20)/50)*effS,55,5+effS/5,0,NONE,100);
            }
            if (PlayerS==2)
            {
                draw_image_ex(FireEffet[effS],xS-15-((xS-x-12)/50)*effS,55,5+effS/5,0,NONE,100);
            }
            effS++;

        }

        if(FrameCount%10==0)
        {
            if(IndexS<FireballCountS-1)
            {
                IndexS++;
                IndexCollissionS++;
            }
            if(IndexS>=FireballCountS-1 && effS>=50)
            {
                OnAttack=1;

                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;
                if (PlayerS==1)
                {
                    Player2Health-=20;
                }
                if (PlayerS==2)
                {
                    Player1Health-=20;

                }
            }
        }
        break;
    case Thunder:

        wS=(hS/((float)SalahPics[IndexS+ThunderStartS]->h/(float)SalahPics[IndexS+ThunderStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+ThunderStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;

        if (effS<50 &&IndexS>=ThunderCountS-1)
        {
            if (PlayerS==1)
            {
                draw_image_ex(ThunderEffet[effS],xS-25+((x-xS-20)/50)*effS,-7+effS/3,70+effS/4,100,NONE,100);
            }
            if (PlayerS==2)
            {
                draw_image_ex(ThunderEffet[effS],xS-30+((x-xS)/50)*effS,-7+effS/3,70+effS/4,100,NONE,100);
            }
            effS++;

        }


        if(FrameCount%10==0)
        {
            if(IndexS<ThunderCountS-1)
            {
                IndexS++;
                IndexCollissionS++;
            }

            if(IndexS==ThunderCountS-1 && effS>=50)
            {
                OnAttack=1;

                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;

                if (PlayerS==1)
                {
                    Player2Health-=20;
                }
                if (PlayerS==2)
                {
                    Player1Health-=20;
                }
            }
        }
        break;

    case Wind:
        wS=(hS/((float)SalahPics[IndexS+WindStartS]->h/(float)SalahPics[IndexS+WindStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+WindStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if (effS<50 &&IndexS>=WindCountS-1)
        {
            if (PlayerS==1)
            {
                draw_image_ex(WindEffet[effS],xS+10+((x-xS-20)/50)*effS,50-effS/3,20+effS,30+effS,NONE,100);
            }
            if (PlayerS==2)
            {
                draw_image_ex(WindEffet[effS],xS-15+((x-xS)/50)*effS,50-effS/3,20+effS,30+effS,NONE,100);
            }

            effS++;

        }


        if(FrameCount%10==0)
        {
            if(IndexS<WindCountS-1)
            {
                IndexS++;
                IndexCollissionS++;
            }

            if(IndexS>=WindCountS-1 && effS>=50)
            {
                OnAttack=1;

                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;
                if (PlayerS==1)
                {
                    Player2Health-=20;
                }
                if (PlayerS==2)
                {
                    Player1Health-=20;

                }
            }
        }
        break;
    case Freeze:
        wS=(hS/((float)SalahPics[IndexS+FreezeStartS]->h/(float)SalahPics[IndexS+FreezeStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+FreezeStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if ( IndexS>=FreezeCountS-1)
        {
            if (PlayerS==1)
            {
                draw_image_ex(FreezeEffet[1],x-15,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-15,35,20,0,NONE,100);
            }
            if (PlayerS==2)
            {
                draw_image_ex(FreezeEffet[1],x-5,35,20,0,NONE,100);

                if (FrameCount%5)
                    draw_image_ex(FreezeEffet[0],x-5,35,20,0,NONE,100);
            }
        }
        if(FrameCount%10==0)
        {
            if(IndexS<FreezeCountS-1)
            {
                IndexS++;
                IndexCollissionS++;
            }
            if(IndexS>=FreezeCountS-1 && FrameCount%120==0)
            {
                OnAttack=1;

                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;
                if (PlayerS==1)
                {
                    Player2Health-=20;
                }
                if (PlayerS==2)
                {
                    Player1Health-=20;

                }
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
                IndexS=0;
                IndexCollissionS=StableStartS;
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
            IndexCollissionS++;

            if(IndexS==UpCountS)
            {
                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;
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
                IndexS=0;
                IndexCollissionS=StableStartS;
            }
        }
        break;

    case Fall:
        wS=(hS/((float)SalahPics[IndexS+FallStartS]->h/(float)SalahPics[IndexS+FallStartS]->w))/AspectRatio;
        if(PlayerS==2) xS-=wS;
        draw_image_ex(SalahPics[IndexS+FallStartS],xS,yS,wS,hS,vflip,100);
        if(PlayerS==2) xS+=wS;
        if(FrameCount%15==0)
        {
            IndexS++;
            IndexCollissionS++;
            if (IndexS>=FallCountS)
            {
                if (PlayerS==1 && Player1Health<5)
                    Player1Health=0;
                if (PlayerS==2 && Player2Health<5)
                    Player2Health=0;
                if (PlayerS==1 && Player1Health>5)
                {
                    etatS=Up;
                    IndexS=0;
                    IndexCollissionW=UpStartS;
                }
                if (PlayerS==2 && Player2Health>5)
                {
                    etatS=Up;
                    IndexS=0;
                    IndexCollissionW=UpStartS;
                }
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
                IndexS=0;
                IndexCollissionS=StableStartS;
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
            {
                etatS=Stable;
                IndexS=0;
                IndexCollissionS=StableStartS;
                yS=55;
            }
            if (IndexS>=2)
                jump_stat=0;
            if (jump_stat==1)
                yS-=10;
            if (jump_stat==0)
                yS+=20;
            IndexS++;
            IndexCollissionS++;
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


