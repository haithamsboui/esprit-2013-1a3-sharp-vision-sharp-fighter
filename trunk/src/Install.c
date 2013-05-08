#include "includes.h"

int IsInstalled=0;
int FPS=60;
int TickCount=0;
int FrameCount=0;
float AspectRatio;

void Ticks()
{
    TickCount++;
}



int install()
{
    int screen_mode;

    if(IsInstalled)
        return 0;
    if(allegro_init())
        return 1;
    if(install_allegro_gl())
        return 1;
    set_window_title("Sharp Fighters");

    Resolutions=get_gfx_mode_list(GFX_OPENGL_FULLSCREEN);

    LoadSettings();

    if(install_keyboard())
        return 1;
    if(install_timer())
        return 1;
    if(install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL))
        return 1;

    JoyStickEnabled=(install_joystick(JOY_TYPE_AUTODETECT)==0);
    JoyStickEnabled=JoyStickEnabled && num_joysticks;

    LoadInput();

    if(install_fonts())
        printf("One or more font files were not loaded.\n");

    allegro_gl_set(AGL_COLOR_DEPTH, depth);
    allegro_gl_set(AGL_RENDERMETHOD, 1);
    allegro_gl_set(AGL_DOUBLEBUFFER, 1);
    allegro_gl_set(AGL_SUGGEST, AGL_COLOR_DEPTH | AGL_DOUBLEBUFFER | AGL_RENDERMETHOD);

    if(Fullscreen)
        screen_mode=GFX_OPENGL_FULLSCREEN;
    else
        screen_mode=GFX_OPENGL_WINDOWED;

    if (set_gfx_mode(screen_mode, Width,Height, 0, 0))
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Unable to set graphic mode\n%s\n", allegro_error);
        return 1;
    }
    SetOpenGL2D();
    screenimage=(IMAGE*)malloc(sizeof(IMAGE));
    screenimage->ID=0;
    AspectRatio=(float)SCREEN_W/(float)SCREEN_H;

    if(install_int(Ticks,1))
        return 1;
    if(install_int(ProcessKeys,25))
        return 1;

    IsInstalled=1;
    return 0;
}
int change_resolution(int fullscreen, int ResIndex)
{
    int screen_mode;
    if(!IsInstalled)
    {
        return install(fullscreen,800,480,32); //Security mesure
    }

    KillTextures();
    allegro_gl_set(AGL_COLOR_DEPTH, Resolutions->mode[ResIndex].bpp);
    if(fullscreen)
        screen_mode=GFX_OPENGL_FULLSCREEN;
    else
        screen_mode=GFX_OPENGL_WINDOWED;

    if (set_gfx_mode(screen_mode, Resolutions->mode[ResIndex].width,Resolutions->mode[ResIndex].height, 0, 0))
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Unable to set graphic mode\n%s\n", allegro_error);
        return 1;
    }

    SetOpenGL2D();
    RefreshGLTextures();
    AspectRatio=(float)SCREEN_W/(float)SCREEN_H;
    Fullscreen=fullscreen;
    Width=Resolutions->mode[ResIndex].width;
    Height=Resolutions->mode[ResIndex].height;
    depth=Resolutions->mode[ResIndex].bpp;
    ResolutionIndex=ResIndex;
    set_config_int("graphics","Fullscreen",Fullscreen);
    set_config_int("graphics","Width",Width);
    set_config_int("graphics","Height",Height);
    set_config_int("graphics","depth",depth);
    set_config_int("graphics","ResolutionIndex",ResIndex);
    flush_config_file();
    return 0;
}

void SetOpenGL2D()
{
    glDisable(GL_DEPTH_TEST);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glAlphaFunc(GL_NOTEQUAL, 0);
    glEnable(GL_ALPHA_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearColor(0.0f,0.0f,0.0f,0.0f);

    glViewport(0, 0, SCREEN_W, SCREEN_H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void uninstall()
{
    int i;
    remove_int(Ticks);
    remove_int(ProcessKeys);

    KillTextures();
    for(i=0; i<TextureCount; i++)
    {
        free(GlobalTextures[i]);
    }
    free(GlobalTextures);
    TextureCount=0;
    free(screenimage);
   // UnLoadCollisionData();
    destroy_gfx_mode_list(Resolutions);

    DisposeVoices();

    uninstall_fonts();
    IsInstalled=0; //Allegro will dispose on exit
}

