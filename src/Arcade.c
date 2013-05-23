#include "includes.h"

void Arcade()
{
    int selectedplayer,nextmap,nextplayer;
    //Loading of data
    Cinematic1();
    rest(1000);
    selectedplayer=CharacterSelect();
    if(selectedplayer==-1) return;
    while((nextplayer=Random(0,4))==selectedplayer);
    nextmap=Random(0,4);
    CinematicVoice(selectedplayer,nextplayer,nextmap);
    GamePlay(selectedplayer,nextplayer,nextmap);
    CinematicWin(selectedplayer,nextplayer);

}

void Savegame ()
{
    set_config_file("Resources/Setting.cfg");
    set_config_int("Savegame","FireH",FireH);
    set_config_int("Savegame","ThunderH",ThunderH);
    set_config_int("Savegame","WindH",WindH);
    set_config_int("Savegame","FreezeH",FreezeH);
    set_config_int("Savegame","FireB",FireB);
    set_config_int("Savegame","ThunderB",ThunderB);
    set_config_int("Savegame","WindB",WindB);
    set_config_int("Savegame","FreezeB",FreezeB);
    set_config_int("Savegame","FireS",FireS);
    set_config_int("Savegame","ThunderS",ThunderS);
    set_config_int("Savegame","WindS",WindS);
    set_config_int("Savegame","FreezeS",FreezeS);
    set_config_int("Savegame","FireM",FireM);
    set_config_int("Savegame","ThunderM",ThunderM);
    set_config_int("Savegame","WindM",WindM);
    set_config_int("Savegame","FreezeM",FreezeM);
    set_config_int("Savegame","FireW",FireW);
    set_config_int("Savegame","ThunderW",ThunderW);
    set_config_int("Savegame","WindW",WindW);
    set_config_int("Savegame","FreezeW",FreezeW);
    flush_config_file();
}

void LoadSavegame ()
{
    set_config_file("Resources/Setting.cfg");
    get_config_int("Savegame","FireH",FireH);
    get_config_int("Savegame","ThunderH",ThunderH);
    get_config_int("Savegame","WindH",WindH);
    get_config_int("Savegame","FreezeH",FreezeH);
    get_config_int("Savegame","FireB",FireB);
    get_config_int("Savegame","ThunderB",ThunderB);
    get_config_int("Savegame","WindB",WindB);
    get_config_int("Savegame","FreezeB",FreezeB);
    get_config_int("Savegame","FireS",FireS);
    get_config_int("Savegame","ThunderS",ThunderS);
    get_config_int("Savegame","WindS",WindS);
    get_config_int("Savegame","FreezeS",FreezeS);
    get_config_int("Savegame","FireM",FireM);
    get_config_int("Savegame","ThunderM",ThunderM);
    get_config_int("Savegame","WindM",WindM);
    get_config_int("Savegame","FreezeM",FreezeM);
    get_config_int("Savegame","FireW",FireW);
    get_config_int("Savegame","ThunderW",ThunderW);
    get_config_int("Savegame","WindW",WindW);
    get_config_int("Savegame","FreezeW",FreezeW);
}

void Cinematic1()
{
    const char Storylines[]="Once upon a time, there was a team of talented developers called Sharp-Vision.\n" \
                            "They were asked to make a video game, but a game like NO OTHER.\n" \
                            " \n" \
                            " \n" \
                            " \n" \
                            "They started a brainstorming to get the perfect idea,\n" \
                            "and finally decided to go with a fight game.\n" \
                            " \n" \
                            " \n" \
                            " \n" \
                            " \n" \
                            " \n" \
                            " \n" \
                            " \n" \
                            " \n" \
                            "They started the development, and SUDDENLY!\n" \
                            "somethings went wrong with the code...\n" \
                            " \n" \
                            " \n" \
                            " \n" \
                            " \n" \
                            "THE MACHINE HAS SWALLOWED THEM INSIDE!!!";

    char buffer[100];
    int i,imageindex=0,timer,shaking=15;
    float xrand=0.5,yrand=0.5,TextY=100,TextSpeed=-0.025;
    IMAGE *powerups[39],*meeting[6],*swallow[2],*focuspoint,*storytext;

    for(i=0; i<39; i++)
    {
        sprintf(buffer,"Resources/Images/Arcade/Powerup2/powerup00%.2d.png",i+1);
        powerups[i]=load_image(buffer);
    }
    for(i=0; i<6; i++)
    {
        sprintf(buffer,"Resources/Images/Arcade/%.2d.png",i+1);
        meeting[i]=load_image(buffer);
    }
    swallow[0]=load_image("Resources/Images/Arcade/swallow.png");
    swallow[1]=load_image("Resources/Images/Arcade/swallow2.png");
    focuspoint=load_image("Resources/Images/Arcade/focuspoint.png");

    glClear(GL_COLOR_BUFFER_BIT);
    draw_text(SFTransRobotics,Storylines,4.9,50,0,CENTER_X,100);
    PrintScreen(1);
    glClear(GL_COLOR_BUFFER_BIT);
    i=0;
    timer=FrameCount;
    while( (FrameCount-timer <8*FPS) && !close_button_pressed && !IsKeyPressed(3,RETURN) && !IsKeyPressed(3,ENTER))
    {
        draw_image_ex(screenimage,0,TextY,100,0,NONE,100);
        draw_image_ex(meeting[0],5,5,90,0,NONE,i);
        if(FrameCount%2==0)
        {
            i++;
        }
        TextY+=TextSpeed;
        next_frame();
    }
    i=0;
    timer=FrameCount;
    while(TextY>40 && !close_button_pressed && !IsKeyPressed(3,RETURN) && !IsKeyPressed(3,ENTER))
    {
        draw_image_ex(screenimage,0,TextY,100,0,NONE,100);
        if(i<100) draw_image_ex(meeting[imageindex],5,5,90,0,NONE,100);
        draw_image_ex(meeting[((imageindex+1)%5)+1],5,5,90,0,NONE,i);
        i+=3;

        if(FrameCount-timer >4*FPS)
        {
            timer=FrameCount;
            imageindex=((imageindex+1)%5)+1;
            i=0;
        }
        TextY+=TextSpeed;
        next_frame();
    }
    i=300;
    while(i>-150 && !close_button_pressed && !IsKeyPressed(3,RETURN) && !IsKeyPressed(3,ENTER))
    {
        draw_image_ex(screenimage,0,TextY,100,0,NONE,i-100);
        draw_image_ex(meeting[((imageindex+1)%5)+1],5,5,90,0,NONE,i);

        i-=3;
        next_frame();
    }
    i=0;
    timer=FrameCount;
    while((FrameCount-timer <3*FPS) && !close_button_pressed && !IsKeyPressed(3,RETURN) && !IsKeyPressed(3,ENTER))
    {
        draw_image_ex(swallow[0],xrand-1,yrand-1,102,0,NONE,100);
        draw_image_ex(swallow[1],xrand-1,yrand-1,102,0,NONE,i++);
        if(FrameCount%shaking==0)xrand*=-1;
        if(FrameCount%(shaking*2)==0) yrand*=-1;
        if(FrameCount%shaking==0)shaking=Max(shaking-1,3);

        next_frame();
    }
    i=0;
    while(i<34 && !close_button_pressed && !IsKeyPressed(3,RETURN) && !IsKeyPressed(3,ENTER))
    {
        draw_image_ex(swallow[0],xrand-1,yrand-1,102,0,NONE,100);
        draw_image_ex(powerups[i],xrand+10,yrand,80,0,NONE,100);
        draw_image_ex(swallow[1],xrand-1,yrand-1,102,0,NONE,100);

        if(FrameCount%7==0) i++;
        if(FrameCount%shaking==0)xrand*=-1;
        if(FrameCount%(shaking*2)==0) yrand*=-1;
        if(FrameCount%5==0)shaking=Max(shaking-1,2);

        next_frame();
    }
    while(i<39 && !close_button_pressed && !IsKeyPressed(3,RETURN) && !IsKeyPressed(3,ENTER))
    {
        draw_image_ex(swallow[0],xrand-1,yrand-1,102,0,NONE,((float)(38-i)/5.0f)*100);
        draw_image_ex(powerups[i],xrand+10,yrand,80,0,NONE,100);
        draw_image_ex(swallow[1],xrand-1,yrand-1,102,0,NONE,((float)(38-i)/5.0f)*100);

        if(FrameCount%7==0) i++;
        if(FrameCount%shaking==0)xrand*=-1;
        if(FrameCount%(shaking*2)==0) yrand*=-1;
        if(FrameCount%5==0)shaking=Max(shaking-1,1);

        next_frame();
    }
}

void CinematicWin(PLAYERNAME winner,PLAYERNAME looser)
{
    char * Playernames[]= {"Mokhtar","Haitham","Brahim","Salah","Wassim"};
    char buffer[500];
    float w,h=102,x=-10,i=0;
    IMAGE *winImage,*loseImage;

    sprintf(buffer,"Resources/Images/%s/win.png",Playernames[winner]);
    winImage=load_image(buffer);
    sprintf(buffer,"Resources/Images/%s/lose.png",Playernames[looser]);
    loseImage=load_image(buffer);

    if(looser!=HAITHAM)
    {
        w=(100/((float)loseImage->h/(float)loseImage->w))/AspectRatio;
        x=50-w/2;
    }
    if(winner==HAITHAM)
    {
        h=120;
    }
    sprintf(buffer,"You must go on without me.\nBut you can't do it alone.\nYou must take my powers in \norder to continue your\njourney... See you in\nthe real world...");
    while(!IsKeyPressed(3,ENTER) && !IsKeyPressed(3,RETURN) && i<(FPS*10))
    {
        draw_image_ex(loseImage,x,0,0,100,NONE,i-FPS);
        draw_image_ex(winImage,0,0,0,h,NONE,i-(float)FPS*2);
        draw_text(SFTransRobotics,buffer,5,80,75,CENTER,i-(float)FPS*4);
        next_frame();
        i++;
    }
    draw_image_ex(loseImage,x,0,0,100,NONE,i-FPS);
    draw_image_ex(winImage,0,0,0,h,NONE,i-(float)FPS*2);
    draw_text(SFTransRobotics,buffer,5,80,75,CENTER,i-(float)FPS*4);
    PrintScreen(1);
    for(i=100; i>=0; i-=0.8)
    {
        draw_image_ex(screenimage,0,0,100,100,NONE,i);
        next_frame();
    }
}

void CinematicVoice(PLAYERNAME player,PLAYERNAME next, LocationName nextmap)
{
    char * Playernames[]= {"Mokhtar","Haitham","Brahim","Salah","Wassim"};
    char * Locationnames[]= {"Tunisia","Egypt","Japan","Malaysia","India"};
    char * cities[]= {"Tunis","Giza","Tokyo","Kuala Lumpur","India"};
    flip f=NONE;
    char buffer[500],buffer2[500];

    IMAGE*voice[2];
    int i;

    for(i=0; i<2; i++)
    {
        sprintf(buffer,"Resources/Images/%s/voice%d.png",Playernames[player],i+1);
        voice[i]=load_image(buffer);
    }

    sprintf(buffer,"\"Good job...good job...\n"
            "I bet you are worried about\n"
            "your friend %s...\n"
            "Don't waste more time,\n"
            "head to %s,\n"
            "you'll find him\n"
            "somewhere in %s...\n"
            "I'll be watching you...\"",Playernames[next],Locationnames[nextmap],cities[nextmap]);

    sprintf(buffer2,"I should keep going.\n"
            "%s is waiting for me alone\n"
            "in another country... Better\n"
            "hurry up...",Playernames[next]);
    if(player==BRAHIM)
    {
        f=VERTICAL;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    draw_text(SFTransRobotics,buffer,5,25,10,CENTER,100);
    PrintScreen(1);
    glClear(GL_COLOR_BUFFER_BIT);
    i=0;
    while(!IsKeyPressed(3,ENTER) && !IsKeyPressed(3,RETURN) & i<(FPS*8))
    {
        draw_image_ex(screenimage,0,0,100,100,NONE,i-FPS);
        draw_image_ex(voice[0],40,15,0,85,f,i-FPS);

        next_frame();
        i++;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    draw_text(SFTransRobotics,buffer2,5,25,10,CENTER,100);
    PrintScreen(1);
    glClear(GL_COLOR_BUFFER_BIT);

    i=0;
    while(!IsKeyPressed(3,ENTER) && !IsKeyPressed(3,RETURN) & i<(FPS*8))
    {
        draw_image_ex(screenimage,0,0,100,100,NONE,i);
        draw_text(SFTransRobotics,buffer,5,25,10,CENTER,100-i);
        draw_image_ex(voice[0],40,15,0,85,f,100-i);
        draw_image_ex(voice[1],40,10,0,90,f,i);
        next_frame();
        i++;
    }
    draw_image_ex(screenimage,0,0,100,100,NONE,100);
    draw_image_ex(voice[1],40,10,0,90,f,100);
    PrintScreen(1);
    glClear(GL_COLOR_BUFFER_BIT);
    for(i=100; i>=0; i--)
    {
        draw_image_ex(screenimage,0,0,100,100,NONE,i);
        next_frame();
    }

}


int CharacterSelect()
{
    IMAGE *Background ,*Background_bar,*select,*Player1,*Player2,*haitham[8],*mokhtar[9],*brahim[8],*wassim[10],*salah[10],*maps[5],*Ready[2];
    int i,pos_player[]= {4,22,40,58,76},select1=0,select2=4,Ready_pos[]= {8,26,44,62,80}; //distance=18
    int press_buton=0,press_buton2=0,ind_turn_mokhtar=0,ind_turn_haitham=0,ind_turn_brahim=0,ind_turn_salah=0,ind_turn_wassim=0;
    flip Turn[]= {NONE,NONE,NONE,NONE,NONE};
    int selectedPers[5]= {1,0,0,0,1},brahim_turn=0,haitham_turn=0,salah_turn=0,mokhtar_turn=0,wassim_turn=0,select_map=0;
    float distance_change1=0,distance_change2=0,fade=1,fade_start=100;
    char direction[100];
    int choix1=0,choix2=0,/*map_pos[]= {6,24,42,60,78}*/distance_change_map=20;
    float w;
    char *maps_names[]= {"Tunisia,Tunis","Egypt,Giza","India,Taj Mahal","Japan,Kyoto","Malaysia,Kuala Lampur"};


    // Loading caracteres

    for (i=0; i<8; i++)
    {
        sprintf(direction,"Resources/Images/Haitham/%d.png",i);
        haitham[i]=load_image(direction);
    }
    for (i=0; i<8; i++)
    {
        sprintf(direction,"Resources/Images/Brahim/%d.png",i);
        brahim[i]=load_image(direction);
    }
    for (i=0; i<9; i++)
    {
        sprintf(direction,"Resources/Images/Mokhtar/%d.png",i);
        mokhtar[i]=load_image(direction);
    }
    for (i=0; i<10; i++)
    {
        sprintf(direction,"Resources/Images/Wassim/%d.png",i);
        wassim[i]=load_image(direction);
    }
    for (i=0; i<10; i++)
    {
        sprintf(direction,"Resources/Images/Salah/%d.png",i);
        salah[i]=load_image(direction);
    }

    for (i=0; i<5; i++)
    {
        sprintf(direction,"Resources/Images/maps/%d.png",i);
        maps[i]=load_image(direction);
    }
    Background=load_image("Resources/Images/Origin.png");
    Background_bar=load_image("Resources/Images/Origin_bar.png");
    select=load_image("Resources/Images/Select.png");
    Player1=load_image("Resources/Images/Versus/player1.png");

    while (!IsKeyPressed(3,RETURN) )
    {
        if(close_button_pressed) return;



        if (IsKeyPressed(3,ENTER) && press_buton>10)
        {
            press_buton=0;
            return select1;
        }

        if (IsKeyPressed(3,RIGHT) && press_buton>10 )
        {
            press_buton=0;
            select1 =(select1+1)%5;
            distance_change1=-18;
            selectedPers[select1]=1;
            selectedPers[(select1-1+5)%5]=0;
        }

        if (IsKeyPressed(3,LEFT) && press_buton>10 )
        {
            press_buton=0;
            select1 =(select1-1+5)%5;
            selectedPers[(select1+1)%5]=0;
            selectedPers[select1]=1;
            distance_change1=18;
        }

        //LOGIC
        distance_change1=distance_change1/1.1;
        fade_start=fade_start/1.1;
// Drawing

        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(Background_bar,0,-27,100,150,NONE,100-fade_start);
        for (i=4; i<90; i=i+18)
            draw_image_ex(select,i,17.5,19,60,NONE,100-fade_start);
        draw_image_ex(Player1,pos_player[select1]+distance_change1,8.1,19,69.5,NONE,100-fade_start);
// Draw and turn Mokhtar
        if (selectedPers[0]==0 )
        {
            w=(50.0f/((float)mokhtar[0]->h/(float)mokhtar[0]->w))/AspectRatio;
            draw_image_ex(mokhtar[0],pos_player[0]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[0],100-fade);
        }
        else
        {
            if (mokhtar_turn==0)
            {
                ind_turn_mokhtar=1;
                Turn[0]=NONE;
            }

            if (mokhtar_turn==8)
            {
                ind_turn_mokhtar=-1;
                Turn[0]=VERTICAL;
            }

            if(FrameCount%10==0)
                mokhtar_turn=(mokhtar_turn+ind_turn_mokhtar)%9;

            w=(50.0f/((float)mokhtar[mokhtar_turn]->h/(float)mokhtar[mokhtar_turn]->w))/AspectRatio;
            draw_image_ex(mokhtar[mokhtar_turn],pos_player[0]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[0],100-fade);
        }

// Draw and turn haitham
        if (selectedPers[1]==0)
        {

            w=(50.0f/((float)haitham[0]->h/(float)haitham[0]->w))/AspectRatio;
            draw_image_ex(haitham[0],pos_player[1]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[1],100-fade);
        }
        else
        {
            if (haitham_turn==0)
            {
                ind_turn_haitham=1;
                Turn[1]=NONE;
            }
            if (haitham_turn==7)
            {
                ind_turn_haitham=-1;
                Turn[1]=VERTICAL;
            }
            if(FrameCount%10==0)
                haitham_turn=(haitham_turn+ind_turn_haitham)%8;
            w=(50.0f/((float)haitham[haitham_turn]->h/(float)haitham[haitham_turn]->w))/AspectRatio;
            draw_image_ex(haitham[haitham_turn],pos_player[1]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[1],100-fade);
        }

// Draw and turn brahim

        if (selectedPers[2]==0)
        {
            w=(50.0f/((float)brahim[0]->h/(float)brahim[0]->w))/AspectRatio;

            draw_image_ex(brahim[0],pos_player[2]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[2],100-fade);
        }
        else
        {
            if (brahim_turn==0)
            {
                ind_turn_brahim=1;
                Turn[2]=NONE;
            }
            if (brahim_turn==7)
            {
                ind_turn_brahim=-1;
                Turn[2]=VERTICAL;
            }
            if(FrameCount%10==0)
                brahim_turn=(brahim_turn+ind_turn_brahim)%8;
            w=(50.0f/((float)brahim[brahim_turn]->h/(float)brahim[brahim_turn]->w))/AspectRatio;

            draw_image_ex(brahim[brahim_turn],pos_player[2]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[2],100-fade);
        }

// Draw and turn salah
        if (selectedPers[3]==0)
        {
            w=(50.0f/((float)salah[0]->h/(float)salah[0]->w))/AspectRatio;
            draw_image_ex(salah[0],pos_player[3]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[3],100-fade);
        }
        else
        {
            if (salah_turn==0)
            {
                ind_turn_salah=1;
                Turn[3]=NONE;
            }
            if (salah_turn==9)
            {
                ind_turn_salah=-1;
                Turn[3]=VERTICAL;
            }
            if(FrameCount%10==0)
                salah_turn=(salah_turn+ind_turn_salah)%10;
            w=(50.0f/((float)salah[salah_turn]->h/(float)salah[salah_turn]->w))/AspectRatio;
            draw_image_ex(salah[salah_turn],pos_player[3]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[3],100-fade);
        }
        // Draw and turn Wassim
        if (selectedPers[4]==0)
        {
            w=(50.0f/((float)wassim[0]->h/(float)wassim[0]->w))/AspectRatio;
            draw_image_ex(wassim[0],pos_player[4]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[4],100-fade);
        }
        else

        {
            if (wassim_turn==0)
            {
                ind_turn_wassim=1;
                Turn[4]=NONE;
            }
            if (wassim_turn==9)
            {
                ind_turn_wassim=-1;
                Turn[4]=VERTICAL;
            }
            if(FrameCount%10==0)
                wassim_turn=(wassim_turn+ind_turn_wassim)%10;
            w=(50.0f/((float)wassim[wassim_turn]->h/(float)wassim[wassim_turn]->w))/AspectRatio;
            draw_image_ex(wassim[wassim_turn],pos_player[4]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[4],100-fade);
        }

        press_buton++;

        next_frame();
    }

    while (fade<100)
    {
        fade=fade*1.1;
        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(Background_bar,0,-27,100,150,NONE,100-fade);
        next_frame();
    }
    while(IsKeyPressed(1,ENTER)){
        rest(1);
    }

    return -1;
}


