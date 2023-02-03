#include <iostream>
#include "Game.hpp"

using namespace std;

int main(){
    //all of this is testing right now
    
    Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    cout << game.boardAsString() << endl;

    string inp;
    Move move;

    cout << "start square: ";
    cin >> inp;

    move.squareFrom = std::stoi(inp);

    cout << "end square: ";
    cin >> inp;

    move.squareTo = std::stoi(inp);

    
    game.makeMove(move);

    cout << "after move" << endl << game.boardAsString() << endl;



    game.~Game();
    
    return 0;
} 