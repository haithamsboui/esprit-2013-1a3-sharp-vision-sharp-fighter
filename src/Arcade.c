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

