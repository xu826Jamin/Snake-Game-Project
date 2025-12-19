#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    
    food.setObjPos(-1, -1, 'o');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    
    food.setObjPos(-1, -1, 'o');
}

// do you need a destructor?

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    // srand(time(NULL)); // Seeding should be done once in main, not here repeatedly.
    
    int candidateX, candidateY;
    bool overlap;

    // Try to find a valid position
    while(true)
    {
        // Generate random coordinates within the board (excluding borders)
        // Board is 0 to boardSize-1. Borders are 0 and boardSize-1.
        // Valid range: 1 to boardSize-2.
        candidateX = (rand() % (boardSizeX - 2)) + 1;
        candidateY = (rand() % (boardSizeY - 2)) + 1;
        
        overlap = false;
        // Check against blockOff list (snake body)
        for(int i = 0; i < blockOff->getSize(); i++)
        {
            objPos tempPos = blockOff->getElement(i);
            if(tempPos.pos->x == candidateX && tempPos.pos->y == candidateY)
            {
                overlap = true;
                break;
            }
        }

        if(!overlap)
        {
            food.setObjPos(candidateX, candidateY, 'o');
            break;
        }
    }
}

objPos GameMechs::getFoodPos() const
{
    return food;
}