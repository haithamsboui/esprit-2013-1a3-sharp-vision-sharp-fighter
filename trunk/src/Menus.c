#include "includes.h"


void mainmenu(int *choix)
{
    IMAGE *Firstmenu[5],*Background,*back_bar,*Select,*Pers_main[5];
    int Button,i,press_buton=0,Pos_cadre[4]= {-10,15,45,70},select_pers=0;
    float taille_x,taille_y,scale,fade=1,back_fade,fade_start=100;
    char direction[100];
    int ind_1,ind_2,ind_3,ind_4;
// loading
    install_timer();
    Button=AddVoice("Resources/Sounds/button3.wav",1);
    Background=load_image("Resources/Images/Origin.png");
    back_bar=load_image("Resources/Images/Origin_bar.png");
    Select=load_image("Resources/Images/Select.png");
    for (i=0; i<5; i++)
    {
        sprintf (direction,"Resources/Images/%d.png",i);
        Firstmenu[i]=load_image(direction);
    }

    for (i=0; i<5; i++)
    {
        sprintf (direction,"Resources/Images/main menu/%d.png",i);
        Pers_main[i]=load_image(direction);
    }
    taille_x=(((float)Firstmenu[0]->w)/1366)*100;
    taille_y=(((float)Firstmenu[0]->h)/1366)*100;
    // drawing
    *choix=*choix+1;
    ind_1=*choix;
    ind_2=(ind_1-1+5)%5;
    ind_3=(ind_2-1+5)%5;
    ind_4=(ind_3-1+5)%5;
    while (!IsKeyPressed(3,ENTER))
    {
        if (IsKeyPressed(3,RIGHT) && press_buton>10)
        {
            voice_start(Button);
            scale=-25,press_buton=0;
            *choix=(*choix-1+5)%5;
            ind_1=*choix;
            ind_2=(ind_1-1+5)%5;
            ind_3=(ind_2-1+5)%5;
            ind_4=(ind_3-1+5)%5;
            select_pers=(select_pers+1)%5;
        }
        if (IsKeyPressed(3,LEFT) && press_buton>10)
        {
            voice_start(Button);
            scale=25,press_buton=0;
            *choix=(*choix+1)%5;
            ind_1=*choix;
            ind_2=(ind_1-1+5)%5;
            ind_3=(ind_2-1+5)%5;
            ind_4=(ind_3-1+5)%5;
                        select_pers=(select_pers-1+5)%5;
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
        draw_image_ex(Pers_main[select_pers],60,0,50,200,NONE,100-fade_start-abs(2*scale)); // draw mokhtar
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
        draw_image_ex(Pers_main[select_pers],60,0,50,200,NONE,100-fade ); // draw mokhtar

        next_frame();
    }

}

void setting (GFX_MODE_LIST * gfxlist,int fullscreen)
{
    IMAGE *Volumes[2],*Background,*back_cadre,*icon[3],*select,*volume_bar,*volume_point,*display[2],*display_cadre;
    float distance_change=100,entre=0,fade=1,volume_fade=100,display_fade=100;
    int ind1=0,ind2=1,ind3=2,pos_x[]= {5,35,65},button_press=0,trans,second_menu=0,Nb_point_volume_music,w=1366/2, h=768/2,depth=32;
    int i,point_pos=0,display_ind=0,cadre_display_pos;
    //Loading;

    display[0]=load_image("Resources/Images/Fullscreen.png");
    display[1]=load_image("Resources/Images/Windowed.png");
    Background=load_image("Resources/Images/Origin.png");
    back_cadre=load_image("Resources/Images/Origin_bar.png");
    display_cadre=load_image("Resources/Images/display.png");
    icon[0]=load_image("Resources/Images/graphics.png");
    icon[1]=load_image("Resources/Images/sound.png");
    icon[2]=load_image("Resources/Images/controll.png");
    select=load_image("Resources/Images/Select.png");
    Volumes[0]=load_image("Resources/Images/Volume_bar.png");
    Volumes[1]=load_image("Resources/Images/Volume_bar1.png");
    volume_bar=load_image("Resources/Images/Volume_bar.png");
    volume_point=load_image("Resources/Images/sound_point.png");
    Nb_point_volume_music=Music_volume/19;
    if (fullscreen==1)
        cadre_display_pos=36.6;
    else
        cadre_display_pos=69.6;
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

    while (!IsKeyPressed(3,RETURN) || second_menu==1)
    {
        if (second_menu==0)
        {
            if (IsKeyPressed(3,RIGHT) && button_press>10 )
            {
                button_press=0;
                distance_change=30;
                ind1=(ind1+1)%3;
                ind2=(ind2+1)%3;
                ind3=(ind3+1)%3;
                entre=0;
                fade=0;
            }
            if (IsKeyPressed(3,LEFT) && button_press>10)
            {
                button_press=0;
                distance_change=-30;
                ind1=(ind1-1+3)%3;
                ind2=(ind2-1+3)%3;
                ind3=(ind3-1+3)%3;
                entre=0;
                fade=0;
            }
            if (IsKeyPressed(3,ENTER) && button_press>10 )
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
            if (IsKeyPressed(3,RETURN) && button_press>10 )
            {
                distance_change=0;
                entre=0;
                button_press=0;
                second_menu=0;
                fade=5;
                volume_fade=100;
            }
            while(IsKeyPressed(3,RETURN))
            {
                rest(1);
            }
            switch(ind2)
            {
            case 0 :
            {
                if (IsKeyPressed(3,DOWN) && button_press>10)
                {
                    button_press=0;
                    display_ind=1;
                    cadre_display_pos=69.6;
                    if (fullscreen==1  )
                    {
                        fullscreen=0;
                        change_resolution(fullscreen,w,h,depth);
                    }
                }
                if(IsKeyPressed(3,UP) && button_press>10)
                {
                    button_press=0;
                    display_ind=0;
                    cadre_display_pos=39.6;

                    if ( fullscreen==0)
                    {
                        fullscreen=1;
                        change_resolution(fullscreen,w,h,depth);
                    }
                }
            }
            break;
            case 1 :
            {

                if (IsKeyPressed(3,LEFT) && Music_volume>0 )
                {
                    Music_volume-=5;
                    SetMusicVolume(Music_volume);
                    Nb_point_volume_music=Music_volume/19;
                }
                if (IsKeyPressed(3,RIGHT) && Music_volume<255)
                {
                    Music_volume+=5;
                    SetMusicVolume(Music_volume);
                    Nb_point_volume_music=Music_volume/19;
                }
            }
            break;
            }
        }
        button_press++;
        distance_change=distance_change/1.1;
        volume_fade=volume_fade/1.02;
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
            {
                draw_image_ex(volume_point,41.3+i*1.5,54.3,1.5,3-volume_fade/4,NONE,100-volume_fade);
                draw_image_ex(volume_point,41.3+i*1.5,80.3,1.5,3-volume_fade/4,NONE,100-volume_fade);

            }
        }

        if (second_menu==1 && ind2==0)
        {
            draw_image_ex(display[0],33.5,38.6,35,25-volume_fade,NONE,100-volume_fade);
            draw_image_ex(display[1],33.5,68.6,35,25-volume_fade,NONE,100-volume_fade);
            draw_image_ex(display_cadre,33.5,cadre_display_pos,35,25-volume_fade,NONE,100-volume_fade);
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
    intro=AddVoice("Resources/Sounds/Credit.wav",0);
    credit=load_image("Resources/Images/credit.png");
    voice_start(intro);
    while (!IsKeyPressed(3,RETURN) && i!=100)
    {
        draw_image_ex(credit,0,100-i,100,100,NONE,100);//draw background
        i+=0.1;
        next_frame();
    }
    voice_stop(intro);
}

void versus (int intro)
{
    IMAGE *Background ,*Background_bar,*select,*Player1,*Player2,*haitham[7],*mokhtar[7],*brahim[7],*wassim[6],*salah[4],*maps[5];
    int i,pos_player[]= {4,22,40,58,76},select1=0,select2=4; //distance=18
    int press_buton=0,press_buton2=0,ind_turn_mokhtar=0,ind_turn_haitham=0,ind_turn_brahim=0,ind_turn_salah=0,ind_turn_wassim=0;
    flip Turn[]= {NONE,NONE,NONE,NONE,NONE};
    int selectedPers[5]= {1,0,0,0,1},brahim_turn=0,haitham_turn=0,salah_turn=0,mokhtar_turn=0,wassim_turn=0,select_map=0;
    float distance_change1=0,distance_change2=0,fade=1,fade_start=100;
    char direction[100];
    int choix1=0,choix2=0,select_ind=0,select_pos[]= {4,22,22+18,22+18*2,22+18*3},/*map_pos[]= {6,24,42,60,78}*/distance_change_map=20;
    float ratioo,w;
    // Loading caracteres
    ratioo=(float)SCREEN_W/((float)SCREEN_H);
    for (i=0; i<7; i++)
    {
        sprintf(direction,"Resources/Images/Haitham/%d copy.png",i);
        haitham[i]=load_image(direction);
        sprintf(direction,"Resources/Images/Brahim/%d copy.png",i);
        brahim[i]=load_image(direction);
        sprintf(direction,"Resources/Images/Mokhtar/%d copy.png",i);
        mokhtar[i]=load_image(direction);
        if (i!=6)
        {
            sprintf(direction,"Resources/Images/Wassim/%d copy.png",i);
            wassim[i]=load_image(direction);
        }
        if (i!=6 && i!=5 && i!=4)
        {
            sprintf(direction,"Resources/Images/Salah/%d copy.png",i);
            salah[i]=load_image(direction);
        }
    }
    for (i=0; i<5; i++)
    {
        sprintf(direction,"Resources/Images/maps/%d.png",i);
        maps[i]=load_image(direction);
        //printf ("iD %d \n",maps[i]->ID);
    }
    Background=load_image("Resources/Images/Origin.png");
    Background_bar=load_image("Resources/Images/Origin_bar.png");
    select=load_image("Resources/Images/Select.png");
    Player1=load_image("Resources/Images/player1.png");
    Player2=load_image("Resources/Images/player2.png");


    while (!IsKeyPressed(3,RETURN))
    {

        if(choix1+choix2!=2)
        {

            if (IsKeyPressed(1,ENTER))
                choix1=1;
            if (IsKeyPressed(2,ENTER))
                choix2=1;
            //printf ("Choix1 %d choi %d \n",choix1,choix2);
            if (IsKeyPressed(1,RIGHT) && press_buton>10 && choix1!=1)
            {
                press_buton=0;
                select1 =(select1+1)%5;
                distance_change1=-18;
                selectedPers[select1]=1;
                selectedPers[(select1-1+5)%5]=0;
                if ((select1-1+5)%5==select2)
                    selectedPers[select2]=1;
            }

            if (IsKeyPressed(1,LEFT) && press_buton>10 &&choix1!=1)
            {
                press_buton=0;
                select1 =(select1-1+5)%5;
                selectedPers[(select1+1)%5]=0;
                selectedPers[select1]=1;
                distance_change1=18;
                if ((select1+1)%5==select2)
                    selectedPers[select2]=1;
            }
            if (IsKeyPressed(2,RIGHT) && press_buton2>10 && choix2!=1)
            {
                press_buton2=0;
                select2 =(select2+1)%5;
                selectedPers[(select2-1+5)%5]=0;
                selectedPers[select2]=1;
                distance_change2=-18;
                if ((select2-1+5)%5==select1)
                    selectedPers[select1]=1;

            }
            if (IsKeyPressed(2,LEFT) && press_buton2>10 && choix2!=1)
            {
                press_buton2=0;
                select2 =(select2-1+5)%5;
                selectedPers[select2]=1;
                selectedPers[(select2+1)%5]=0;
                if ((select2+1)%5==select1)
                    selectedPers[select1]=1;
                distance_change2=18;
            }

            //LOGIC
            distance_change2=distance_change2/1.1;
            distance_change1=distance_change1/1.1;
            fade_start=fade_start/1.1;
            press_buton++;
            press_buton2++;
// Drawing

            draw_image_ex(Background,0,0,100,100,NONE,100);
            draw_image_ex(Background_bar,0,-27,100,150,NONE,100-fade_start);
            for (i=4; i<90; i=i+18)
                draw_image_ex(select,i,17.5,19,60,NONE,100-fade_start);
            draw_image_ex(Player1,pos_player[select1]+distance_change1,17.5,19,60,NONE,100-fade_start);
            draw_image_ex(Player2,pos_player[select2]+distance_change2,17.5,19,60,NONE,100-fade_start);
// Draw and turn Mokhtar
            if (selectedPers[0]==0 )
            {
                w=(50.0f/((float)mokhtar[mokhtar_turn]->h/(float)mokhtar[mokhtar_turn]->w))/ratioo;
                draw_image_ex(mokhtar[0],pos_player[0]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[0],100-fade);
            }
            else
            {
                if (mokhtar_turn==0)
                {
                    ind_turn_mokhtar=1;
                    Turn[0]=NONE;
                }
                if (mokhtar_turn==6)
                {
                    ind_turn_mokhtar=-1;
                    Turn[0]=VERTICAL;
                }
                if(FrameCount%10==0)
                    mokhtar_turn=(mokhtar_turn+ind_turn_mokhtar)%7;
                w=(50.0f/((float)mokhtar[mokhtar_turn]->h/(float)mokhtar[mokhtar_turn]->w))/ratioo;
                draw_image_ex(mokhtar[mokhtar_turn],pos_player[0]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[0],100-fade);
            }

// Draw and turn haitham
            if (selectedPers[1]==0)
            {

                w=(50.0f/((float)haitham[0]->h/(float)haitham[0]->w))/ratioo;
                draw_image_ex(haitham[0],pos_player[1]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[1],100-fade);
            }
            else
            {
                if (haitham_turn==0)
                {
                    ind_turn_haitham=1;
                    Turn[1]=NONE;
                }
                if (haitham_turn==6)
                {
                    ind_turn_haitham=-1;
                    Turn[1]=VERTICAL;
                }
                if(FrameCount%10==0)
                    haitham_turn=(haitham_turn+ind_turn_haitham)%7;
                w=(50.0f/((float)haitham[haitham_turn]->h/(float)haitham[haitham_turn]->w))/ratioo;
                draw_image_ex(haitham[haitham_turn],pos_player[1]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[1],100-fade);
            }

// Draw and turn brahim

            if (selectedPers[2]==0)
            {
                w=(50.0f/((float)brahim[0]->h/(float)brahim[0]->w))/ratioo;

                draw_image_ex(brahim[0],pos_player[2]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[2],100-fade);
            }
            else
            {
                if (brahim_turn==0)
                {
                    ind_turn_brahim=1;
                    Turn[2]=NONE;
                }
                if (brahim_turn==6)
                {
                    ind_turn_brahim=-1;
                    Turn[2]=VERTICAL;
                }
                if(FrameCount%10==0)
                    brahim_turn=(brahim_turn+ind_turn_brahim)%7;
                w=(50.0f/((float)brahim[brahim_turn]->h/(float)brahim[brahim_turn]->w))/ratioo;

                draw_image_ex(brahim[brahim_turn],pos_player[2]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[2],100-fade);
            }

// Draw and turn salah
            if (selectedPers[3]==0)
            {
                w=(50.0f/((float)salah[0]->h/(float)salah[0]->w))/ratioo;
                draw_image_ex(salah[0],pos_player[3]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[3],100-fade);
            }
            else
            {
                if (salah_turn==0)
                {
                    ind_turn_salah=1;
                    Turn[3]=NONE;
                }
                if (salah_turn==3)
                {
                    ind_turn_salah=-1;
                    Turn[3]=VERTICAL;
                }
                if(FrameCount%10==0)
                    salah_turn=(salah_turn+ind_turn_salah)%4;
                w=(50.0f/((float)salah[salah_turn]->h/(float)salah[salah_turn]->w))/ratioo;
                draw_image_ex(salah[salah_turn],pos_player[3]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[3],100-fade);
            }
            // Draw and turn Wassim
            if (selectedPers[4]==0)
            {
                w=(50.0f/((float)wassim[0]->h/(float)wassim[0]->w))/ratioo;
                draw_image_ex(wassim[0],pos_player[4]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[4],100-fade);
            }
            else

            {
                if (wassim_turn==0)
                {
                    ind_turn_wassim=1;
                    Turn[4]=NONE;
                }
                if (wassim_turn==5)
                {
                    ind_turn_wassim=-1;
                    Turn[4]=VERTICAL;
                }
                if(FrameCount%10==0)
                    wassim_turn=(wassim_turn+ind_turn_wassim)%6;
                w=(50.0f/((float)wassim[wassim_turn]->h/(float)wassim[wassim_turn]->w))/ratioo;
                draw_image_ex(wassim[wassim_turn],pos_player[4]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[4],100-fade);
            }
            if (choix1)
                draw_text(Verdana,"PLAYER 1 Ready",10,20,10,CENTER,100);
            if (choix2)
                draw_text(Verdana,"PLAYER 2 Ready",10,75,10,CENTER,100);
            next_frame();

        }
        if(choix1+choix2==2){
            while(IsKeyPressed(3,ENTER))
            {
                rest(1);
            }
        }

        while(choix1+choix2==2)
        {
            if (IsKeyPressed(3,RETURN))
            {
                choix1=0;
                choix2=0;

            while(IsKeyPressed(3,RETURN))
            {
                rest(1);
            }
            }



            if (IsKeyPressed(3,ENTER) && press_buton>10)
            {
                press_buton=0;
                voice_stop(intro);
                GamePlay(3,1,maps[select_map]);
                voice_start(intro);
            }

            if (IsKeyPressed(3,RIGHT) && press_buton >10)
            {
                press_buton=0;
                select_map=(select_map-1+5)%5;
                distance_change_map=50;
            }

            if (IsKeyPressed(3,LEFT) && press_buton> 10)
            {
                press_buton=0;
                select_map=(select_map+1)%5;

                distance_change_map=-50;
            }
            distance_change_map=distance_change_map/1.1;
            draw_image_ex(Background,0,0,100,100,NONE,100);
            draw_image_ex(Background_bar,0,-27,100,150,NONE,100);
            draw_image_ex(maps[(select_map+1)%5],-25+distance_change_map,27,50,40,NONE,30+distance_change_map);
            draw_image_ex(maps[select_map],25+distance_change_map,27,50,40,NONE,100);
            draw_image_ex(maps[(select_map-1+5)%5],75+distance_change_map,27,50,40,NONE,30-distance_change_map);
            draw_image_ex(select,20,23,60,48,NONE,100);
            press_buton++;
            next_frame();


        }
    }

    while (fade<100)
    {
        fade=fade*1.1;
        draw_image_ex(Background,0,0,100,100,NONE,100);
        draw_image_ex(Background_bar,0,-27,100,150,NONE,100-fade);
        /*for (i=4; i<90; i=i+18)
            draw_image_ex(select,i,17.5,19,60,NONE,100-fade);
        draw_image_ex(mokhtar[0],pos_player[0]+2,21,15,50,NONE,100-fade);
        draw_image_ex(haitham[0],pos_player[1]+2,21,15,50,NONE,100-fade);
        draw_image_ex(brahim[0],pos_player[2]+2,21,15,50,NONE,100-fade);
        draw_image_ex(salah[0],pos_player[3]+2,21,15,50,NONE,100-fade);
        draw_image_ex(wassim[0],pos_player[4]+2,21,15,50,NONE,100-fade);
        draw_image_ex(Player1,pos_player[select1]+distance_change1,17.5,19,60,NONE,100-fade);
        draw_image_ex(Player2,pos_player[select2]+distance_change2,17.5,19,60,NONE,100-fade);*/
        next_frame();
    }
}

void ChargerEffetNaturel(IMAGE *effet[100], char chemin[200], int nombreFrame)
{
    int i; char tmp[200];

    for(i=0;i<nombreFrame;i++)
    {
        sprintf(tmp,"%s%.2d.png", chemin, i);
        effet[i]=load_image(tmp);
    }

}
int indice_rain=0;
void GamePlay(int Player1,int Player2,IMAGE* Map){
    int time =30;
    char texttime[10];
    IMAGE*rain[100],*flies[100],*Map2;
    int thunder, rainsound,gameplaysound,sarsour,fight,lotfi;

    next_frame();
    draw_text(SharpCurve,"Loading...",20,50,50,CENTER,100);
    next_frame();

    Map2=load_image("Resources/Images/maps/0.png");
    ChargerEffetNaturel(rain,"Resources/Images/Rain/rain00",100);
    ChargerEffetNaturel(flies,"Resources/Images/nightFilies/nightFlies00",100);
    LoadSalah(1);
    LoadHaitham(2);

    thunder=AddVoice("Resources/Sounds/Thunder.wav",1);
    rainsound=AddVoice("Resources/Sounds/Rain.wav",1);
    gameplaysound=AddVoice("Resources/Sounds/Gameplay.wav",0);
    sarsour=AddVoice("Resources/Sounds/Sarsour.wav",1);
    fight=AddVoice("Resources/Sounds/Fight.wav",1);
    lotfi=AddVoice("Resources/Sounds/Lotfi.wav",0);
    DoEarth(FRANCE,MALAYSIA);

    sprintf(texttime,"%d",time);

    voice_set_playmode(thunder, PLAYMODE_LOOP);
    voice_set_playmode(rainsound, PLAYMODE_LOOP);
    voice_set_playmode(gameplaysound, PLAYMODE_LOOP);
    voice_set_playmode(sarsour, PLAYMODE_LOOP);
    voice_set_playmode(lotfi, PLAYMODE_LOOP);

    voice_set_volume(rainsound,255);
    voice_set_volume(thunder,100);
    voice_set_volume(gameplaysound,128);
    voice_set_volume(lotfi,80);

    voice_start(thunder);
    voice_start(rainsound);
    voice_start(gameplaysound);

    voice_start(fight);
    while(!IsKeyPressed(3,RETURN)){
        draw_image_ex(Map,-1.5,-2,103,104,NONE,100);
        Draw_Salah();
        Draw_Haitham();

        if(FrameCount%60==0){
            sprintf(texttime,"%d",time);
            time--;
        }
        if(time<0){
            break;
        }

        draw_image_ex(rain[indice_rain],0,0,100,100,NONE,100);
        if(FrameCount%3==0)
        indice_rain=(indice_rain+1)%100;

        draw_text(Arista,texttime,10,50,5,CENTER_X,95);
        next_frame();
    }
    voice_stop(thunder);
    voice_stop(rainsound);
    voice_stop(gameplaysound);

    time=30;
    DoEarth(MALAYSIA,TUNISIA);
    voice_start(sarsour);
    voice_start(lotfi);
    voice_start(fight);
    while(!IsKeyPressed(3,RETURN)){
        draw_image_ex(Map2,-1.5,-2,103,104,NONE,100);
        Draw_Salah();
        Draw_Haitham();

        if(FrameCount%60==0){
            sprintf(texttime,"%d",time);
            time--;
        }
        if(time<0){
            break;
        }

        draw_image_ex(flies[indice_rain],0,0,100,100,NONE,100);
        if(FrameCount%3==0)
        indice_rain=(indice_rain+1)%100;

        draw_text(Arista,texttime,10,50,5,CENTER_X,95);
        next_frame();
    }
    voice_stop(sarsour);
    voice_stop(lotfi);
}
