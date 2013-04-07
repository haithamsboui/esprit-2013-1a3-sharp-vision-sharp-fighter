#include "includes.h"

const char* FontFiles[]= {"SharpCurve.ttf","verdana.ttf"};
FTGLfont **fontlist;
FTGLfont **fontlist2;

int install_fonts()
{
    int i,n,fail=0;
    char filename[255];

    n=sizeof(FontFiles)/sizeof(const char *);
    fontlist=malloc(n*sizeof(FTGLfont*));
    fontlist2=malloc(n*sizeof(FTGLfont*));

    for(i=0; i<n; i++)
    {
        sprintf(filename,"Resources/Fonts/%s",FontFiles[i]);
        fontlist[i]=ftglCreatePolygonFont(filename);
        fontlist2[i]=ftglCreateOutlineFont(filename);

        fail = fail | (fontlist[i]==0 || fontlist2[i]==0 );
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
    ftglSetFontFaceSize(fontlist2[font],1,72);

    ftglGetFontBBox(fontlist[font],text,-1,bbox);

    glScalef(size/100.0f,size/100 * ((float)SCREEN_W/(float)SCREEN_H),1.0f);
    if((style & CENTER_X) == CENTER_X)
    {
        glTranslatef(-fabs(bbox[3]-bbox[0])/2.0f,0.0f,0.0f);
    }
    if((style & CENTER_Y) == CENTER_Y)
    {
        glTranslatef(0.0f,fabs(bbox[4]-bbox[1])/2.0f,0.0f);
    }

    glTranslatef(bbox[0],-bbox[1]-fabs(bbox[4]-bbox[1]),0.0f);

    glScalef(100.0f/size,100.0f/size / ((float)SCREEN_W/(float)SCREEN_H),1.0f);

    x=x/50 -1;
    y=-(y/50 -1);

    glTranslatef(x,y,0.0f);

    glScalef(size/100.0f,size/100  * ((float)SCREEN_W/(float)SCREEN_H),1.0f);

    glColor4f(0.0f,0.0f,0.0f,0.75f);
    ftglRenderFont(fontlist[font], text, FTGL_RENDER_ALL);

    //glLineWidth(1.5f);
    glColor3f(1.0f,1.0f,1.0f);
    ftglRenderFont(fontlist2[font], text, FTGL_RENDER_ALL);

    glPopMatrix();

}

void uninstall_fonts()
{
    int i,n;

    n=sizeof(FontFiles)/sizeof(const char *);
    for(i=0; i<n; i++)
    {
        ftglDestroyFont(fontlist[i]);
        ftglDestroyFont(fontlist2[i]);
    }
    free(fontlist);
    free(fontlist2);
}

