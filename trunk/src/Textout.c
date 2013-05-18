#include "includes.h"

const char *FontFiles[]= {"SharpCurve.ttf","verdana.ttf","Arista.ttf","velocity.ttf"};

FTGLfont **fontlist;
FTGLfont **fontlist2;

int install_fonts()
{
    int i,fail=0;
    char filename[255];
    fontlist=malloc(FONTSCOUNT*sizeof(FTGLfont*));
    fontlist2=malloc(FONTSCOUNT*sizeof(FTGLfont*));

    for(i=0; i<FONTSCOUNT; i++)
    {
        sprintf(filename,"Resources/Fonts/%s",FontFiles[i]);
        fontlist[i]=ftglCreatePolygonFont(filename);
        fontlist2[i]=ftglCreateOutlineFont(filename);

        fail = fail | (fontlist[i]==0 || fontlist2[i]==0 );
    }
    return fail;
}

void draw_text(FONTS font,const char* text,float size,float x, float y, FONTSTYLE style, float Transparency)
{
    float bbox[6],totalH=0;
    char *buffer=malloc(strlen(text)+1);
    char *textarray[200];
    int i,n;
    if(fontlist[font]==NULL)
        return;

    sprintf(buffer,"%s",text);
    textarray[0]=strtok(buffer,"\n");
    for(n=1; (textarray[n]=strtok(NULL,"\n"))!=NULL; n++);

    x=x/50 -1;
    y=-(y/50 -1);
    Transparency=Percentage(Transparency);
    glBindTexture(GL_TEXTURE_2D,0);
    for(i=0; i<n; i++)
    {
        glPushMatrix();
        glLoadIdentity();
        ftglSetFontFaceSize(fontlist[font],1,72);
        ftglSetFontFaceSize(fontlist2[font],1,72);

        ftglGetFontBBox(fontlist[font],textarray[i],-1,bbox);

        glScalef(size/100.0f,size/100 * AspectRatio,1.0f);
        if((style & CENTER_X) == CENTER_X)
        {
            glTranslatef(-fabs(bbox[3]-bbox[0])/2.0f,0.0f,0.0f);
        }
        if((style & CENTER_Y) == CENTER_Y)
        {
            glTranslatef(0.0f,fabs(bbox[4]-bbox[1])/2.0f,0.0f);
        }
        totalH+=bbox[4]+0.3;
        glTranslatef(bbox[0],-bbox[1]-fabs(totalH-bbox[1]),0.0f);

        glScalef(100.0f/size,100.0f/size / AspectRatio,1.0f);

        glTranslatef(x,y,0.0f);

        glScalef(size/100.0f,size/100  * AspectRatio,1.0f);


        glColor4f(1.0f,1.0f,1.0f,Transparency/100.0f);

        ftglRenderFont(fontlist[font], textarray[i], FTGL_RENDER_ALL);

        glLineWidth(size/30);
        glColor4f(0.0f,0.0f,0.0f,Transparency/100.0f);

        ftglRenderFont(fontlist2[font], textarray[i], FTGL_RENDER_ALL);

        glPopMatrix();
    }
    free(buffer);
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

