#include "Bot.hpp"

int Bot::evali(Board brd){
    return 0;
}

Bot::Bot(Game &game)
{
    mGame = &game;
}

Bot::~Bot(){
       
}

void Bot::makeStoredMove(){
    mGame->makeMove(mMoveToMake);
}