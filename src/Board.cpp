#include "Board.hpp"

using namespace std;

Board::Board(){
    for(int i = 0; i < size(mPieces); i++){
        mPieces[i] = new Piece(Piece::bishop, Piece::white);
    }
}

Board::Board(string fen){

}

Board::~Board(){
    for(int i = 0; i < size(mPieces); i++){
        delete mPieces[i];
    }
}

string Board::toString(){
    string brd = "";


    for(int i = 7; i >= 0; i--){
        brd += "--------\n";
        brd += "|";

        for(int j = 0; j < 8; j++){
            brd += (*mPieces[i*8 + j]).toChar() + "|";
        }

        brd += "--------\n";
    }

    return brd;
}