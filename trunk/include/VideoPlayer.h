#ifndef VIDEOPLAYER_H_INCLUDED
#define VIDEOPLAYER_H_INCLUDED


#include "includes.h"

//must initialize allegro, allegroGL,timer, sound and keyboard.
//Play video mpg or ogv, and stop if key pressed.
int PlayVideo(const char *filename);

//play the sound of the video without showing it.
int PlayAudio(const char *filename);

#endif // VIDEOPLAYER_H_INCLUDED
