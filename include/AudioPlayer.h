#ifndef AUDIOPLAYER_H_INCLUDED
#define AUDIOPLAYER_H_INCLUDED

#include "includes.h"

 int *Voices; //List of allocated sounds
 int voice_len; //Number of sounds

//Load Sound .wav to memory
int AddVoice(const char *filename);
//Get Time of sound in seconds
float GetVoiceLength(int voice);
//Unload sounds from memory
void DisposeVoices();

#endif // AUDIOPLAYER_H_INCLUDED


/*playing sound with default allegro functions :
start :
voice_start(voice);
stop :
voice_stop(voice);
fade in/out volume :
voice_ramp_volume(voice,1000,255);*/
