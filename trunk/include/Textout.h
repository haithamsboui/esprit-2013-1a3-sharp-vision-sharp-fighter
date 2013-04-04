#ifndef TEXTOUT_H_INCLUDED
#define TEXTOUT_H_INCLUDED

#include "includes.h"

typedef enum {SharpCurve} FONTS;
const char * const FontFiles[sizeof(FONTS)/sizeof(int)];
FTGLfont **fontlist;


int install_fonts();

void draw_text(FONTS font,const char* text,int size,float x, float y);

void uninstall_fonts();

#endif // TEXTOUT_H_INCLUDED
