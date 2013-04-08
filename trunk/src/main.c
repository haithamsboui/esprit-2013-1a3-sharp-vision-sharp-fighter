/*TODO :
    -Conserving Textures when recreating GL context (change resolution)

*/
#include "includes.h"


int main()
{
    int i,w=1366/2, h=768/2, fullscreen=0, depth=32;
int intro ;
int state=1;
    GFX_MODE_LIST * gfxlist;
int choix=0;
int control[]={KEY_UP,KEY_DOWN,KEY_RIGHT,KEY_LEFT,KEY_A,KEY_Z,KEY_E};


        //intialization
    if(install(fullscreen,w,h,depth))
        return 1;//ERROR


    //Get possible resolutions
    gfxlist=get_gfx_mode_list(GFX_OPENGL_FULLSCREEN);
    printf("\nGraphics modes : %d\n",gfxlist->num_modes);
    for(i=0; i<gfxlist->num_modes; i++)
    {
        printf("%dx%dx%d\n",gfxlist->mode[i].width,gfxlist->mode[i].height,gfxlist->mode[i].bpp);
    }

intro=AddVoice("Resources/Sounds/Credit.wav");
PlayVideo("Resources/Videos/SharpIntro.ogv");
voice_start(intro);

readkey();
while (state)
{
   mainmenu(&choix);
    switch (choix)
    {
        case 0 :
    break;
    case 1:
    versus();
    break;
    case 2 :
    setting (intro,gfxlist);
    break;
        case 3 :
         credit();
         break;
         case 4 :
         state=0;
         break;
    }

}
printf ("END");
     voice_stop(intro);
    uninstall();//liberation de memoire
    return 0;
}
END_OF_MAIN()