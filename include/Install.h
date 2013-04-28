#ifndef INSTALL_H_INCLUDED
#define INSTALL_H_INCLUDED

#include "includes.h"

//Is Allegro Installed?
 int IsInstalled;

//Images per second
 int FPS;

//variable to count Milliseconds per image
 int TickCount;
//Contains number of frames drawn since game started
 int FrameCount;

//Ratio of SCREEN_W/SCREEN_H
 float AspectRatio;

//Called every 1 millisecond
void Ticks();

//Initialize allegro and all libs, and create window
int install();

//change graphics mode
int change_resolution(int fullscreen, int ResIndex);

//prepare OpenGL to draw in 2D mode.
//this should be called after playing a video, drawing in 3D, ect.
void SetOpenGL2D();

void uninstall();

#endif // INSTALL_H_INCLUDED
