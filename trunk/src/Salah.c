#include "includes.h"

IMAGE *SalahPics[51];

float x,y;
float w,h;
int direction;
int Player;
EtatSalah etat;

void LoadSalah(int player){
    int i;
    char path[255];
    for (i=0;i<51;i++){
        sprintf(path,"Resources/Images/Salah/GamePlay/%d.png",i);
        SalahPics[i]=load_image(path);
    }

    y=50;
    w=20;
    h=40;
    Player=player;

    switch(player){
        case 1:
            direction=1;
            x=25;
        break;
        case 2:
            direction=0;
            x=75;
        break;
    }
}


void Draw_Salah(){

}
