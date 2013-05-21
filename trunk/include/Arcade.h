#ifndef ARCADE_H_INCLUDED
#define ARCADE_H_INCLUDED

#include "includes.h"

typedef enum {MOKHTAR,HAITHAM,BRAHIM,SALAH,WASSIM} PLAYERNAME;

void Arcade();

void Cinematic1();

void CinematicWin(PLAYERNAME winner,PLAYERNAME looser);

void CinematicVoice(PLAYERNAME player,PLAYERNAME next, LocationName nextmap);


#endif // ARCADE_H_INCLUDED
