#include "Piece.hpp"
#include "LettersManip.hpp"
#include "string"

using namespace std;
using namespace LettersManip;

Piece::Piece(){
    mType = notype;
    mColor = nocolor;
}

Piece::Piece(type nType, color nColor){
    mType = nType;
    mColor = nColor;
}

Piece::Piece(const Piece& piece){
    mType = piece.mType;
    mColor = piece.mColor;
}

const map<Piece::type, char> Piece::pieceToChar = {
            {Piece::notype, '0'},
            {Piece::pawn, 'p'},
            {Piece::knight, 'n'},
            {Piece::bishop, 'b'},
            {Piece::rook, 'r'},
            {Piece::queen, 'q'},
            {Piece::king, 'k'}
        };

Piece::type Piece::getType(){
    if(this == NULL)
        return notype;
    return mType;
}

Piece::color Piece::getColor(){
    if(this == NULL)
        return nocolor;
    return mColor;
}

int Piece::promoteTo(type promotion){
    if(promotion == notype || promotion == pawn || promotion == king)
        return 1;
    mType = promotion;
    return 0;
}

string Piece::toString(){
    if(this == NULL){
        return "no piece";
    }

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

        //default:
        //    throw ("Invalid Piece");
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
        
        //default:
        //    throw ("Invalid Piece");
    }

    return output;
}

char Piece::toChar(){
    char chr;

    try{
        chr = pieceToChar.at(mType);
    } catch(std::exception e){
        chr = ' ';
    }
    

    if(mColor == white){
        chr = toUpperCase(chr);
    }

    return chr;
}

//Piece& Piece::operator=(const Piece &){
    
//}
