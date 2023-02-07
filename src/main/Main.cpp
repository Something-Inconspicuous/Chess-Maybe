#include <iostream>
#include "Game.hpp"

using namespace std;

int main(){
    //all of this is testing right now
    
    Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    cout << game.boardAsString() << endl;

    string inp;
    Move move;

    cout << "start file: ";
    cin >> inp;

    move.fileFrom = std::stoi(inp);

    cout << "start rank: ";
    cin >> inp;

    move.rankFrom = std::stoi(inp);

    cout << "end file: ";
    cin >> inp;

    move.fileTo = std::stoi(inp);

    cout << "end rank: ";
    cin >> inp;

    move.rankTo = std::stoi(inp);

    
    game.makeMove(move);

    cout << "after move" << endl << game.boardAsString() << endl;



    game.~Game();
    
    return 0;
} 