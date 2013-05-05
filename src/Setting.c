#include "includes.h"


int Music_volume=255; // 0-255
int Effect_volume=255; // 0-255

int Fullscreen=0;
int Width=800;
int Height=480;
int depth=32;

GFX_MODE_LIST * Resolutions;
int ResolutionIndex=0;

int LoadSettings(){
    set_config_file("Resources/Setting.cfg");
    Music_volume=get_config_int("sound","Music_volume",Music_volume);
    Effect_volume=get_config_int("sound","Effect_volume",Effect_volume);
    Fullscreen=get_config_int("graphics","Fullscreen",Fullscreen);
    Width=get_config_int("graphics","Width",Width);
    Height=get_config_int("graphics","Height",Height);
    depth=get_config_int("graphics","depth",depth);
    ResolutionIndex=(get_config_int("graphics","ResolutionIndex",ResolutionIndex)%Resolutions->num_modes);
    return 0;
}


