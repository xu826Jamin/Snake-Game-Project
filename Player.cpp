#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPosList = new objPosArrayList();
    
    // Initialize snake at center to avoid empty list issues
    objPos headPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(headPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

void Player::getPlayerPos(objPosArrayList* &returnPosList) const
{
    // return the reference to the playerPos arrray list
    returnPosList = playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'w':
        case 'W':
            if(myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        case 's':
        case 'S':
            if(myDir != UP)
            {
                myDir = DOWN;
            }
            break;
        case 'a':
        case 'A':
            if(myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
        case 'd':
        case 'D':
            if(myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }          
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    if(myDir == STOP)
    {
        return;
    }

    objPos currentHead = playerPosList->getHeadElement();
    int newX = currentHead.pos->x;
    int newY = currentHead.pos->y;

    switch(myDir)
    {
        case UP:
            newY--;
            break;
        case DOWN:
            newY++;
            break;
        case LEFT:
            newX--;
            break;
        case RIGHT:
            newX++;
            break;
        default:
            break;
    }

    // Board wrapping
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    if(newX <= 0)
    {
        newX = boardX - 2;
    }
    else if(newX >= boardX - 1)
    {
        newX = 1;
    }

    if(newY <= 0)
    {
        newY = boardY - 2;
    }
    else if(newY >= boardY - 1)
    {
        newY = 1;
    }

    objPos newHead(newX, newY, currentHead.symbol);
    playerPosList->insertHead(newHead);
    playerPosList->removeTail();
}

// More methods to be added