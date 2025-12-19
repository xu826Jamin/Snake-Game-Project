#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "ScreenDrawer.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs* gm;
Player* pl;

int main(void)
{

    Initialize();

    while(gm->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    srand(time(NULL));

    // these two variables are 2 characters because you need to type them a million times 
    // our two 'main' objects
    gm = new GameMechs();
    pl = new Player(gm);
    
    objPosArrayList* plBody = nullptr;
    pl->getPlayerPos(plBody);
    gm->generateFood(plBody);
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        gm->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    pl->updatePlayerDir();
    pl->movePlayer();
    
    gm->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    
    drawScreenActual(pl, gm);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    
    if(gm->getLoseFlagStatus())
    {
        int score = gm->getScore();
        MacUILib_printf("Game Over! Your final score was: %d\n", score);
        // integer division for inverse modulus effect
        int score_norm = score / 5;
        // custom message at end of game
        switch (score_norm) {
            // impossible to die with score < 5
            case 1:
                MacUILib_printf("Nice try...\n");
                break;
            case 2:
                MacUILib_printf("Good run!\n");
                break;
            case 3:
                MacUILib_printf("Great job!\n");
                break;
            case 4:
                MacUILib_printf("WOW! You're a pro!\n");
                break;
            case 5:
                MacUILib_printf("INSANE! You're too good at this...\n");
                break;
            // activates for score >=30
            default:
                MacUILib_printf("You're so good, the developers didn't even add flavor text for your score!\n");
                break;
        }
    }
    delete pl;
    delete gm;

    MacUILib_uninit();
}
