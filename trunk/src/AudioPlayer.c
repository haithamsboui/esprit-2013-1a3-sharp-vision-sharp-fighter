#include "includes.h"

int *VoicesMusic; //List of allocated music
int *VoicesSfx;
int voice_len_music=0; //Number of music
int voice_len_sfx=0; //Number of sfx

//Load Sound .wav to memory
int AddVoice(const char *filename, int sfx)
{
    SAMPLE *samp;
    int v;
    samp=load_sample(filename);
    if(!samp)
        return 0;
    if((v=allocate_voice(samp))==-1)
    {
        destroy_sample(samp);
        return 0;
    }
    if(sfx)
    {
        voice_len_sfx++;
        VoicesSfx=(int*)realloc(VoicesSfx,voice_len_sfx*sizeof(int));
        VoicesSfx[voice_len_sfx-1]=v;
        voice_set_volume(v,Effect_volume);
    }
    else
    {
        voice_len_music++;
        VoicesMusic=(int*)realloc(VoicesMusic,voice_len_music*sizeof(int));
        VoicesMusic[voice_len_music-1]=v;
        voice_set_volume(v,Music_volume);
    }

    return v;
}

void SetMusicVolume(int volume)
{
    int i;
    for(i=0; i<voice_len_music; i++)
    {
        voice_set_volume(VoicesMusic[i], Music_volume);
    }
}

void SetEffectsVolume(int volume)
{
    int i;
    for(i=0; i<voice_len_sfx; i++)
    {
        voice_set_volume(VoicesSfx[i], Effect_volume);
    }
}

//Get Time of sound in seconds
float GetVoiceLength(int voice)
{
    SAMPLE *samp;
    float len=0.0f;
    if((samp=voice_check(voice))!=NULL)  //Addionnal check
    {
        len=(float)samp->len/(float)samp->freq;
    }
    return len;
}

//Unload sounds from memory
void DisposeVoices()
{
    int i;
    SAMPLE* samp;
    for(i=0; i<voice_len_music; i++)
    {
        if((samp=voice_check(VoicesMusic[i]))!=NULL)  //Addionnal check
        {
            destroy_sample(samp);
        }
        deallocate_voice(VoicesMusic[i]);
    }
    for(i=0; i<voice_len_sfx; i++)
    {
        if((samp=voice_check(VoicesSfx[i]))!=NULL)  //Addionnal check
        {
            destroy_sample(samp);
        }
        deallocate_voice(VoicesSfx[i]);
    }
    free(VoicesMusic);
    VoicesMusic=NULL;
    voice_len_music=0;
    free(VoicesSfx);
    VoicesSfx=NULL;
    voice_len_sfx=0;
}
