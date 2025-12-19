#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "ScreenDrawer.h"

void drawScreenActual(Player* pl, GameMechs* gm) {
    // the makefile requires a ScreenDrawer output so this is here i guess ¯\_(ツ)_/¯
    // this probably shouldn't be abstracted

    bool drawn;

    objPosArrayList* playerBody = nullptr;
    pl->getPlayerPos(playerBody);
    objPos food = gm->getFoodPos();

    int boardX = gm->getBoardSizeX();
    int boardY = gm->getBoardSizeY();

    MacUILib_printf("Score: %d\n", gm->getScore());
    // debug line
    // MacUILib_printf("Player Pos: %d, %d\n", playerBody->getHeadElement().pos->x, playerBody->getHeadElement().pos->y);

    // create a buffer, add all our characters, then use one print call since io is expensive
    // remember to allocate size+1 because we need a \0
    char* buffer = (char*)malloc(sizeof(char) * (boardX + 1) * boardY + 1);
    if (buffer == NULL) {
        return;
    }
    int bufferIndex = 0;

    for (int y = 0; y < boardY; y++)
    {
        for (int x = 0; x < boardX; x++)
        {
            bool drawn = false;

            // draw snake + its body if it occupies this cell
            for (int k = 0; k < playerBody->getSize(); k++)
            {
                objPos thisSeg = playerBody->getElement(k);
                if (thisSeg.pos->x == x && thisSeg.pos->y == y)
                {
                    buffer[bufferIndex++] = thisSeg.symbol;
                    drawn = true;
                    break;
                }
            }
            if (drawn) continue;

            // border
            if (y == 0 || y == boardY - 1 || x == 0 || x == boardX - 1)
            {
                buffer[bufferIndex++] = '#';
            }
            // food
            else if (x == food.pos->x && y == food.pos->y)
            {
                buffer[bufferIndex++] = food.symbol;
            }
            // space
            else
            {
                buffer[bufferIndex++] = ' ';
            }
        }
        // finish all rows with a newline
        buffer[bufferIndex++] = '\n';
    }
    // null terminator at very end
    buffer[bufferIndex] = '\0';

    MacUILib_printf(buffer);

    // make sure we free the allocated memory
    free(buffer);
}