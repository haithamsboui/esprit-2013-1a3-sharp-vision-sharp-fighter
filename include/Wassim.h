#ifndef WASSIM_H_INCLUDED
#define WASSIM_H_INCLUDED

#include "includes.h"
#define WassimImageCount 45
#define StableStartW 0
#define StablecountW 3

#define WalkStartW 9
#define WalkcountW 3

#define KickStartW 18
#define KickcountW 3

#define PunchStartW 14
#define PunchcountW 4

#define FireballStartW 30
#define FireballcountW 4

#define FreezeStartW 34
#define FreezecountW 3

#define ThunderStartW 37
#define ThundercountW 4

#define WindStartW 42
#define WindcountW 3

#define DefenceStartW 12
#define DefencecountW 2

#define CrouchStartW 6
#define CrouchcountW 2

#define JumpStartW 3
#define JumpcountW 3

#define FallStartW 21
#define FallcountW 5

#define HitStartW 21
#define HitcountW 3

#define UpStartW 27
#define UpCountW 3
IMAGE *WassimPics[WassimImageCount];

EtatPlayer etatW;

float xW,yW;
float wW,hW;

int directionW;
int PlayerW;
int IndexW;
int IndexCollissionW;
int SuperPowerW;
int FireW;
int ThunderW;
int WindW;
int FreezeW;
void Draw_Wassim(int CPU);
void LoadWassim(int player);


#endif // WASSIM_H_INCLUDED
