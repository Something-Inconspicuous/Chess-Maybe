#include <iostream>
#include "Game.hpp"

using namespace std;

void printMoves(vector<Move> moves){
    if(moves.size() == 0){
        cout << "no moves found" << endl;
    } else{
        for (Move m : moves){
            cout << m.fileFrom << ":" << m.rankFrom
            << "->"
            << m.fileTo << ":" << m.rankTo << endl;
        }
        
    }
}

Move getMove(){
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

    return move;
}

int main(){
    //all of this is testing right now
    
    Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    cout << game.boardAsString() << endl;

    

    
    //Move move = getMove();
    
    //game.makeMove(move);

    printMoves(game.getMovesFor(1, 0));


    //cout << "after move" << endl << game.boardAsString() << endl;

    //cout<<"test"<<endl;



    //game.~Game();
    
    return 0;
} 