/**
 * @file Piece.hpp
 * @author Something Inconspicuous <webhead220@gmail.com>
 * 
 * @brief Holds a representation of a chess piece
*/

#include "string"
#include <map>

using namespace std;

struct Piece{
    public:
        enum type{
            notype, pawn, knight, bishop, rook, queen, king
        };

        enum color{
            nocolor, white, black
        };
        
        Piece(type, color);
        Piece();

        int getType();

        int getColor();

        string toString();

    private:
        type mType;
        color mColor;
};