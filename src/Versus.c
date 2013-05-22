#include "includes.h"

void versus (int intro)
{
    IMAGE *Background ,*Background_bar,*select,*Player1,*Player2,*haitham[8],*mokhtar[9],*brahim[8],*wassim[10],*salah[10],*maps[5],*Ready[2];
    int i,pos_player[]= {4,22,40,58,76},select1=0,select2=4,Ready_pos[]= {8,26,44,62,80}; //distance=18
    int press_buton=0,press_buton2=0,ind_turn_mokhtar=0,ind_turn_haitham=0,ind_turn_brahim=0,ind_turn_salah=0,ind_turn_wassim=0;
    flip Turn[]= {NONE,NONE,NONE,NONE,NONE};
    int selectedPers[5]= {1,0,0,0,1},brahim_turn=0,haitham_turn=0,salah_turn=0,mokhtar_turn=0,wassim_turn=0,select_map=0;
    float distance_change1=0,distance_change2=0,fade=1,fade_start=100;
    char direction[100];
    int choix1=0,choix2=0,/*map_pos[]= {6,24,42,60,78}*/distance_change_map=20;
    float w;
    char *maps_names[]= {"Tunisia,Tunis","Egypt,Giza","India,Taj Mahal","Japan,Kyoto","Malaysia,Kuala Lampur"};


    // Loading caracteres

    for (i=0; i<8; i++)
    {
        sprintf(direction,"Resources/Images/Haitham/%d.png",i);
        haitham[i]=load_image(direction);
    }
    for (i=0; i<8; i++)
    {
        sprintf(direction,"Resources/Images/Brahim/%d.png",i);
        brahim[i]=load_image(direction);
    }
    for (i=0; i<9; i++)
    {
        sprintf(direction,"Resources/Images/Mokhtar/%d.png",i);
        mokhtar[i]=load_image(direction);
    }
    for (i=0; i<10; i++)
    {
        sprintf(direction,"Resources/Images/Wassim/%d.png",i);
        wassim[i]=load_image(direction);
    }
    for (i=0; i<10; i++)
    {
        sprintf(direction,"Resources/Images/Salah/%d.png",i);
        salah[i]=load_image(direction);
    }

    for (i=0; i<5; i++)
    {
        sprintf(direction,"Resources/Images/maps/%d.png",i);
        maps[i]=load_image(direction);
    }
    Background=load_image("Resources/Images/Origin.png");
    Background_bar=load_image("Resources/Images/Origin_bar.png");
    select=load_image("Resources/Images/Select.png");
    Player1=load_image("Resources/Images/Versus/player1.png");
    Player2=load_image("Resources/Images/Versus/player2.png");
    Ready[0]=load_image("Resources/Images/Versus/ready1.png");
    Ready[1]=load_image("Resources/Images/Versus/ready2.png");

    while (!IsKeyPressed(3,RETURN) || (choix1+choix2!=0))
    {
        if(close_button_pressed) return;
        if(choix1+choix2!=2)
        {

            if (IsKeyPressed(1,ENTER) && select1!=select2 )
                choix1=1;
            if (IsKeyPressed(2,ENTER) && select1!=select2)
                choix2=1;

            if (IsKeyPressed(1,RETURN) && choix1==1)
            {

                choix1=0;
                while (IsKeyPressed(1,RETURN))
                    rest(1);
            }
            if (IsKeyPressed(2,RETURN) && choix2==1)
            {

                choix2=0;
                while (IsKeyPressed(2,RETURN))
                    rest(1);

            }
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
            draw_image_ex(Player1,pos_player[select1]+distance_change1,8.1,19,69.5,NONE,100-fade_start);
            draw_image_ex(Player2,pos_player[select2]+distance_change2,8.1,19,69.5,NONE,100-fade_start);
// Draw and turn Mokhtar
            if (selectedPers[0]==0 )
            {
                w=(50.0f/((float)mokhtar[0]->h/(float)mokhtar[0]->w))/AspectRatio;
                draw_image_ex(mokhtar[0],pos_player[0]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[0],100-fade);
            }
            else
            {
                if (mokhtar_turn==0)
                {
                    ind_turn_mokhtar=1;
                    Turn[0]=NONE;
                }

                if (mokhtar_turn==8)
                {
                    ind_turn_mokhtar=-1;
                    Turn[0]=VERTICAL;
                }

                if(FrameCount%10==0)
                    mokhtar_turn=(mokhtar_turn+ind_turn_mokhtar)%9;

                w=(50.0f/((float)mokhtar[mokhtar_turn]->h/(float)mokhtar[mokhtar_turn]->w))/AspectRatio;
                draw_image_ex(mokhtar[mokhtar_turn],pos_player[0]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[0],100-fade);
            }

// Draw and turn haitham
            if (selectedPers[1]==0)
            {

                w=(50.0f/((float)haitham[0]->h/(float)haitham[0]->w))/AspectRatio;
                draw_image_ex(haitham[0],pos_player[1]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[1],100-fade);
            }
            else
            {
                if (haitham_turn==0)
                {
                    ind_turn_haitham=1;
                    Turn[1]=NONE;
                }
                if (haitham_turn==7)
                {
                    ind_turn_haitham=-1;
                    Turn[1]=VERTICAL;
                }
                if(FrameCount%10==0)
                    haitham_turn=(haitham_turn+ind_turn_haitham)%8;
                w=(50.0f/((float)haitham[haitham_turn]->h/(float)haitham[haitham_turn]->w))/AspectRatio;
                draw_image_ex(haitham[haitham_turn],pos_player[1]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[1],100-fade);
            }

// Draw and turn brahim

            if (selectedPers[2]==0)
            {
                w=(50.0f/((float)brahim[0]->h/(float)brahim[0]->w))/AspectRatio;

                draw_image_ex(brahim[0],pos_player[2]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[2],100-fade);
            }
            else
            {
                if (brahim_turn==0)
                {
                    ind_turn_brahim=1;
                    Turn[2]=NONE;
                }
                if (brahim_turn==7)
                {
                    ind_turn_brahim=-1;
                    Turn[2]=VERTICAL;
                }
                if(FrameCount%10==0)
                    brahim_turn=(brahim_turn+ind_turn_brahim)%8;
                w=(50.0f/((float)brahim[brahim_turn]->h/(float)brahim[brahim_turn]->w))/AspectRatio;

                draw_image_ex(brahim[brahim_turn],pos_player[2]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[2],100-fade);
            }

// Draw and turn salah
            if (selectedPers[3]==0)
            {
                w=(50.0f/((float)salah[0]->h/(float)salah[0]->w))/AspectRatio;
                draw_image_ex(salah[0],pos_player[3]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[3],100-fade);
            }
            else
            {
                if (salah_turn==0)
                {
                    ind_turn_salah=1;
                    Turn[3]=NONE;
                }
                if (salah_turn==9)
                {
                    ind_turn_salah=-1;
                    Turn[3]=VERTICAL;
                }
                if(FrameCount%10==0)
                    salah_turn=(salah_turn+ind_turn_salah)%10;
                w=(50.0f/((float)salah[salah_turn]->h/(float)salah[salah_turn]->w))/AspectRatio;
                draw_image_ex(salah[salah_turn],pos_player[3]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[3],100-fade);
            }
            // Draw and turn Wassim
            if (selectedPers[4]==0)
            {
                w=(50.0f/((float)wassim[0]->h/(float)wassim[0]->w))/AspectRatio;
                draw_image_ex(wassim[0],pos_player[4]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[4],100-fade);
            }
            else

            {
                if (wassim_turn==0)
                {
                    ind_turn_wassim=1;
                    Turn[4]=NONE;
                }
                if (wassim_turn==9)
                {
                    ind_turn_wassim=-1;
                    Turn[4]=VERTICAL;
                }
                if(FrameCount%10==0)
                    wassim_turn=(wassim_turn+ind_turn_wassim)%10;
                w=(50.0f/((float)wassim[wassim_turn]->h/(float)wassim[wassim_turn]->w))/AspectRatio;
                draw_image_ex(wassim[wassim_turn],pos_player[4]+2+(15.0f/2.0f)-(float)w/2.0f,21,w,50,Turn[4],100-fade);
            }
            if (choix1)
                draw_image_ex(Ready[0],Ready_pos[select1],40,10,10,NONE,100);
            if (choix2)
                draw_image_ex(Ready[1],Ready_pos[select2],40,10,10,NONE,100);

            next_frame();

        }
        if(choix1+choix2==2)
        {
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
                player1=select1;
                player2=select2;
                GamePlay(select1,select2,select_map);
                return;
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
            draw_text(SharpCurve,"Select a map ",9,48,20.5,CENTER,100);
            draw_text(SharpCurve,maps_names[select_map],7,48.5,75,CENTER,100);
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
        next_frame();
    }

}

void ChargerEffetNaturel(IMAGE *effet[100], char chemin[200], int nombreFrame)
{
    int i;
    char tmp[200];

    for(i=0; i<nombreFrame; i++)
    {
        sprintf(tmp,"%s%.2d.png", chemin, i);
        effet[i]=load_image(tmp);
    }
}

int indice_efx=0;


void GamePlay(int Player1,int Player2,int Map)
{
    IMAGE *MapLoad,*Loadcombo,*EFX[100],*Versus[7],*Score,*Time,*bloodbar,*heads_bar,*heads[5],*Pause[5],*Pause_cadre,*RoundWin;
    int thunder, rainsound,gameplaysound,sarsour,fight,lotfi,button_press=0;
    char MapDirection[50],direction[50],texttime[10],Round[10],time =60,round =1,i,pause=0,Pause_pos_ind=0;
    int Pause_pos[]= {20,35,50,65,80};
    float  gamestart=1.0;
    Player1Health=100;
    Player2Health=100;
    Combot1=0;
    Combot2=0;
    Location loc;
    int Player1Win=0,player2win=0;
    RoundWin=load_image("Resources/Images/Versus/RoundWin.png");
    Power1=load_image("Resources/Images/Versus/Power1.png");
    Power2=load_image("Resources/Images/Versus/Power2.png");
    Versus[0]=load_image("Resources/Images/Mokhtar/Versus.png");
    Versus[1]=load_image("Resources/Images/Haitham/Versus.png");
    Versus[2]=load_image("Resources/Images/Brahim/Versus.png");
    Versus[3]=load_image("Resources/Images/Salah/Versus.png");
    Versus[4]=load_image("Resources/Images/Wassim/Versus.png");
    Versus[5]=load_image("Resources/Images/Versus/Versus.png");
    Versus[6]=load_image("Resources/Images/Versus/VS.png");
    Loadcombo=load_image("Resources/Images/Versus/loadcombo.png");
    Pause_cadre=load_image("Resources/Images/Versus/pause_cadre.png");

    for (i=0; i<5; i++)
    {
        sprintf (direction,"Resources/Images/Versus/%d.png",i);
        heads[i]=load_image(direction);
    }
    for (i=0; i<5; i++)
    {
        sprintf (direction,"Resources/Images/Versus/pause%d.png",i);
        Pause[i]=load_image(direction);
    }
    bloodbar=load_image("Resources/Images/Versus/bloodbar.png");
    Score=load_image("Resources/Images/Versus/score.png");
    Time=load_image("Resources/Images/Versus/time.png");
    heads_bar=load_image("Resources/Images/Versus/heads.png");
    next_frame();


    draw_image_ex(Versus[5],0,0,100,100,NONE,100);
    draw_image_ex(Versus[Player1],0,0,100,100,VERTICAL,100);
    draw_image_ex(Versus[Player2],0,0,100,100,NONE,100);
    draw_image_ex(Versus[6],0,0,100,100,NONE,100);

    next_frame();

    sprintf (MapDirection,"Resources/Images/maps/%d.png",Map);
    MapLoad=load_image(MapDirection);
    switch (Map)
    {
    case 0 :
    {
        loc=TUNISIA;
        ChargerEffetNaturel(EFX,"Resources/Images/nightFilies/nightFlies00",100);
        lotfi=AddVoice("Resources/Sounds/Lotfi.wav",0);
        sarsour=AddVoice("Resources/Sounds/Sarsour.wav",1);
        voice_set_playmode(sarsour, PLAYMODE_LOOP);
        voice_set_playmode(lotfi, PLAYMODE_LOOP);
        voice_set_volume(lotfi,80);
    }
    break;
    case 1 :
        loc=EGYPT;
        break;
    case 2 :

        break;
    case 3 :
        loc=JAPAN;
        ChargerEffetNaturel(EFX,"Resources/Images/Leaf/leaf00",100);
        break;
    case 4 :
    {
        loc=MALAYSIA;
        ChargerEffetNaturel(EFX,"Resources/Images/Rain/rain00",100);
        thunder=AddVoice("Resources/Sounds/Thunder.wav",1);
        rainsound=AddVoice("Resources/Sounds/Rain.wav",1);
        gameplaysound=AddVoice("Resources/Sounds/Gameplay.wav",0);
        voice_set_playmode(gameplaysound, PLAYMODE_LOOP);
        voice_set_playmode(thunder, PLAYMODE_LOOP);
        voice_set_playmode(rainsound, PLAYMODE_LOOP);
        voice_set_volume(rainsound,255);
        voice_set_volume(thunder,100);
        voice_set_volume(gameplaysound,128);
    }

    break;

    }
    switch (Player1)
    {
    case 0 :
        LoadMokhtar(1);
        break;
    case 1 :
        LoadHaitham(1);
        break;
    case 2 :
        LoadBrahim(1);
        break;
    case 3 :
        LoadSalah(1);
        break;
    case 4 :
        LoadWassim(1);
        break;
    }

    switch (Player2)
    {
    case 0 :
        LoadMokhtar(2);
        break;
    case 1 :
        LoadHaitham(2);
        break;
    case 2 :
        LoadBrahim(2);
        break;
    case 3 :
        LoadSalah(2);
        break;
    case 4 :
        LoadWassim(2);
        break;
    }

    fight=AddVoice("Resources/Sounds/Fight.wav",1);
    //  DoEarth(TUNISIA,loc);
    sprintf(texttime,"%d",time);
    voice_start(fight);

    while(Player1Win!=2 && player2win !=2 )
    {
        if (pause==0)
        {

            switch (Map)
            {
            case 0 :
            {
                voice_start(sarsour);
                voice_start(lotfi);
            }
            break;
            case 1 :
            {

            }
            break;
            case 2 :
            {

            }
            break;
            case 3 :
            {

            }
            break;
            case 4 :
            {
                voice_start(gameplaysound);
                voice_start(thunder);
                voice_start(rainsound);
            }
            break;

            }

            draw_image_ex(MapLoad,-1.5,-2,103,104,NONE,100);
            draw_image_ex(EFX[indice_efx],0,-10,100,100,NONE,100);
            if(FrameCount%3==0)
                indice_efx=(indice_efx+1)%100;
            draw_image_ex(Score,-2.5+(Player1Health/2.5-40),3.4,40,0,NONE,100);
            draw_image_ex(Score,61.5+((-Player2Health)/2.5+40),4,40,0,VERTICAL,100);
            draw_image_ex(bloodbar,0,0,100,0,NONE,100);
            draw_image_ex(Time,-15,0,130,0,NONE,100);


            draw_image_ex(heads_bar,0,0,100,0,NONE,100);
            if ( gamestart<100)
            {
                draw_text(Arista,"Fight ",gamestart/4,50,35,CENTER_X,gamestart);
                gamestart+=1.8;
            }
            for (i=0; i<Combot1; i++)
                draw_image_ex(Loadcombo,-2+(i+1)*2.1,0.5,100,0,NONE,100);

            for (i=0; i<Combot2; i++)
                draw_image_ex(Loadcombo,2-(i+1)*2.1,0.5,100,0,VERTICAL,100);


            switch (Player1)
            {
            case 0 :
                Draw_Mokhtar();
                break;
            case 1 :
                Draw_Haitham();

                break;
            case 2 :
                Draw_Brahim();

                break;
            case 3 :
                Draw_Salah();

                break;
            case 4 :
                Draw_Wassim();
                break;
            }

            switch (Player2)
            {
            case 0 :
                Draw_Mokhtar();
                break;
            case 1 :
                Draw_Haitham();
                break;
            case 2 :
                Draw_Brahim();
                break;
            case 3 :
                Draw_Salah();
                break;
            case 4 :
                Draw_Wassim();
                break;
            }

            draw_image_ex(heads[Player1],0,0,100,0,VERTICAL,100);
            draw_image_ex(heads[Player2],0,0,100,0,NONE,100);
 for (i=0;i<Player1Win;i++)
                        draw_image_ex(RoundWin,27.5+i*3.4,26.9,2,0,NONE,100);

            for (i=0;i<player2win;i++)
                        draw_image_ex(RoundWin,71.95-i*3.4,26.9,2,0,NONE,100);
            if(FrameCount%60==0)
            {
                sprintf(texttime,"%d",time);
                time--;
            }


            if (time<0 || Player1Health<=0 || Player2Health<=0 )
            {
 if (Player1Health<=0)
 player2win++;

 if (Player2Health<=0)
 Player1Win++;
 if (Player1Health!=0 && Player2Health!=0)
                round++;
                if (round<=3 && Player1Win!=2 && player2win !=2)
                {
                     time=60;
                    next_frame();
                    draw_image_ex(MapLoad,-1.5,-2,103,104,NONE,100);
                    sprintf(Round,"Round %d",round);
                    draw_text(Arista,Round,15,50,50,CENTER_X,100);
                    switch (Player1)
                    {
                    case 0 :
                        SuperPowerM=0;
                        xM=10;
                        Combot1=0;
                        etatM=Stable;
                        break;
                    case 1 :
                        etatH=Stable;
                        SuperPowerH=0;
                        xH=10;
                        Combot1=0;
                        break;
                    case 2 :
                        Combot1=0;
                        etatB=Stable;
                        SuperPowerB=0;
                        xB=10;
                        break;
                    case 3 :
                        Combot1=0;
                        etatS=Stable;
                        SuperPowerS=0;
                        xS=10;
                        break;
                    case 4 :
                        etatW=Stable;
                        Combot1=0;
                        SuperPowerW=0;
                        xW=10;
                        break;
                    }

                    switch (Player2)
                    {
                    case 0 :
                        Combot2=0;
                        etatM=Stable;
                        SuperPowerM=0;
                        xM=90;
                        break;
                    case 1 :

                        Combot2=0;
                        etatH=Stable;
                        SuperPowerH=0;
                        xH=90;
                        break;
                    case 2 :
                        Combot2=0;
                        etatB=Stable;
                        SuperPowerB=0;
                        xB=90;
                        break;
                    case 3 :
                        SuperPowerS=0;
                        xS=90;
                        Combot2=0;
                        etatS=Stable;
                        break;
                    case 4 :
                        SuperPowerW=0;
                        xW=90;
                        Combot2=0;
                        etatW=Stable;
                        break;
                    }
                    Player1Health=100;
                    Player2Health=100;
                    next_frame();
                    rest(2500);
                }
            }
            draw_text(Arista,texttime,10,50,2,CENTER_X,95);
            if (IsKeyPressed(3,RETURN) && button_press>10)
            {
                pause=1;
                PrintScreen(0);
            }
        }
        if (pause==1)
        {
            draw_image_ex(screenimage,0,0 ,100,100,NONE,50);
            for (i=0; i<5; i++)
                draw_image_ex(Pause[i],35.5,Pause_pos[i],27.4,0,NONE,100);
            draw_image_ex(Pause_cadre,35.5,Pause_pos[Pause_pos_ind],27.4,0,NONE,100);
            draw_text(Arista,"PAUSE MENU",15,50,5,CENTER_X,100);

            if (IsKeyPressed(3,DOWN)&& button_press>10)
            {
                button_press=0;
                Pause_pos_ind=(Pause_pos_ind+1)%5;
            }
            if (IsKeyPressed(3,UP)&& button_press>10)
            {
                button_press=0;
                Pause_pos_ind=(Pause_pos_ind+4)%5;
            }
            if (IsKeyPressed(3,ENTER) && button_press>10)
            {

                button_press=0;
                switch (Pause_pos_ind)
                {
                case 0 :
                {
                    pause=0;
                }
                break;
                case 1 :
                {
                    switch (Map)
                    {
                    case 0 :
                        voice_stop(sarsour);
                        voice_stop(lotfi);
                        break;
                    case 1 :
                        break;
                    case 2 :
                        break;
                    case 3 :
                        break;
                    case 4 :
                        voice_stop(thunder);
                        voice_stop(rainsound);
                        voice_stop(gameplaysound);
                        break;
                    }
                    next_frame();
                    GamePlay(Player1,Player2,Map);
                }
                break;
                case 3 :
                {
                    switch (Map)
                    {
                    case 0 :
                        voice_stop(sarsour);
                        voice_stop(lotfi);
                        break;
                    case 1 :
                        break;
                    case 2 :
                        break;
                    case 3 :
                        break;
                    case 4 :
                        voice_stop(thunder);
                        voice_stop(rainsound);
                        voice_stop(gameplaysound);
                        break;
                    }
                    while (IsKeyPressed(3,ENTER))
                        rest(1);
                    return ;
                }
                break;
                case 2 :
                {
                    ingame=1;
                    setting();
                    ingame=0;
                }
                break;
                case 4 :
                {
                    uninstall();
                    exit (0);
                }
                break;
                }
            }
        }
        button_press++;

        if (Player1Win==2)
        {
    draw_text(Arista,"Player 1 Win",15,45,45,CENTER_X,100);
        }
         if (player2win==2)
        {
    draw_text(Arista,"Player 2 Win",15,45,45,CENTER_X,100);
        }
        next_frame();
    }
    rest(2500);
    switch (Map)
    {
    case 0 :
        voice_stop(sarsour);
        voice_stop(lotfi);
        break;
    case 1 :
        break;
    case 2 :
        break;
    case 3 :
        break;
    case 4 :
        voice_stop(thunder);
        voice_stop(rainsound);
        voice_stop(gameplaysound);
        break;
    }

}




