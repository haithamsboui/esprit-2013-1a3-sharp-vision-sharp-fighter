#include "includes.h"



void Arcade()
{
    //Loading of data
    Cinematic1();
}

void Cinematic1()
{
    const char Storylines[]="Once upon a time, there was a team of talented developpers called Sharp Vision.\n" \
                            "They were asked to make a video game, but like no other.\n" \
                            "They started brainstorming about the idea";
    char buffer[100];
    int i,timer;
    float TextY=100;
    IMAGE *powerups[40],*meeting[6],*swallow[2],*focuspoint;

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
    i=0;
    timer=FrameCount;
    while((FrameCount-timer <5*FPS) && !close_button_pressed && !IsKeyPressed(3,RETURN) && !IsKeyPressed(3,ENTER))
    {
        draw_text(Arista,Storylines,5,50,TextY,CENTER_X,i);
        draw_image_ex(meeting[0],5,5,90,0,NONE,i);
        if(FrameCount%2==0)
        {
            i++;
        }
        TextY-=0.05;
        next_frame();
    }
    i=0;
    timer=FrameCount;
    while(1 && !close_button_pressed && !IsKeyPressed(3,RETURN) && !IsKeyPressed(3,ENTER))
    {
        draw_text(Arista,Storylines,5,50,TextY,CENTER_X,100);
        if(i<100) draw_image_ex(meeting[0],5,5,90,0,NONE,100);
        draw_image_ex(meeting[1],5,5,90,0,NONE,i);

            i+=3;

        TextY-=0.05;
        next_frame();
    }
}

