#include "includes.h"

int colorProgress=0;
void draw_image_evil(IMAGE *image, float x, float y, float w, float h,flip flips, float trans)
{
    trans=Percentage(trans)/100.0f;;
    if(trans==0.0f) return;
    glColor4f(1.0f,LinearFunc(0.0f,0.5f,fabs(colorProgress-100)), 0.0f, trans);
    colorProgress =(colorProgress+1)%201;
    draw_image(image,x,y,w,h,flips);
}

void draw_image_freeze(IMAGE *image, float x, float y, float w, float h,flip flips, float trans)
{
    trans=Percentage(trans)/100.0f;
    if(trans==0.0f) return;
    glColor4f(0.0f, 1.0f, 1.0f, trans);
    draw_image(image,x,y,w,h,flips);
}

void draw_image_ex(IMAGE *image, float x, float y, float w, float h,flip flips, float trans)
{
    trans=Percentage(trans)/100.0f;
    if(trans==0.0f) return;
    glColor4f(1.0f, 1.0f, 1.0f, trans);
    draw_image(image,x,y,w,h,flips);
}

void draw_image(IMAGE *image, float x, float y, float w, float h,flip flips)
{
    int hflip,vflip;


    if ((image==NULL) || (image->ID==0) || (w==0 && h==0)) return;


    if(w==0 && h!=0)
    {
        w=(h/((float)image->h/(float)image->w))/AspectRatio;
    }
    if(w!=0 && h==0)
    {
        h=(w/((float)image->w/(float)image->h))*AspectRatio;
    }


    vflip = (flips & 1)==1;
    hflip = (flips & 2)==2;

    x=x/50 -1;
    y=-(y/50 -1);
    w=w/50;
    h=h/50;

    glBindTexture(GL_TEXTURE_2D, image->ID);
    glBegin(GL_QUADS);

    glTexCoord2f(hflip, vflip);
    glVertex3f(x, y-h,0);

    glTexCoord2f(!hflip, vflip);
    glVertex3f(x+w, y-h,0);

    glTexCoord2f(!hflip, !vflip);
    glVertex3f(x+w, y,0);

    glTexCoord2f(hflip, !vflip);
    glVertex3f(x, y,0);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Counter;
void next_frame()
{
    glFlush();
    allegro_gl_flip();
    Counter=(1000.0/FPS)-(TickCount-Counter);
    if(Counter>0)
        rest(Counter);
    //we don't need to clear GL_DEPTH_BUFFER_BIT
    glClear (GL_COLOR_BUFFER_BIT);
    Counter=TickCount=0;
    FrameCount++;
}


