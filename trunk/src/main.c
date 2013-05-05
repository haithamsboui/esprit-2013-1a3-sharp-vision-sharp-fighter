#include "includes.h"

int main()
{
    int intro ;
    int state=1,choix=0;


    //intialization

    if(install())
        return 1;//ERROR

    LoadCollisionData();
    return 0;

    PlayVideo("Resources/Videos/SharpIntro.ogv");

    intro=AddVoice("Resources/Sounds/intro.wav",0);
    voice_start(intro);
    voice_set_playmode(intro, PLAYMODE_LOOP);

    while (state)
    {
        mainmenu(&choix);

        switch (choix)
        {
        case 0 :
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
            state=0;
            break;
        }

    }

    voice_stop(intro);
    uninstall();//liberation de memoire
    return 0;
}
END_OF_MAIN()

