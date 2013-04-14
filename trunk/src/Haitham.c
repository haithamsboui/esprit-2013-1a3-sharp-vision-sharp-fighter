#include "includes.h"

#define StableStartH 5
#define StableCountH 4

#define WalkStartH 16
#define WalkCountH 5

#define KickStartH 9
#define KickCountH 4

#define PunchStartH 22
#define PunchCountH 5

IMAGE *HaithamPics[27];

float xH,yH;
float wH,hH;
int directionH;
int PlayerH=0;
EtatPlayer etatH;
int IndexH;
float screen_ratioH;

void LoadHaitham(int player)
{
    int i;
    char path[255];
    for (i=0; i<27; i++)
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
    screen_ratioH=(float)SCREEN_W/(float)SCREEN_H;
}

int iH=1;
void Draw_Haitham()
{
    flip vflip;

    if(directionH)
        vflip=NONE;
    else
        vflip = VERTICAL;

    if(etatH!=Kick && etatH!=Punch)
    {
        if(IsKeyPressed(PlayerH,KICK))
        {
            etatH=Kick;
            IndexH=0;
        }
        else if(IsKeyPressed(PlayerH,PUNCH))
        {
            etatH=Punch;
            IndexH=0;
        }
        else if(IsKeyPressed(PlayerH,RIGHT))
        {
            etatH=Forward;
            xH+=0.2;
        }
        else if (IsKeyPressed(PlayerH,LEFT))
        {
            etatH=Backward;
            xH-=0.2;
        }
        else
            etatH=Stable;
    }


    switch(etatH)
    {
    case Stable:
        if(FrameCount%10==0)
        {
            if(IndexH==0)
                iH=1;
            if(IndexH>=StableCountH-1)
                iH=-1;

            IndexH=IndexH+iH;
        }
        IndexH = Min(IndexH,StableCountH-1);
        wH=(hH/((float)HaithamPics[IndexH+StableStartH]->h/(float)HaithamPics[IndexH+StableStartH]->w))/screen_ratioH;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+StableStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        break;
    case Forward:
        if(FrameCount%10==0)
        {
            IndexH=((IndexH-1+WalkCountH)%WalkCountH);
        }
        IndexH = Min(IndexH,WalkCountH-1);
        wH=(hH/((float)HaithamPics[IndexH+WalkStartH]->h/(float)HaithamPics[IndexH+WalkStartH]->w))/screen_ratioH;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+WalkStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        break;

    case Backward:
        if(FrameCount%10==0)
        {
            IndexH=((IndexH+1)%WalkCountH);
        }
        IndexH = Min(IndexH,WalkCountH-1);
        wH=(hH/((float)HaithamPics[IndexH+WalkStartH]->h/(float)HaithamPics[IndexH+WalkStartH]->w))/screen_ratioH;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+WalkStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        break;

    case Kick:
        wH=(hH/((float)HaithamPics[IndexH+KickStartH]->h/(float)HaithamPics[IndexH+KickStartH]->w))/screen_ratioH;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+KickStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==KickCountH)
            {
                etatH=Stable;
            }
        }

        break;

    case Punch:
        wH=(hH/((float)HaithamPics[IndexH+PunchStartH]->h/(float)HaithamPics[IndexH+PunchStartH]->w))/screen_ratioH;
        if(PlayerH==2) xH-=wH;
        draw_image_ex(HaithamPics[IndexH+PunchStartH],xH,yH,wH,hH,vflip,100);
        if(PlayerH==2) xH+=wH;
        if(FrameCount%10==0)
        {
            IndexH++;
            if(IndexH==PunchCountH)
            {
                etatH=Stable;
            }
        }
        break;
    }
}

