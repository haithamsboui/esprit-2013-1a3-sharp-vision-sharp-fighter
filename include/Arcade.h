#ifndef ARCADE_H_INCLUDED
#define ARCADE_H_INCLUDED

#include "includes.h"

typedef enum {MOKHTAR,HAITHAM,BRAHIM,SALAH,WASSIM} PLAYERNAME;

int Dramatic;

void Arcade();

void Cinematic1();

void CinematicWin(PLAYERNAME winner,PLAYERNAME looser);

void CinematicVoice(PLAYERNAME player,PLAYERNAME next, LocationName nextmap);

int CharacterSelect();

#endif // ARCADE_H_INCLUDED
