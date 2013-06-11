#ifndef VERSUS_H_INCLUDED
#define VERSUS_H_INCLUDED

void versus (int intro);
void ChargerEffetNaturel(IMAGE *effet[100], char chemin[200], int nombreFrame);
void GamePlay(int Player1,int Player2,int Map);
int player2;
int player1;
int Player1Health;
int Player2Health;
int Combot1;
int Combot2;
    IMAGE *Power1;
    IMAGE *Power2;
 IMAGE *ThunderEffet[50];
 IMAGE *FireEffet[50];
 IMAGE *WindEffet[50];
IMAGE *FreezeEffet[2];
int OnAttack;
#endif // VERSUS_H_INCLUDED
