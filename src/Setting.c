#include "includes.h"


int Music_volume=255; // 0-255
int Effect_volume=255; // 0-255

int Fullscreen=0;
int Width;
int Height;
int depth=32;

void LoadSettings(){
    Music_volume=get_config_int("sound","Music_volume",Music_volume);
    Effect_volume=get_config_int("sound","Effect_volume",Effect_volume);
    Fullscreen=get_config_int("graphics","Fullscreen",Fullscreen);
    Width=get_config_int("graphics","Width",Width);
    Height=get_config_int("graphics","Height",Height);
    depth=get_config_int("graphics","depth",depth);
}

GFX_MODE_LIST GetResolution()
{
  GFX_MODE_LIST * gfxlist;
  int i;
 gfxlist=get_gfx_mode_list(GFX_OPENGL_FULLSCREEN);
  /*  for(i=0; i<gfxlist->num_modes; i++)
    {
        printf("%dx%dx%d\n",gfxlist->mode[i].width,gfxlist->mode[i].height,gfxlist->mode[i].bpp);
    }
    printf("\nGraphics modes : %d\n",gfxlist->num_modes);
*/
return (* gfxlist);
}
