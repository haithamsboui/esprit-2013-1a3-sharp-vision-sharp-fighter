#include "includes.h"


int Music_volume=255; // 0-255
int Effect_volume=255; // 0-255

int Fullscreen=0;
int Width=800;
int Height=600;
int depth=32;

void LoadSettings(){
    Music_volume=get_config_int("sound","Music_volume",Music_volume);
    Effect_volume=get_config_int("sound","Effect_volume",Effect_volume);
    Fullscreen=get_config_int("graphics","Fullscreen",0);
    Width=get_config_int("graphics","Width",800);
    Height=get_config_int("graphics","Height",600);
    depth=get_config_int("graphics","depth",32);
}
