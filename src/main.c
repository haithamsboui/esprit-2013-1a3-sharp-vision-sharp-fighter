#include "includes.h"


int main()
{
    int i,w=1366/1.5, h=768/1.5, fullscreen=0, depth=32;
    int intro ;
    int state=1,choix=0;
    GFX_MODE_LIST * gfxlist;

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

    intro=AddVoice("Resources/Sounds/intro.wav",0);
    PlayVideo("Resources/Videos/SharpIntro.ogv");


    voice_start(intro);
    voice_set_playmode(intro, PLAYMODE_LOOP);

    while (state)
    {
        mainmenu(&choix);

        switch (choix)
        {
        case 0 :
            break;
        case 1:
            versus(intro);

            break;
        case 2 :
            setting (intro,gfxlist,fullscreen);
            break;
        case 3 :
        {
            voice_stop(intro);
            credit();
            voice_start(intro);

        }
        break;
        case 4 :
            state=0;
            break;
        }

    }

    voice_stop(intro);
    uninstall();//liberation de memoire
    return 0;
}
END_OF_MAIN()
