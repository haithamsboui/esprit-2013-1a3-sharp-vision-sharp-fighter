#include "includes.h"


void mainmenu(int *choix)
{
    IMAGE *Firstmenu[5],*Background,*back_bar,*Select,*mokh;
    int Button,i,press_buton=0,Pos_cadre[4]= {-10,15,45,70};
    float taille_x,taille_y,scale,fade=1,back_fade,fade_start=100;
    char direction[100];
    int ind_1,ind_2,ind_3,ind_4;
// loading
    install_timer();
    Button=AddVoice("Resources/Sounds/button3.wav");
    Background=load_image("Resources/Images/Origin.png");
    back_bar=load_image("Resources/Images/Origin_bar.png");
    mokh=load_image("Resources/Images/mokhtar.png");
    Select=load_image("Resources/Images/Select.png");
    for (i=0; i<5; i++)
    {
        sprintf (direction,"Resources/Images/%d.png",i);
        Firstmenu[i]=load_image(direction);
    }
    taille_x=(((float)Firstmenu[0]->w)/1366)*100;
    taille_y=(((float)Firstmenu[0]->h)/1366)*100;
    // drawing
    *choix=*choix+1;
    ind_1=*choix;
    ind_2=(ind_1-1+5)%5;
    ind_3=(ind_2-1+5)%5;
    ind_4=(ind_3-1+5)%5;
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
            ind_4=(ind_3-1+5)%5;
        }
        if (key[KEY_LEFT]&&press_buton>10)
        {
            voice_start(Button);
            scale=25,press_buton=0;
            *choix=(*choix+1)%5;
            ind_1=*choix;
            ind_2=(ind_1-1+5)%5;
            ind_3=(ind_2-1+5)%5;
            ind_4=(ind_3-1+5)%5;
        }
        scale=scale/1.1;
        fade_start=fade_start/1.1;
        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(back_bar,0,2,100,100,NONE,100-fade_start);
        draw_image_ex(Firstmenu[ind_1],Pos_cadre[0]-scale,35,taille_x,taille_y+10,NONE,100-fade_start);
        draw_image_ex(Firstmenu[ind_2],Pos_cadre[1]-scale,30,taille_x+5,taille_y+20,NONE,100-fade_start);
        draw_image_ex(Firstmenu[ind_3],Pos_cadre[2]-scale,35,taille_x,taille_y+10,NONE,100-fade_start);
        draw_image_ex(Firstmenu[ind_4],Pos_cadre[3]-scale,35,taille_x,taille_y+10,NONE,100-fade_start);

        draw_image_ex(Select,16,32,27,40,NONE,100-fade_start);
        draw_image_ex(mokh,60,0,50,200,NONE,100-fade_start); // draw mokhtar
        next_frame();
        press_buton++;
    }
    *choix=ind_2;


    while(fade<100)
    {
        fade=fade*1.1;
        if(ind_2==3 || ind_2==4)
            back_fade=100-fade;
        else
            back_fade=100 ;
        draw_image_ex(Background,0,0,100,100,NONE,back_fade);
        draw_image_ex(back_bar,0,2,100,100,NONE,100-fade);
        draw_image_ex(Firstmenu[ind_1],Pos_cadre[0],35,taille_x,taille_y+10,NONE,100-fade);
        draw_image_ex(Firstmenu[ind_2],Pos_cadre[1],30,taille_x+5,taille_y+20,NONE,100-fade);
        draw_image_ex(Firstmenu[ind_3],Pos_cadre[2],35,taille_x,taille_y+10,NONE,100-fade);
        draw_image_ex(Select,16,32,27,40,NONE,100-fade);
        draw_image_ex(mokh,60,0,50,200,NONE,100-fade); // draw mokhtar

        next_frame();
    }

}

void setting (int Voice,GFX_MODE_LIST * gfxlist)
{
    IMAGE *Volumes[2],*Background,*back_cadre,*icon[3],*select,*volume_bar,*volume_point;
    float distance_change=100,entre=0,fade=1,volume_fade=100;
    int ind1=0,ind2=1,ind3=2,pos_x[]= {5,35,65},button_press=0,trans,second_menu=0,Nb_point_volume_music;
    int volume=voice_get_volume(Voice),i,point_pos=0;
    //Loading;
    install_timer();
    install_fonts();
    Background=load_image("Resources/Images/Origin.png");
    back_cadre=load_image("Resources/Images/Origin_bar.png");
    icon[0]=load_image("Resources/Images/graphics.png");
    icon[1]=load_image("Resources/Images/sound.png");
    icon[2]=load_image("Resources/Images/controll.png");
    select=load_image("Resources/Images/Select.png");
    Volumes[0]=load_image("Resources/Images/Volume_bar.png");
    Volumes[1]=load_image("Resources/Images/Volume_bar1.png");
    volume_bar=load_image("Resources/Images/Volume_bar.png");
    volume_point=load_image("Resources/Images/sound_point.png");
    Nb_point_volume_music=voice_get_volume(Voice)/19;
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

    while (!key[KEY_ESC] || second_menu==1)
    {
        if (second_menu==0)
        {
            if (key[KEY_RIGHT] && button_press>10 )
            {
                button_press=0;
                distance_change=30;
                ind1=(ind1+1)%3;
                ind2=(ind2+1)%3;
                ind3=(ind3+1)%3;
                entre=0;
                fade=0;
            }
            if (key[KEY_LEFT] && button_press>10)
            {
                button_press=0;
                distance_change=-30;
                ind1=(ind1-1+3)%3;
                ind2=(ind2-1+3)%3;
                ind3=(ind3-1+3)%3;
                entre=0;
                fade=0;
            }
            if (key[KEY_ENTER] && button_press>10 )
            {
                distance_change=0;
                entre=5;
                button_press=0;
                second_menu=1;
                fade=0;
            }
        }
        if (second_menu==1)
        {
            if (key[KEY_BACKSPACE] && button_press>10 )
            {
                distance_change=0;
                entre=0;
                button_press=0;
                second_menu=0;
                fade=5;
                volume_fade=100;
            }
            switch(ind2)
            {
            case 1 :
            {

                if (key[KEY_LEFT] && voice_get_volume(Voice)>0 )
                {
                    volume--;
                    voice_set_volume(Voice,volume);
                    Nb_point_volume_music=voice_get_volume(Voice)/19;
                }
                if (key[KEY_RIGHT]  && voice_get_volume(Voice)<255)
                {
                    volume++;
                    voice_set_volume(Voice,volume);
                    Nb_point_volume_music=voice_get_volume(Voice)/19;
                }
            }
            break;
            }
        }
        button_press++;
        distance_change=distance_change/1.1;
        volume_fade=volume_fade/1.02;
        printf ("%f\n",volume_fade);
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
        if (second_menu==1 && ind2==1)
        {
            draw_image_ex(Volumes[0],33.5,39.6,35,25-volume_fade,NONE,100-volume_fade);
            draw_image_ex(Volumes[1],33.5,65.6,35,25-volume_fade,NONE,100-volume_fade);

            for (i=0; i<Nb_point_volume_music; i++)
                draw_image_ex(volume_point,41.3+i*1.5,54.3,1.5,3-volume_fade/7,NONE,100-volume_fade);
        }
        next_frame();
    }
    fade=1;
    while (fade<100)
    {
        fade=fade*1.1;
        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(back_cadre,0,2,100,100,NONE,100-fade);
        draw_image_ex(select,pos_x[0]+31-entre/5,30-entre/3,27+entre/2,40+1.9*entre,NONE,100-fade);
        draw_image_ex(icon[ind1],distance_change+pos_x[0],30 ,30,40,NONE,100-fade);
        draw_image_ex(icon[ind2],distance_change+pos_x[1],30 ,30,40,NONE,100-fade);
        draw_image_ex(icon[ind3],distance_change+pos_x[2],30 ,30,40,NONE,100-fade);
        next_frame();
    }
}
void credit ()
{
    IMAGE *credit;
    int intro;
    float i=0;
    intro=AddVoice("Resources/Sounds/Credit.wav");
    credit=load_image("Resources/Images/credit.png");
    voice_start(intro);
    while (!key[KEY_ESC] && i!=100)
    {
        draw_image_ex(credit,0,100-i,100,100,NONE,100);//draw background
        i+=0.1;
        next_frame();
    }
    voice_stop(intro);
}
void versus ()
{
    IMAGE *Background ,*Background_bar,*personne[5],*select,*Player1,*Player2;
    int i,Pos_select=19,Position=0,Pers=0,Pos_player1=4,pos_player2=76;//distance=18
    int press_buton=0,press_buton2=0;
    float distance_change1=0,distance_change2=0,fade=1,fade_start=100;
    Background=load_image("Resources/Images/Origin.png");
    Background_bar=load_image("Resources/Images/Origin_bar.png");
    personne[0]=load_image("Resources/Images/mokhtar.png");
    personne[1]=load_image("Resources/Images/haitham.png");
    select=load_image("Resources/Images/Select.png");
    Player1=load_image("Resources/Images/player1.png");
    Player2=load_image("Resources/Images/player2.png");


    while (!key[KEY_ESC])
    {

        if (key[KEY_RIGHT] && press_buton>10)
        {
            press_buton=0;
            Pos_player1 =(Pos_player1+18)%90;
            distance_change1=-18;

        }

        if (key[KEY_LEFT] && press_buton>10)
        {
            press_buton=0;
            Pos_player1 =(Pos_player1-18+90)%90;
            distance_change1=18;

        }
        if (key[KEY_D] && press_buton2>10)
        {
            press_buton2=0;
            pos_player2 =(pos_player2+18)%90;
            distance_change2=-18;

        }

        if (key[KEY_Q] && press_buton2>10)
        {
            press_buton2=0;
            pos_player2 =(pos_player2-18+90)%90;
            distance_change2=18;

        }
        distance_change2=distance_change2/1.1;
        distance_change1=distance_change1/1.1;
        fade_start=fade_start/1.1;
        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(Background_bar,0,-27,100,150,NONE,100-fade_start);
        for (i=4; i<90; i=i+18)
            draw_image_ex(select,i,17.5,19,60,NONE,100-fade_start);
        draw_image_ex(personne[0],6,21,15,50,NONE,100-fade_start);
        draw_image_ex(personne[1],24,21,15,50,NONE,100-fade_start);
        draw_image_ex(Player1,Pos_player1+distance_change1,17.5,19,60,NONE,100-fade_start);
        draw_image_ex(Player2,pos_player2+distance_change2,17.5,19,60,NONE,100-fade_start);
        next_frame();
        press_buton++;
        press_buton2++;
    }

    while (fade<100)
    {
        fade=fade*1.1;
        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(Background_bar,0,-27,100,150,NONE,100-fade);
        for (i=4; i<90; i=i+18)
            draw_image_ex(select,i,17.5,19,60,NONE,100-fade);
        draw_image_ex(personne[0],6,21,15,50,NONE,100-fade);
        draw_image_ex(personne[1],24,21,15,50,NONE,100-fade);
        draw_image_ex(Player1,Pos_player1+distance_change1,17.5,19,60,NONE,100-fade);
        draw_image_ex(Player2,pos_player2+distance_change2,17.5,19,60,NONE,100-fade);
        next_frame();
    }
}

