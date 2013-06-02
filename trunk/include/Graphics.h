#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "includes.h"

//Flags to flip image when drawing
typedef enum {NONE=0, HORIZONTAL=1,VERTICAL=2} flip;



//Draw Image to screen
void draw_image_ex(IMAGE *image, float x, float y, float w, float h,flip flips, float trans);
//Draw Image with blue tint (freeze)
void draw_image_freeze(IMAGE *image, float x, float y, float w, float h,flip flips, float trans);
//Draw Image with evil tint
void draw_image_evil(IMAGE *image, float x, float y, float w, float h,flip flips, float trans);
//Basic draw image
void draw_image(IMAGE *image, float x, float y, float w, float h,flip flips);
//Blit buffer to screen and wait for next frame
void next_frame();
int Counter;

#endif // GRAPHICS_H_INCLUDED
