#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "includes.h"

//Flags to flip image when drawing
typedef enum {NONE=0, HORIZONTAL=1,VERTICAL=2} flip;

//Draw Image to screen
void draw_image_ex(IMAGE *image, float x, float y, float w, float h,flip flips, float trans);
//Blit buffer to screen and wait for next frame
int next_frame();
int Counter;

#endif // GRAPHICS_H_INCLUDED
