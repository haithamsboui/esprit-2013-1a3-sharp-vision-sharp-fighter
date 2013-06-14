#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
#include "includes.h"

int ingame;
  IMAGE **BUTTONS;
int close_button_pressed;

void close_button_handler();

void intromenu(int intro);

void mainmenu(int *choix);

void credit();

void setting ();

void versus (int intro);

void ChargerEffetNaturel(IMAGE *effet[100], char chemin[200], int nombreFrame);

void GamePlay(int Player1,int Player2,int Map);

#endif // MENUS_H_INCLUDED
