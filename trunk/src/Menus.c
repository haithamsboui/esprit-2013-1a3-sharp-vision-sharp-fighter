#include "includes.h"
int close_button_pressed = 0;

void close_button_handler()
{
    close_button_pressed = 1;
}
END_OF_FUNCTION(close_button_handler)

void intromenu(int intro)
{
    int i,waitframes,keypress=0;
    float texttrans=0, textmulti=3, drawtrans=0,drawmulti=0.3, drawval=0;
    IMAGE *background,*logo;
    Pointf InterpolationPoints[]= {{.x=-25.0f,.y=-100.0f},{.x=0.0f,.y=0.0f},{.x=50.0f,.y=75.0f},{.x=100.0f,.y=100.0f}};
    background=load_image("Resources/Images/Origin.png");
    logo=load_image("Resources/Images/logo2.png");
    PlayVideo("Resources/Videos/EspritIntro.ogv");
    PlayVideo("Resources/Videos/SharpIntro.ogv");
    PlayVideo("Resources/Videos/FighterIntro.ogv");

    while(AnyKeyPressed(3))
    {
        rest(10);
    }

    voice_set_playmode(intro, PLAYMODE_LOOP);
    voice_set_volume(intro,0);
    voice_start(intro);
    voice_ramp_volume(intro,1000,Music_volume);

    waitframes=FrameCount;

    while(!keypress && !close_button_pressed)
    {
        if(FrameCount%5==0)
        {
            keypress=AnyKeyPressed(3);
        }

        if((FrameCount-waitframes)/(float)FPS>30)
        {
            voice_ramp_volume(intro,1000,0);
            PlayVideo("Resources/Videos/FighterIntro.ogv");

            waitframes=FrameCount;
            voice_ramp_volume(intro,1000,Music_volume);
        }

        draw_image_ex(background,0,0,100,100,NONE,100);
        for(i=256; i>0; i/=2)
        {
            draw_image_ex(logo,10-drawtrans/(100.0f/(4.0f*i)),32-drawtrans/(100.0f/(2.0f*i)),80+drawtrans/(100.0f/(8.0f*i)),0,NONE,(drawtrans-10)/(2*i));
        }
        draw_image_ex(logo,10,32,80,0,NONE,150-drawtrans);
        if(texttrans>100 || texttrans<0)
        {
            textmulti=textmulti* (-1);
        }
        texttrans+=textmulti;
        if(drawval>100 || drawval<0)
        {
            drawmulti=drawmulti* (-1);
        }
        drawval+=drawmulti;
        drawtrans=LaGrange(InterpolationPoints,3,drawval);
        draw_text(Arista,"Press any key to continue...",10,50,80,CENTER,texttrans);
        next_frame();
    }
}


void mainmenu(int *choix)
{
clear_keybuf();
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
    // drawingsvn
    *choix=*choix+1;
    ind_1=*choix;
    ind_2=(ind_1-1+5)%5;
    ind_3=(ind_2-1+5)%5;
    ind_4=(ind_3-1+5)%5;
    while (!IsKeyPressed(3,ENTER) && !close_button_pressed)
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
        draw_image_ex(Pers_main[select_pers],60,0,50,0,NONE,100-fade_start-abs(2*scale)); // draw mokhtar
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
        draw_image_ex(Pers_main[select_pers],60,0,50,0,NONE,100-fade ); // draw mokhtar
        next_frame();
    }

}

void setting ()
{
    IMAGE *Volumes[2],*Background,*back_cadre,*icon[3],*select,*volume_point,*display_cadre,*screen,* resolution,*joystick,*keybord,*cadre_control,*cadre_modif,*volume_cadre;
    float distance_change=100,cadre_display_pos[]= {49.6,76.6},cadre_volume_pos[]= {49.3,75.6},entre=0,fade=1,volume_fade=100,controlpos[]= {38.6,55.6},control_distance=5,keybord_fade=0,joystick_fade=0,modif_fade=0.1;
    int ind1=0,ind2=1,ind3=2,pos_x[]= {5,35,65},button_press=0,trans,second_menu=0,Nb_point_volume_music,Nb_point_volume_effect;
    int i,Button;
    char screen_mod[15],res[10],buttons[50];
    int cadre_ind=0,control_in=0,key_modif=0;
    char *keybord_control[]= {"UP","DOWN","LEFT","RIGHT","PUNCH","KICK","DEFENCE","FIREBALL","FREEZE","THUNDER","WIND","ENTER","RETURN"};
    IMAGE *BUTTONS[14],*keybord_modif;
    Button=AddVoice("Resources/Sounds/button3.wav",1);
    int ReadingKey=0,PlayerSelection=0,SelectedPlayer=1,PlayerPos[]= {45,60};
    //Loading;
    for (i=0; i<14; i++)
    {
        sprintf(buttons,"Resources/Images/Buttons/%d.png",i);
        BUTTONS[i]=load_image(buttons);
    }
    keybord_modif=load_image("Resources/Images/setting/select_modif_control.png");
    volume_cadre=load_image("Resources/Images/setting/Volume_cadre.png");
    cadre_control=load_image("Resources/Images/setting/cadre_control.png");
    screen=load_image("Resources/Images/setting/screen.png");
    resolution=load_image("Resources/Images/setting/resolution.png");
    joystick=load_image("Resources/Images/setting/joystick.png");
    keybord=load_image("Resources/Images/setting/keybord.png");
    Background=load_image("Resources/Images/Origin.png");
    back_cadre=load_image("Resources/Images/Origin_bar.png");
    display_cadre=load_image("Resources/Images/setting/display.png");
    icon[0]=load_image("Resources/Images/setting/graphics.png");
    icon[1]=load_image("Resources/Images/setting/sound.png");
    icon[2]=load_image("Resources/Images/setting/controll.png");
    select=load_image("Resources/Images/setting/Select.png");
    Volumes[0]=load_image("Resources/Images/setting/Volume_bar.png");
    Volumes[1]=load_image("Resources/Images/setting/Volume_bar1.png");
    volume_point=load_image("Resources/Images/setting/sound_point.png");
    cadre_modif=load_image("Resources/Images/setting/control_modif.png");
    Nb_point_volume_music=Music_volume/19;
    Nb_point_volume_effect=Effect_volume/19;
    if (Fullscreen==1)
        sprintf (screen_mod,"Fullscreen");
    else
        sprintf (screen_mod,"Windowed");

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
        if(close_button_pressed) return;
        if (second_menu==0)
        {
            if (IsKeyPressed(3,RIGHT) && button_press>10 )
            {
                voice_start(Button);

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
                voice_start(Button);

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
                voice_start(Button);

                distance_change=0;
                entre=5;
                button_press=0;
                second_menu=1;
                fade=0;

            }
        }

        if (second_menu==1 )
        {
            if (IsKeyPressed(3,RETURN) && button_press>10 && control_in ==0)
            {
                voice_start(Button);

                distance_change=0;
                entre=0;
                button_press=0;
                second_menu=0;
                fade=5;
                volume_fade=100;
                modif_fade=0.1;
                cadre_ind=0;
                while(IsKeyPressed(3,RETURN))
                {
                    rest(1);
                }
            }

            switch(ind2)
            {
            case 0 :
            {
                if (IsKeyPressed(3,DOWN) && button_press>10)
                {
                    voice_start(Button);

                    cadre_ind=(cadre_ind+1)%2;//;
                    button_press=0;
                }

                if (IsKeyPressed(3,UP) && button_press>10)
                {
                    voice_start(Button);

                    cadre_ind=(cadre_ind-1+2)%2;//49.6;
                    button_press=0;
                }

                if (IsKeyPressed(3,LEFT) && button_press>10)
                {
                    voice_start(Button);

                    button_press=0;

                    if (cadre_ind==0 )
                    {
                        Fullscreen=(Fullscreen-1+2)%2;
                        if (Fullscreen)
                            sprintf(screen_mod,"Fullscreen");
                        else
                            sprintf(screen_mod,"Windowed");
                        change_resolution(Fullscreen,ResolutionIndex);
                    }
                    if (cadre_ind ==1)

                    {
                        ResolutionIndex=(ResolutionIndex-1+(Resolutions->num_modes))%(Resolutions->num_modes);
                        if (Resolutions->mode[ResolutionIndex].width == Resolutions->mode[(ResolutionIndex+1)%Resolutions->num_modes].width && Resolutions->mode[ResolutionIndex].height==Resolutions->mode[(ResolutionIndex+1)%Resolutions->num_modes].height)
                            ResolutionIndex=(ResolutionIndex-1+Resolutions->num_modes)%(Resolutions->num_modes);

                        change_resolution(Fullscreen,ResolutionIndex);
                    }
                }

                if(IsKeyPressed(3,RIGHT) && button_press>10)
                {
                    voice_start(Button);

                    button_press=0;
                    if (cadre_ind==0 )
                    {
                        Fullscreen=(Fullscreen+1)%2;
                        if (Fullscreen)
                            sprintf(screen_mod,"Fullscreen");
                        else
                            sprintf(screen_mod,"Windowed");

                        change_resolution(Fullscreen,ResolutionIndex);
                    }
                    if (cadre_ind ==1)
                    {
                        ResolutionIndex=(ResolutionIndex+1)%Resolutions->num_modes;
                        if (Resolutions->mode[ResolutionIndex].width == Resolutions->mode[(ResolutionIndex-1+Resolutions->num_modes)%Resolutions->num_modes].width && Resolutions->mode[ResolutionIndex].height==Resolutions->mode[(ResolutionIndex-1+Resolutions->num_modes)%Resolutions->num_modes].height)
                            ResolutionIndex=(ResolutionIndex+1)%(Resolutions->num_modes);
                        change_resolution(Fullscreen,ResolutionIndex);
                    }
                }
            }
            break;
            case 1 :
            {
                if ((IsKeyPressed(3,DOWN) || IsKeyPressed(3,UP) ) && button_press>10 )
                {
                    voice_start(Button);
                    button_press=0;
                    cadre_ind=(cadre_ind+1)%2;
                }

                if (IsKeyPressed(3,LEFT)  && button_press>1)
                {
                    voice_start(Button);

                    button_press=0;

                    if (cadre_ind==0 && Music_volume>0)
                    {
                        Music_volume-=5;
                        SetMusicVolume(Music_volume);
                        Nb_point_volume_music=Music_volume/19;

                    }
                    if (cadre_ind==1 &&  Effect_volume>0)
                    {
                        Effect_volume-=5;
                        SetEffectsVolume(Effect_volume);
                        Nb_point_volume_effect=Effect_volume/19;

                    }
                }

                if (IsKeyPressed(3,RIGHT) && button_press>1)
                {
                    voice_start(Button);

                    button_press=0;
                    if (cadre_ind==0 && Music_volume<255)
                    {
                        Music_volume+=5;
                        SetMusicVolume(Music_volume);
                        Nb_point_volume_music=Music_volume/19;

                    }
                    if (cadre_ind==1 && Effect_volume<255)
                    {

                        Effect_volume+=5;
                        SetEffectsVolume(Effect_volume);
                        Nb_point_volume_effect=Effect_volume/19;

                    }
                }
            }
            break;
            case 2 :
            {
                if (control_in==1)
                {


                    if (IsKeyPressed(3,RETURN) && button_press>10  )
                    {
                        if (PlayerSelection==0)
                        {
                            voice_start(Button);
                            control_in=0;
                            button_press=0;
                            keybord_fade=0;
                            joystick_fade=0;
                            modif_fade=0.1;
                            key_modif=0;
                        }
                        else
                            PlayerSelection=0;
                        SelectedPlayer=1;
                        while(IsKeyPressed(3,RETURN))
                        {
                            rest(1);
                        }
                    }
                    if (PlayerSelection==0)
                    {

                        if (IsKeyPressed(3,UP) && button_press>10)
                        {
                            SelectedPlayer=(SelectedPlayer)%2+1;
                            button_press=0;
                        }
                        if (IsKeyPressed(3,DOWN) && button_press>10)
                        {
                            SelectedPlayer=(SelectedPlayer)%2+1;
                            button_press=0;
                        }
                        if (IsKeyPressed(3,ENTER) && button_press>10)
                        {
                            PlayerSelection=1;
                            button_press=0;
                        }

                    }
                    if (PlayerSelection)
                    {
                        if (cadre_ind==0)
                        {
                            if(ReadingKey)
                            {
                                ReadingKey=0;
                                clear_keybuf();
                                draw_image_ex(screenimage,0,0 ,100,100,NONE,30);
                                draw_text( SharpCurve,"PRESS KEY ",15,50,45,CENTER_X,100);
                                next_frame();
                                ReadKeyboard(SelectedPlayer,key_modif);
                                button_press=0;
                            }
                            if (IsKeyPressed(3,ENTER) && button_press>10)
                            {
                                ReadingKey=1;
                                button_press=0;

                            }

                            if (IsKeyPressed(3,UP) && button_press>10 )
                            {
                                button_press=0;
                                key_modif=(key_modif-1+13)%13;
                            }

                            if (IsKeyPressed(3,DOWN) && button_press>10 )
                            {
                                button_press=0;
                                key_modif=(key_modif+1)%13;
                            }
                        }

                        if (cadre_ind==1 && JoyStickEnabled && button_press>10)
                        {
                            if(ReadingKey)
                            {

                                ReadingKey=0;
                                draw_image_ex(screenimage,0,0 ,100,100,NONE,30);
                                draw_text( SharpCurve,"PRESS KEY ",15,50,45,CENTER_X,100);
                                next_frame();
                                rest(100);
                                ReadJoystick(SelectedPlayer,key_modif);
                                button_press=0;
                            }

                            if (IsKeyPressed(3,ENTER) && button_press>10 )
                            {
                                ReadingKey=1;
                                button_press=0;

                            }

                            if (IsKeyPressed(3,UP) && button_press>10 )
                            {
                                button_press=0;
                                key_modif=(key_modif-1+13)%13;
                            }

                            if (IsKeyPressed(3,DOWN) && button_press>10 )
                            {
                                button_press=0;
                                key_modif=(key_modif+1)%13;

                            }
                        }
                    }
                }
                if (control_in==0)
                {
                    if (IsKeyPressed(3,DOWN) && button_press>10)
                    {
                        voice_start(Button);

                        button_press=0;
                        cadre_ind=(cadre_ind+1)%2;
                    }

                    if (IsKeyPressed(3,UP) && button_press>10)
                    {
                        voice_start(Button);

                        button_press=0;
                        cadre_ind=(cadre_ind+1)%2;
                    }

                    if (IsKeyPressed(3,ENTER) && button_press>10 && control_in == 0)
                    {
                        voice_start(Button);

                        button_press=0;
                        control_in=1;
                        if (cadre_ind==0)
                            joystick_fade=10;
                        else
                            keybord_fade=10;
                    }
                }
            }
            break;
            }
        }
        if (modif_fade<100 )
            modif_fade=modif_fade*1.1;

        if (joystick_fade<100)
            joystick_fade=joystick_fade*1.4;

        if (keybord_fade<100)
            keybord_fade=keybord_fade*1.1;

        control_distance=control_distance/1.05;
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

        if (second_menu==1 && ind2==0)
        {
            draw_image_ex(screen,30,35.6-volume_fade/3,40,25,NONE,100-volume_fade);
            draw_image_ex(resolution,30,62.6-volume_fade/3,40,25,NONE,100-volume_fade);
            draw_text(Verdana,screen_mod,5,50,53-volume_fade/3,CENTER,100);
            sprintf(res,"%dx%d",Width,Height);
            draw_text(Verdana,res,5,50,80-volume_fade/3,CENTER,100);
            draw_image_ex(display_cadre,33,cadre_display_pos[cadre_ind]-3-volume_fade/3,35,12.5,NONE,100-volume_fade);
        }

        if (second_menu==1 && ind2==1)
        {
            draw_image_ex(Volumes[0],33.5,39.6-volume_fade/3,35,25,NONE,100-volume_fade);
            draw_image_ex(Volumes[1],33.5,65.6-volume_fade/3,35,25,NONE,100-volume_fade);
            draw_image_ex(volume_cadre,35.3,cadre_volume_pos[cadre_ind]-0.3-volume_fade/3,31.7,13.5,NONE,100-volume_fade);

            for (i=0; i<Nb_point_volume_music; i++)

                draw_image_ex(volume_point,41.3+i*1.5,54.3,1.5,3-volume_fade/4,NONE,100-volume_fade);
            for (i=0; i<Nb_point_volume_effect; i++)
                draw_image_ex(volume_point,41.3+i*1.5,80.3,1.5,3-volume_fade/4,NONE,100-volume_fade);
        }


        if (second_menu==1 && ind2==2)
        {
            if (control_in==0)
            {
                draw_image_ex(keybord,33,38.6-volume_fade/3,35,10,NONE,100-volume_fade);
                draw_image_ex(joystick,33,55.6-volume_fade/3,35,10,NONE,100-volume_fade);
                draw_image_ex(cadre_control,33,controlpos[cadre_ind]-volume_fade/3,35,10,NONE,100-volume_fade);
            }
            if (control_in==1 && PlayerSelection==0)
            {
                draw_text(Verdana,"Player 1",5,50,50,CENTER,100);
                draw_text(Verdana,"Player 2",5,50,65,CENTER,100);
                draw_image_ex(keybord_modif,40,PlayerPos[SelectedPlayer-1],20,10,NONE,100);
            }
            if (control_in==1 && PlayerSelection==1)
            {

                draw_image_ex(keybord,33,38.6-volume_fade/3-joystick_fade/10,35,10,NONE,100-volume_fade-keybord_fade);
                draw_image_ex(joystick,33,55.6-volume_fade/3-keybord_fade/3.8,35,10,NONE,100-volume_fade-joystick_fade);
                draw_image_ex(cadre_control,33,controlpos[cadre_ind]-volume_fade/3-keybord_fade/3.8-joystick_fade/10,35,10,NONE,100-volume_fade);
                draw_image_ex(cadre_modif,33,35.5,35,modif_fade/1.62,NONE,modif_fade);
                switch (cadre_ind)
                {
                case 0:


                    for (i=0; i<13; i++)
                    {

                        draw_text(Verdana,keybord_control[i],2.5,40,45+4*i,CENTER,modif_fade);
                        if (SelectedPlayer==1)
                            draw_text(Verdana,scancode_to_name(Player1Keyboard[i]),2.5,60,45+i*4,CENTER,modif_fade);
                        else
                            draw_text(Verdana,scancode_to_name(Player2Keyboard[i]),2.5,60,45+i*4,CENTER,modif_fade);
                    }
                    draw_image_ex(keybord_modif,35,42.5+key_modif*4,31,4,NONE,modif_fade);

                    break;
                case 1 :
                    if (JoyStickEnabled)
                    {
                        for (i=0; i<13; i++)
                        {
                            draw_text(Verdana,keybord_control[i],2.5,40,45+4*i,CENTER,modif_fade);
                            if (SelectedPlayer==1)
                                draw_image_ex(BUTTONS[Player1Joypad[i]],60,43+4*i,0,4,NONE,modif_fade);
                            else
                                draw_image_ex(BUTTONS[Player2Joypad[i]],60,43+4*i,0,4,NONE,modif_fade);
                        }
                        draw_image_ex(keybord_modif,35,42.5+key_modif*4,31,4,NONE,modif_fade);

                    }
                    else
                        draw_text(Verdana,"No joystick detected",5,50,60,CENTER,100);
                    break;
                }
            }

        }
        if (ReadingKey)
            PrintScreen(0);
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
        if(close_button_pressed) return;
        draw_image_ex(credit,0,100-i,100,100,NONE,100);//draw background
        i+=0.1;
        next_frame();
    }
    voice_stop(intro);
}

