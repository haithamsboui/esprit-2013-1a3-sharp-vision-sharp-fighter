#include "includes.h"


void mainmenu(int *choix)
{
    IMAGE *Firstmenu[5],*Background,*back_bar,*Select,*mokh;
    int Button,i,press_buton=0,Pos_cadre[3]= {-10,15,45},fade=0;
    float taille_x,taille_y,scale;
    char direction[100];
    int ind_1,ind_2,ind_3;
// loading
    install_timer();
    Button=AddVoice("./Ressources/button3.wav");
    Background=load_image("./Ressources/Origin.png");
    back_bar=load_image("./Ressources/Origin_bar.png");
    mokh=load_image("./Ressources/mokhtar.png");
    Select=load_image("./Ressources/Select.png");
    for (i=0; i<5; i++)
    {
        sprintf (direction,"./Ressources/%d.png",i);
        Firstmenu[i]=load_image(direction);
    }
    taille_x=(((float)Firstmenu[0]->w)/1366)*100;
    taille_y=(((float)Firstmenu[0]->h)/1366)*100;
    // drawing
    *choix=*choix+1;
    ind_1=*choix;
    ind_2=(ind_1-1+5)%5;
    ind_3=(ind_2-1+5)%5;
    while (!key[KEY_ENTER])
    {
        if (key[KEY_RIGHT] && press_buton>10)
        {
            voice_start(Button);
            scale=-25,press_buton=0;
            *choix=(*choix-1+5)%5;
            ind_1=*choix;
            ind_2=(ind_1-1+5)%5;
            ind_3=(ind_2-1+5)%5;
        }
        if (key[KEY_LEFT]&&press_buton>10)
        {
            voice_start(Button);
            scale=25,press_buton=0;
            *choix=(*choix+1)%5;
            ind_1=*choix;
            ind_2=(ind_1-1+5)%5;
            ind_3=(ind_2-1+5)%5;
        }
        scale=scale/1.1;
        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(back_bar,0,2,100,100,NONE,100);
        draw_image_ex(Firstmenu[ind_1],Pos_cadre[0]-scale,35,taille_x,taille_y+10,NONE,100);
        draw_image_ex(Firstmenu[ind_2],Pos_cadre[1]-scale,30,taille_x+5,taille_y+20,NONE,100);
        draw_image_ex(Firstmenu[ind_3],Pos_cadre[2]-scale,35,taille_x,taille_y+10,NONE,100);
        draw_image_ex(Select,16,32,27,40,NONE,50);
        draw_image_ex(mokh,60,0,50,200,NONE,100); // draw mokhtar
        next_frame();
        press_buton++;
    }
    *choix=ind_2;
    switch (*choix)
    {

    case 2 :
    {
        while(fade<50)
        {
            rest(10);
            fade++;
            draw_image_ex(Background,0,0,100,100,NONE,100);
            draw_image_ex(back_bar,0,2,100,100,NONE,100);
            draw_image_ex(Firstmenu[ind_1],Pos_cadre[0]-scale-fade,35,taille_x,taille_y+10,NONE,100-2*fade);
            draw_image_ex(Firstmenu[ind_2],Pos_cadre[1]-scale-fade,30,taille_x+5,taille_y+20,NONE,100-2*fade);
            draw_image_ex(Firstmenu[ind_3],Pos_cadre[2]-scale-fade,35,taille_x,taille_y+10,NONE,100-2*fade);
            draw_image_ex(Select,16,32,27,40,NONE,50-fade);
            draw_image_ex(mokh,60,0,50,200,NONE,100-2*fade); // draw mokhtar
            next_frame();
        }

    }
    break;


    }
}

void setting (int Voice,GFX_MODE_LIST * gfxlist)
{
    IMAGE *Background,*back_cadre,*icon[3],*select;
    float distance_change=100,entre=0,fade=0;
    int ind1=0,ind2=1,ind3=2,pos_x[]= {5,35,65},button_press=0,trans,second_menu=0;
    //Loading;
    install_timer();

    Background=load_image("./Ressources/Origin.png");
    back_cadre=load_image("./Ressources/Origin_bar.png");
    icon[0]=load_image("./Ressources/graphics.png");
    icon[1]=load_image("./Ressources/sound.png");
    icon[2]=load_image("./Ressources/controll.png");
    select=load_image("./Ressources/Select.png");
    //Drawing
    while (distance_change>0.1)
    {
        distance_change=distance_change/1.1;
        trans=100-distance_change;
        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(back_cadre,0,2,100,100,NONE,100);
        draw_image_ex(select,36,30,27,40,NONE,trans);
        draw_image_ex(icon[0],distance_change+pos_x[0],30 ,30,40,NONE,100);
        draw_image_ex(icon[1],distance_change+pos_x[1],30 ,30,40,NONE,100);
        draw_image_ex(icon[2],distance_change+pos_x[2],30 ,30,40,NONE,100);
        next_frame();
    }

    while (!key[KEY_ESC])
    {

        if (key[KEY_RIGHT] && button_press>10 && second_menu==0)
        {
            button_press=0;
            distance_change=30;
            ind1=(ind1+1)%3;
            ind2=(ind2+1)%3;
            ind3=(ind3+1)%3;
               entre=0;
               fade=0;
        }
        if (key[KEY_LEFT] && button_press>10 && second_menu==0)
        {
            button_press=0;
            distance_change=-30;
            ind1=(ind1-1+3)%3;
            ind2=(ind2-1+3)%3;
            ind3=(ind3-1+3)%3;
entre=0;
fade=0;
        }
        if (key[KEY_ENTER] && button_press>10 && second_menu==0)

        {
            distance_change=0;
            entre=5;
            button_press=0;
            second_menu=1;
       fade=0;
        }
        if (key[KEY_BACKSPACE] && button_press>10 && second_menu==1)
        {
            distance_change=0;
            entre=0;
            button_press=0;
            second_menu=0;
        fade=5;
        }

button_press++;
        distance_change=distance_change/1.1;
        if(entre<20 )
            entre=entre*1.05;
        if( fade>0 )
            fade=fade/1.1;

        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(back_cadre,0,2,100,100,NONE,100);
        draw_image_ex(select,pos_x[0]+31-entre/5,30-entre/3,27+entre/2,40+1.9*entre,NONE,100-3*distance_change);
        draw_image_ex(icon[ind1],distance_change+pos_x[0],30 ,30,40,NONE,100);
        draw_image_ex(icon[ind2],distance_change+pos_x[1]+entre/4+fade/4,30-1.5*entre-1.5*fade ,30-entre/2-fade/2,40-entre/2-fade/2,NONE,100);
        draw_image_ex(icon[ind3],distance_change+pos_x[2],30 ,30,40,NONE,100);
        next_frame();

    }


}
void credit ()
{
    IMAGE *credit;
    int intro;
    float i=0;
    intro=AddVoice("./Ressources/Credit.wav");
    credit=load_image("./Ressources/credit.png");
    voice_start(intro);
    while (!key[KEY_ESC] && i!=100)
    {
        draw_image_ex(credit,0,100-i,100,100,NONE,100);//draw background
        i+=0.1;
        next_frame();

    }
    voice_stop(intro);
}
// EN Cours ... avec l'arcade mode
void versus ()
{
    IMAGE *Background ,*personne[2],*select;
    int i,Pos_select=19,Position=0,Pers=0;
    int press_buton=0;

    Background=load_image("./Ressources/Versus.png");
    personne[0]=load_image("./Ressources/mokhtar.png");
    personne[1]=load_image("./Ressources/haitham.png");

    select=load_image("./Ressources/Select.png");
    draw_image_ex(Background,0,0,100,100,NONE,100);//draw background
    draw_image_ex(personne[0],60,0,50,200,NONE,100); // draw mokhtar
    draw_image_ex(select,34,Pos_select,9,11,NONE,100);
    next_frame();

    while (!key[KEY_ESC])
    {


        if ((key[KEY_DOWN] && press_buton>5) && Position <4 && Pers<5)
        {
            press_buton=0;
            Position++;
            for (i=0; i<101; i+=5)
            {
                draw_image_ex(Background,0,0,100,100,NONE,100);//draw background
                draw_image_ex(personne[Pers],60,0,50,200,NONE,100-i); // draw mokhtar
                draw_image_ex(select,34,Pos_select,10,12,NONE,100);
                next_frame();
            }
            Pos_select=Pos_select+12;
            Pers++;
            for (i=0; i<101; i+=5)
            {
                draw_image_ex(Background,0,0,100,100,NONE,100);//draw background
                draw_image_ex(personne[Pers],60,0,50,200,NONE,i); // draw mokhtar
                draw_image_ex(select,34,Pos_select,10,12,NONE,100);
                next_frame();
            }

        }
        if ((key[KEY_UP] && press_buton>5) && Position >0 && Pers>-1)
        {
            press_buton=0;
            Position--;
            for (i=0; i<101; i+=5)
            {
                draw_image_ex(Background,0,0,100,100,NONE,100);//draw background
                draw_image_ex(personne[Pers],60,0,50,200,NONE,100-i); // draw mokhtar
                draw_image_ex(select,34,Pos_select,10,12,NONE,100);
                next_frame();
            }
            Pos_select=Pos_select-12;
            Pers--;
            for (i=0; i<101; i+=5)
            {
                draw_image_ex(Background,0,0,100,100,NONE,100);//draw background
                draw_image_ex(personne[Pers],60,0,50,200,NONE,i); // draw mokhtar
                draw_image_ex(select,34,Pos_select,10,12,NONE,100);
                next_frame();
            }

        }
        press_buton++;

    }
}

