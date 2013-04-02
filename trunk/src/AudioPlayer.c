#include "includes.h"

 int *Voices; //List of allocated sounds
 int voice_len=0; //Number of sounds

//Load Sound .wav to memory
int AddVoice(const char *filename)
{
    SAMPLE *samp;
    int v;
    samp=load_sample(filename);
    if(!samp)
        return 0;
    if((v=allocate_voice(samp))==-1){
        destroy_sample(samp);
        return 0;
    }
    voice_len++;
    Voices=(int*)realloc(Voices,voice_len*sizeof(int));
    Voices[voice_len-1]=v;
    return v;
}
//Get Time of sound in seconds
float GetVoiceLength(int voice){
    SAMPLE *samp;
    float len=0.0f;
    if((samp=voice_check(voice))!=NULL){ //Addionnal check
            len=(float)samp->len/(float)samp->freq;
    }
    return len;
}

//Unload sounds from memory
void DisposeVoices()
{
    int i;
    SAMPLE* samp;
    for(i=0; i<voice_len; i++)
    {
        if((samp=voice_check(Voices[i]))!=NULL){ //Addionnal check
            destroy_sample(samp);
        }
        deallocate_voice(Voices[i]);
    }
    free(Voices);
    Voices=NULL;
    voice_len=0;
}
