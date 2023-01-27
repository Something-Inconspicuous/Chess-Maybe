#include "Piece.hpp"
#include "string"
#include <map>

//#include "exception"

using namespace std;
//using std::exception;

Piece::Piece(){
    mType = NONE;
    mColor = NONE;
}

Piece::Piece(int type, int color){
    mType = type;
    mColor = color;
}

std::map<char, int> Piece::pieceRep = {
            {'p', PAWN},
            {'n', KNIGHT},
            {'b', BISHOP},
            {'r', ROOK},
            {'q', QUEEN},
            {'k', KING}
        };
bool Piece::isColor(int color){
    if(color != WHITE && color != BLACK && color != NONE){
        throw ("recieved color value that does not exist");
    }
    return mColor == color;
}

int Piece::type(){
    return mType;
}

int Piece::color(){
    return mColor;
}

string Piece::toString(){
    string output = "";

    switch(mColor){
        case NONE:
            output += "Non-colored ";
            break;

        case WHITE:
            output += "White ";
            break;

        case BLACK:
            output += "Black ";
            break;

        default:
            throw ("Invalid Piece");
    }

    switch(mType){
        case NONE:
            output += "untyped piece";
            break;

        case PAWN:
            output += "pawn";
            break;
        
        case KNIGHT:
            output += "knight";
            break;

        case BISHOP:
            output += "bishop";
            break;
        
        case ROOK:
            output += "rook";
            break;
        
        case QUEEN:
            output += "queen";
            break;

        case KING:
            output += "king";
            break;
        
        default:
            throw ("Invalid Piece");
    }

    return output;
}

char Piece::toChar(){
    
}