#include "includes.h"

const char * const FontFiles[]= {"SharpCurve.ttf"};
FTGLfont **fontlist;


int install_fonts()
{
    int i,n,fail=0;
    char buffer[255];

    n=sizeof(FontFiles)/sizeof(const char *);
    fontlist=malloc(n*sizeof(FTGLfont*));
    for(i=0; i<n; i++)
    {
        sprintf(buffer,"Resources/Fonts/%s",FontFiles[i]);
        fontlist[i]=ftglCreatePixmapFont(buffer); //TODO : must use polygon font.
        fail = fail | (fontlist[i]==0);
    }
    return fail;
}

void draw_text(FONTS font,const char* text,int size,float x, float y)
{
    if(fontlist[font]==NULL)
        return;
    //glPushMatrix();
    ftglSetFontFaceSize(fontlist[font],size,72);
    ftglRenderFont(fontlist[font], text, FTGL_RENDER_ALL);
    //glTranslatef(x,y,0.0f); //TRANSLATION WITH PIXMAP FONTS DO NOT WORK!!!
    //glPopMatrix();
}

void uninstall_fonts()
{
    int i,n;

    n=sizeof(FontFiles)/sizeof(const char *);
    for(i=0; i<n; i++)
    {
        ftglDestroyFont(fontlist[i]);
    }
    free(fontlist);
}




/*
  FTGLfont *font = ftglCreatePixmapFont("RemachineScript_PERSONAL_USE_ONLY.ttf");

    //If something went wrong, bail out.
    if(!font)
        printf("You are fucked");
    else
        printf("Fuck yea");

    ftglSetFontFaceSize(font,300,72);
    while(!key[KEY_ENTER]){
        ftglRenderFont(font, "Hello World!", FTGL_RENDER_ALL);
        next_frame();
    }

    readkey();
    //Destroy the font object.
    ftglDestroyFont(font);
*/
