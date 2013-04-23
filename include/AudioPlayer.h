#ifndef AUDIOPLAYER_H_INCLUDED
#define AUDIOPLAYER_H_INCLUDED

#include "includes.h"

int *VoicesMusic; //List of allocated music
int *VoicesSfx;
int voice_len_music; //Number of music
int voice_len_sfx; //Number of sfx


//Load Sound .wav to memory
int AddVoice(const char *filename, int sfx);
//change volume (0-255)
void SetMusicVolume(int volume);
void SetEffectsVolume(int volume);
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
