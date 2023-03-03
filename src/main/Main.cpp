#include <iostream>
#include "Game.hpp"

#define clrscr() {for(int i = 0; i < 50; i++){std::cout<<std::endl;}};

using namespace std;

Move getMove(){
    string inp;
    char c;
    Move move;

    cout << "start file: ";
    cin >> inp;

    try{
        move.fileFrom = std::stoi(inp);
    } catch(invalid_argument){
        c = inp[0];

        move.fileFrom = Game::charToFile(c);
    }
    

    cout << "start rank: ";
    cin >> inp;

    c = inp[0];
    move.rankFrom = Game::charToRank(c);
    //cout<<move.rankFrom<<endl;
    

    cout << "end file: ";
    cin >> inp;

    try{
        move.fileTo = std::stoi(inp);
    } catch(invalid_argument){
        c = inp[0];
        move.fileTo = Game::charToFile(c);
        //cout<<move.fileTo<<endl;
    }

    cout << "end rank: ";
    cin >> inp;
    
    c = inp[0];
    move.rankTo = Game::charToRank(c);

    return move;
}

// Hi people -Your biggest fan, Cow
int main(){
    clrscr();
    //all of this is testing right now
    
    //Game game("rnbqkbnr/pppppppp/7r/7K/8/8/PPPPPPPP/RNBQ1BNR");
    Game game(Game::START_FEN);
    cout << game.boardAsString() << endl;

    //Move move = getMove();
    
    //game.makeMove(move);

    std::vector<Move> moves = game.getLegalMovesFor(1, 0);
    //cout << ":" << game.checkLegality(moves.at(0)) << endl;

    cout<<game.movesToString(moves)<<endl;

    cout << "after move" << endl << game.boardAsString(moves) << endl;

    //cout<<"test"<<endl;
    

    //game.~Game();
    
    return 0;
} 