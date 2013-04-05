#include "includes.h"

void draw_image_ex(IMAGE *image, float x, float y, float w, float h,flip flips, float trans)
{
    if (image->ID==0) return;

    int hflip,vflip;
    vflip = (flips & 1)==1;
    hflip = (flips & 2)==2;
    trans=Percentage(trans)/100.0f;
    x=x/50 -1;
    y=-(y/50 -1);
    w=w/50;
    h=h/50;
    glColor4f(1.0f, 1.0f, 1.0f, trans);
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
int next_frame()
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
    return FrameCount;
}

