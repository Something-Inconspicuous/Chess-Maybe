#include "Piece.h"
//#include "exception"

using namespace std;
//using std::exception;

Piece::Piece(){
    mPieceValue = 0;
}

Piece::Piece(int type, int color){
    mPieceValue = type + color;
}

bool Piece::isColor(int color){
    if(color != WHITE && color != BLACK && color != NONE){
        throw ("recieved color value that does not exist");
    }
    return false;
}

int Piece::type(){
    return mPieceValue < WHITE ? mPieceValue : (mPieceValue < BLACK ? mPieceValue - WHITE : mPieceValue - BLACK);
}

int Piece::color(){
    return mPieceValue - type();
}

/*string Piece::toString(){
    string output = "";

    switch(color()){
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

    switch(type()){
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
*/