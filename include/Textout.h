#ifndef TEXTOUT_H_INCLUDED
#define TEXTOUT_H_INCLUDED

#include "includes.h"

typedef enum {NORMAL,CENTER_X,CENTER_Y,CENTER} FONTSTYLE;
typedef enum {SharpCurve,Verdana} FONTS;

//TODO : Fix variable size according to FONTS size"
//#define FONTSCOUNT sizeof(FONTS)/sizeof(int)
const char* FontFiles[];
FTGLfont **fontlist;
FTGLfont **fontlist2;
//Load .ttf files
int install_fonts();
//draw text, using specific font,size, location and style.
void draw_text(FONTS font,const char* text,float size,float x, float y, FONTSTYLE style);
//free font memory
void uninstall_fonts();

#endif // TEXTOUT_H_INCLUDED
