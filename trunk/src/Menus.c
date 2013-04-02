#include "includes.h"

volatile int ticks = 0;
void ticker()
{
    ticks++;
}
END_OF_FUNCTION(ticker);
const int updates_per_second = 30;

void mainmenu(int *choix)
{
    IMAGE Firstmenu[5],Background,Select,mokh;
    int Button,i,press_buton=0,Pos_cadre[3]= {-10,15,45};
    float taille_x,taille_y,scale;
    char direction[100];
    int StartTime;
    int ind_1,ind_2,ind_3;

// loading

    install_timer();
    install_int(ticker, 1);
    Button=AddVoice("./Ressources/button3.wav");
    Background=load_image("./Ressources/Background.png");
    mokh=load_image("./Ressources/mokhtar.png");
    Select=load_image("./Ressources/Select.png");
    for (i=0; i<5; i++)
    {
        sprintf (direction,"./Ressources/%d.png",i);
        Firstmenu[i]=load_image(direction);
    }
    taille_x=(((float)Firstmenu[0].w)/1366)*100;
    taille_y=(((float)Firstmenu[0].h)/1366)*100;


    // drawing
          //*choix=(*choix-1+5)%5;
            ind_1=*choix;
            ind_2=(ind_1-1+5)%5;
            ind_3=(ind_2-1+5)%5;


    // Key pushing

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

                scale=scale/1.3;
                draw_image_ex(Background,0,0,100,100,NONE,100);//draw background
                draw_image_ex(Firstmenu[ind_1],Pos_cadre[0]-scale,35,taille_x,taille_y+10,NONE,100);
                draw_image_ex(Firstmenu[ind_2],Pos_cadre[1]-scale,30,taille_x+5,taille_y+20,NONE,100);
                draw_image_ex(Firstmenu[ind_3],Pos_cadre[2]-scale,35,taille_x,taille_y+10,NONE,100);
                draw_image_ex(Select,16,32,27,40,NONE,50);
                draw_image_ex(mokh,60,0,50,200,NONE,90); // draw mokhtar
                next_frame();

press_buton++;
        }
            *choix=ind_1-1;
    }



void setting (int Voice,GFX_MODE_LIST * gfxlist)
{
    //Loading;
    IMAGE Background,cadre,sound,volume,control;
    int distance_change,Position=0,pos_cadre[]= {25,38,51},press_buton=0;


    install_timer();
    install_int(ticker, 1);
    Background=load_image("./Ressources/Setting.png");
    cadre =load_image("./Ressources/setting_cadre.png");
    sound=load_image("./Ressources/sound_bar.png");
    volume=load_image("./Ressources/sound_cursor.png");
    control=load_image("./Ressources/control.png");

    //Drawing
    while (!key[KEY_ESC])
    {
    draw_image_ex(Background,0,0,100,100,NONE,100);
    draw_image_ex(cadre,32,pos_cadre[Position],50,10,NONE,100);
    draw_image_ex(sound,50,pos_cadre[1]+3,22,2,NONE,80);
    draw_image_ex(volume,50.5+voice_get_volume(Voice)/12.75,pos_cadre[1]+2,1,4,NONE,80);
    next_frame();


        if ((key[KEY_DOWN]  && press_buton>5)  )
        {
            printf ("%d \n",abs(Position%3));


            distance_change=13;
            press_buton=0;
            Position++;
            while (distance_change!=0)
            {

                distance_change=distance_change/2;
                draw_image_ex(Background,0,0,100,100,NONE,100);
                draw_image_ex(cadre,32,pos_cadre[abs(Position%3)]+distance_change,50,10,NONE,100);
                draw_image_ex(sound,50,pos_cadre[1]+3,22,2,NONE,80);
                draw_image_ex(volume,50.5+voice_get_volume(Voice)/12.75,pos_cadre[1]+2,1,4,NONE,80);


                next_frame();
            }

        }

        if ((key[KEY_UP]  && press_buton>5)  )
        {

            printf ("%d \n",abs(Position%3));
            distance_change=13;
            press_buton=0;
            Position--;
            while (distance_change!=0)
            {

                distance_change=distance_change/2;
                draw_image_ex(Background,0,0,100,100,NONE,100);
                draw_image_ex(cadre,32,pos_cadre[abs(Position%3)]-distance_change,50,10,NONE,100);
                draw_image_ex(sound,50,pos_cadre[1]+3,22,2,NONE,80);
                draw_image_ex(volume,50.5+voice_get_volume(Voice)/12.75,pos_cadre[1]+2,1,4,NONE,80);
                next_frame();
            }

        }

        switch (abs(Position%3))
        {
        case 1 :
        {
            if ((key[KEY_RIGHT]  && press_buton>5 &&  voice_get_volume(Voice)<256 )  )
            {
                press_buton=0;
                draw_image_ex(Background,0,0,100,100,NONE,100);
                draw_image_ex(cadre,32,pos_cadre[abs(Position%3)]+distance_change,50,10,NONE,100);
                draw_image_ex(sound,50,pos_cadre[1]+3,22,2,NONE,80);
                voice_set_volume(Voice, voice_get_volume(Voice)+255/20);
                draw_image_ex(volume,50.5+voice_get_volume(Voice)/12.75,pos_cadre[1]+2,1,4,NONE,80);
                next_frame();
            }
            if ((key[KEY_LEFT]  && press_buton>5 &&  voice_get_volume(Voice)>0 )  )
            {
                press_buton=0;
                draw_image_ex(Background,0,0,100,100,NONE,100);
                draw_image_ex(cadre,32,pos_cadre[abs(Position%3)]+distance_change,50,10,NONE,100);
                draw_image_ex(sound,50,pos_cadre[1]+3,22,2,NONE,80);
                voice_set_volume(Voice, voice_get_volume(Voice)-255/20);
                draw_image_ex(volume,50.5+voice_get_volume(Voice)/12.75,pos_cadre[1]+2,1,4,NONE,80);
                next_frame();
            }

        }
        break;

        case 2 :
        {
            if (key[KEY_ENTER])
            {
                while (!key[KEY_BACKSPACE])
                {

                    draw_image_ex(control,0,0,100,100,NONE,100);
                    next_frame();
                }
            }
        }
        break;
        }


        press_buton++;

    }

}
void credit ()
{
    IMAGE logo,credit;
    int intro;
    float i=0;
    intro=AddVoice("./Ressources/Credit.wav");
    credit=load_image("./Ressources/credit.png");
    logo=load_image("./Ressources/logo.png");
    voice_start(intro);
    while (!key[KEY_ESC] && i!=100)
    {printf ("**** credit %d",credit.h);
        draw_image_ex(credit,0,100-i,100,100,NONE,100);//draw background
        draw_image_ex(logo,45,190+(credit.h/1366)*100-i,20,20,NONE,100);
        i+=0.1;
        next_frame();

    }

    voice_stop(intro);
}

void versus ()
{
    IMAGE Background ,personne[2],select;
    int i,Pos_select=19,Position=0,Pers=0;
    int StartTime,press_buton=0;

    install_timer();
    install_int(ticker, 1);
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
                StartTime=ticks;

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
        StartTime=ticks-StartTime;
        StartTime=(1000/updates_per_second)-StartTime;
        if(StartTime>0)
        {
            rest(StartTime);
        }
    }
}
