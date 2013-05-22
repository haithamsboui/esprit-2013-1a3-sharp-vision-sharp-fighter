#include "includes.h"

void Arcade()
{
    //Loading of data
    Cinematic1();
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


