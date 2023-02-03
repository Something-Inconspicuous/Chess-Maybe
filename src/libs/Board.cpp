#include "Board.hpp"
#include "LettersManip.hpp"

using namespace std;
using namespace LettersManip;

const int directionAddValues[8] = {};

Board::Board(){
    // Create an empty board
    for(int i = 0; i < (sizeof(mPieces)/sizeof(Piece)); i++){
        mPieces[i] = NULL;
    }
}

Board* Board::startingBoard(){
    // Create a board in the standard starting position
    return new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

Board::Board(string fen){
    for(int i = 0; i < (sizeof(mPieces)/sizeof(Piece)); i++){
        mPieces[i] = NULL;
    }

    map<char, Piece::type> dict = {
        {'p', Piece::pawn},
        {'n', Piece::knight},
        {'b', Piece::bishop},
        {'r', Piece::rook},
        {'q', Piece::queen},
        {'k', Piece::king}
    };

    int rank = 7, file = 0;

    for(int i = 0; i < fen.length(); i++){
        char c = fen[i];

        if(c == '/'){
            rank--;
            file = 0;
        } else{
            if(c >= '0' && c <= '9'){
                file += c - '0';
            } else{
                Piece::color col = c >= 'A' && c <= 'Z' ? Piece::white : Piece::black;

                mPieces[rank*8 + file] = new Piece(dict[toLowerCase(c)], col);
                file++;
            }
        }
    }
}

Board::~Board(){
    // Not(~) Board function clears the board
    for(int i = 0; i < (sizeof(mPieces)/sizeof(Piece)); i++){
        delete mPieces[i];
    }
}

string Board::toString(){
    // renders the Board for printing
    string brd = "";
    brd = "";
    for(int i = 7; i >= 0; i--){
        brd += "-----------------\n";
        brd += "|";
        for (int j = 0; j < 8; j++){
            Piece* pTemp = mPieces[i*8 + j];

            if(pTemp != NULL){
                brd += (*pTemp).toChar();
                //brd += std::to_string(i*8 + j);
                brd += "|";
            } else{
                brd += " |";
            }

            //destroy pointer, just to be safe
            pTemp = NULL;
            delete pTemp;
        }
        brd += "\n";
    }
    brd += "-----------------\n";
    
    return brd;
}

Piece Board::getPiece(int index){
    return *mPieces[index];
}

void Board::setPiece(int index, Piece piece){
    delete mPieces[index];

    mPieces[index] = &piece;
}

void Board::makeMove(Move move){
    delete mPieces[move.squareTo];
    
    mPieces[move.squareTo] = mPieces[move.squareFrom];

    delete mPieces[move.squareFrom];
    mPieces[move.squareFrom] = NULL;
}

