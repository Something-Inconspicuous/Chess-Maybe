#include <iostream>
#include "Game.hpp"

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
    //all of this is testing right now
    
    Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    cout << game.boardAsString() << endl;

    Move move = getMove();
    
    game.makeMove(move);

    std::vector<Move> moves = game.getMovesFor(1, 1);

    cout<<game.movesToString(moves)<<endl;

    cout << "after move" << endl << game.boardAsString() << endl;

    //cout<<"test"<<endl;


    //game.~Game();
    
    return 0;
} 