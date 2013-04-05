#include "includes.h"

const char * const FontFiles[]= {"SharpCurve.ttf"};
FTGLfont **fontlist;


int install_fonts()
{
    int i,n,fail=0;
    char filename[255];

    n=sizeof(FontFiles)/sizeof(const char *);
    fontlist=malloc(n*sizeof(FTGLfont*));
    for(i=0; i<n; i++)
    {
        sprintf(filename,"Resources/Fonts/%s",FontFiles[i]);
        fontlist[i]=ftglCreateOutlineFont(filename); //TODO : must use textured font.
        fail = fail | (fontlist[i]==0);
    }
    return fail;
}

void draw_text(FONTS font,const char* text,float size,float x, float y, FONTSTYLE style)
{
    float bbox[6];
    if(fontlist[font]==NULL)
        return;
    glPushMatrix();

    ftglSetFontFaceSize(fontlist[font],1,72);

    ftglGetFontBBox(fontlist[font],text,-1,bbox);

    glScalef(size/100.0f,size/100,1.0f);
    if((style & CENTER_X) == CENTER_X)
    {
        glTranslatef(-fabs(bbox[3]-bbox[0])/2.0f,0.0f,0.0f);
    }
    if((style & CENTER_Y) == CENTER_Y)
    {
        glTranslatef(0.0f,fabs(bbox[4]-bbox[1])/2.0f,0.0f);
    }

    glTranslatef(bbox[0],-bbox[1]-fabs(bbox[4]-bbox[1]),0.0f);

    glScalef(100.0f/size,100.0f/size,1.0f);

    x=x/50 -1;
    y=-(y/50 -1);

    glTranslatef(x,y,0.0f);

    glScalef(size/100.0f,size/100,1.0f);

    ftglRenderFont(fontlist[font], text, FTGL_RENDER_ALL);

    glPopMatrix();

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
