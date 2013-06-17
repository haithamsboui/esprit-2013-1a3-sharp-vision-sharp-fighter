#ifndef ARCADE_H_INCLUDED
#define ARCADE_H_INCLUDED

#include "includes.h"
int FireH;
int ThunderH;
int WindH;
int FreezeH;
int FireB;
int ThunderB;
int WindB;
int FreezeB;
int FireW;
int ThunderW;
int WindW;
int FreezeW;
int FireM;
int ThunderM;
int WindM;
int FreezeM;
int FireS;
int ThunderS;
int WindS;
int FreezeS;

typedef enum {MOKHTAR,HAITHAM,BRAHIM,SALAH,WASSIM} PLAYERNAME;

int Dramatic;

void Arcade();

void Cinematic1();

void CinematicWin(PLAYERNAME winner,PLAYERNAME looser);

void CinematicVoice(PLAYERNAME player,PLAYERNAME next, LocationName nextmap);

int CharacterSelect();
void Savegame ();
void LoadSavegame ();

#endif // ARCADE_H_INCLUDED
