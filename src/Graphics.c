#include "includes.h"

void draw_image_ex(IMAGE *image, float x, float y, float w, float h,flip flips, float trans)
{
    int hflip,vflip;

    trans=Percentage(trans);
    if ((image->ID==0) || (w==0 && h==0) || trans==0.0f) return;


    if(w==0 && h!=0){
        w=(h/((float)image->h/(float)image->w))/AspectRatio;
    }
    if(w!=0 && h==0){
        h=(w/((float)image->w/(float)image->h))*AspectRatio;
    }


    vflip = (flips & 1)==1;
    hflip = (flips & 2)==2;
    trans/=100.0f;
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

