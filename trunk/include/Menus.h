#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
#include "includes.h"


void mainmenu(int *choix);

void credit();

void setting (int Voice,GFX_MODE_LIST * gfxlist,int fullscreen);

void versus ();

void GamePlay(int Player1,int Player2,IMAGE* Map);

#endif // MENUS_H_INCLUDED
