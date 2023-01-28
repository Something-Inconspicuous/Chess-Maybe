#include "Piece.hpp"
#include "string"
#include <map>

//#include "exception"

using namespace std;
//using std::exception;

Piece::Piece(){
    mType = notype;
    mColor = nocolor;
}

Piece::Piece(type nType, color nColor){
    mType = nType;
    mColor = nColor;
}

int Piece::getType(){
    return mType;
}

int Piece::getColor(){
    return mColor;
}

string Piece::toString(){
    string output = "";

    switch(mColor){
        case nocolor:
            output += "Non-colored ";
            break;

        case white:
            output += "White ";
            break;

        case black:
            output += "Black ";
            break;

        default:
            throw ("Invalid Piece");
    }

    switch(mType){
        case notype:
            output += "untyped piece";
            break;

        case pawn:
            output += "pawn";
            break;
        
        case knight:
            output += "knight";
            break;

        case bishop:
            output += "bishop";
            break;
        
        case rook:
            output += "rook";
            break;
        
        case queen:
            output += "queen";
            break;

        case king:
            output += "king";
            break;
        
        default:
            throw ("Invalid Piece");
    }

    return output;
}

char Piece::toChar(){
    char chr = pieceToChar.at(mType);

    if(mColor == white){
        chr = uppercase(chr);
    } else if(mColor == black){
        //cool, is already lowercase
    } else{
        chr = '0';
    }

    return chr;
}

char Piece::uppercase(char c){
    return c -('a'-'A');
}