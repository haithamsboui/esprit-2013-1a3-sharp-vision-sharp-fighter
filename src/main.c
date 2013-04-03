#include "includes.h"

int main()
{
    int i,w=1366/2, h=768/2, fullscreen=0, depth=32;
    IMAGE *img,*bg,*mokh;
    int sound1,volume;
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

    printf("\nVideo : Press ESC to skip...\n");
    PlayVideo("Resources/Videos/SharpIntro.ogv");

    fullscreen=!fullscreen; //change screen mode :D
    change_resolution(fullscreen, w, h, depth);


    DoEarth(TUNISIA,NEWYORK);

    img=load_image("Resources/Images/Arcade.png");
    bg=load_image("Resources/Images/Background.png");
    mokh=load_image("Resources/Images/mokhtar.png");

    sound1=AddVoice("Resources/Sounds/intro.wav");
    voice_set_playmode(sound1, PLAYMODE_LOOP);
    voice_start(sound1);

    printf("\nGame loop : Press Space to change volume and transparency\nPress Enter to exit...\n");


    while(!key[KEY_ENTER])
    {
        volume=voice_get_volume(sound1);
        if(key[KEY_SPACE])
        {
            if(volume==255)
            {
                voice_ramp_volume(sound1,1000,20);
            }
            else if(volume==20)
            {
                voice_ramp_volume(sound1,1000,255);
            }
        }


        draw_image_ex(bg,0,0,100,100,NONE,100);//draw background
        draw_image_ex(img,0,12,50,75,NONE,(float)volume/255.0f*100.0f);//draw arcade
        draw_image_ex(mokh,60,0,50,200,NONE,(float)volume/255.0f*100.0f);//draw mokhtar


        next_frame();
    }



    voice_stop(sound1);

    uninstall();//liberation de memoire
    return 0;
}
END_OF_MAIN()
