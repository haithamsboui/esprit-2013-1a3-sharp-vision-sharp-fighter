#include "includes.h"

int main()
{
    int intro;
    int choix=0;

    //intialization

    if(install())
        return 1;//ERROR

    intro=AddVoice("Resources/Sounds/intro.wav",0);

    intromenu(intro);


    while (!close_button_pressed)
    {
        mainmenu(&choix);
        if(!close_button_pressed)
        {
            switch (choix)
            {
            case 0 :
                Arcade();
                break;
            case 1:
                versus(intro);
                break;

            case 2 :
                setting ();
                break;

            case 3 :
                voice_stop(intro);
                credit();
                voice_start(intro);
                break;

            case 4 :
                close_button_pressed=1;
                break;
            }
        }
    }

    voice_stop(intro);
    uninstall();//liberation de memoire
    return 0;
}
END_OF_MAIN()

