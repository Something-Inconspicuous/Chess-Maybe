#include "Game.hpp"
#include <iostream>

using namespace std;

Game::Game(string fen){
    mBoard = new Board(fen);
}

Game::~Game(){
    delete mBoard;
}

void Game::changeTurn(){
    mTurnToMove = mTurnToMove == Piece::white ? Piece::black : Piece::white;
}

void Game::makeMove(Move move){
    mBoard->makeMove(move);
}

string Game::boardAsString(){
    return mBoard->toString();
}