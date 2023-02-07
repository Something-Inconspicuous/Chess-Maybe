#include "Board.hpp"
#include "LettersManip.hpp"

using namespace std;
using namespace LettersManip;

Board::Board(){
    // Create an empty board
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 8; file++){
            delete mPieces[file][rank];
            mPieces[file][rank] = NULL;
        }
    }
}

Board* Board::startingBoard(){
    // Create a board in the standard starting position
    return new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

Board::Board(string fen){
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 8; file++){
            delete mPieces[file][rank];
            mPieces[file][rank] = NULL;
        }
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


                mPieces[file][rank] = new Piece(dict[toLowerCase(c)], col);
                file++;
            }
        }
    }
}

Board::~Board(){
    // Not(~) Board function clears the board
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 8; file++){
            delete mPieces[file][rank];
            mPieces[file][rank] = NULL;
        }
    }
}

string Board::toString(){
    // renders the Board for printing
    string brd = "";
    brd = "";
    for(int rank = 7; rank >= 0; rank--){
        brd += "+ - + - + - + - + - + - + - + - +\n";
        brd += "| ";
        for (int file = 0; file < 8; file++){
            Piece* pTemp = mPieces[file][rank];

            if(pTemp != NULL){
                brd += (*pTemp).toChar();
                //brd += std::to_string(i*8 + j);
                brd += " | ";
            } else{
                brd += "  | ";
            }

            //destroy pointer, just to be safe
            pTemp = NULL;
            delete pTemp;
        }
        brd += "\n";
    }
    brd += "+ - + - + - + - + - + - + - + - +\n";
    
    return brd;
}

Piece Board::getPiece(int file, int rank){
    return *mPieces[file][rank];
}

void Board::makeMove(Move move){
    delete mPieces[move.fileTo][move.rankTo];
    
    mPieces[move.fileTo][move.rankTo] = mPieces[move.fileFrom][move.rankFrom];

    delete mPieces[move.fileFrom][move.rankFrom];
    mPieces[move.fileFrom][move.rankFrom] = NULL;
}

