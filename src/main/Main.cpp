#include <iostream>
#include "Game.hpp"

using namespace std;

void printMoves(vector<Move> moves, Game game){
    if(moves.size() == 0){
        cout << "no moves found" << endl;
    } else{
        for (Move m : moves){
            //cout<<m.fileFrom<<":"<<m.rankFrom<<"->"<<m.fileTo<<":"<<m.rankTo<<endl;
            cout << game.moveToString(m) << endl;
        }
        
    }
}

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

int main(){
    //all of this is testing right now
    
    Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    cout << game.boardAsString() << endl;

    Move move = getMove();
    
    game.makeMove(move);

    std::vector<Move> moves = game.getMovesFor(1, 0);

    printMoves(moves, game);

    cout << "after move" << endl << game.boardAsString() << endl;

    cout << game.getBoard().getPiece(2, 2).toString() << endl;
    cout << game.getBoard().getPiece(1, 0).toString() << endl;

    //cout<<"test"<<endl;


    //game.~Game();
    
    return 0;
} 