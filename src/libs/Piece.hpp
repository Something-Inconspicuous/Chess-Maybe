/**
 * @file Piece.hpp
 * @author Something Inconspicuous <webhead220@gmail.com>
 * 
 * @brief Holds a representation of a chess piece
*/

#include "string"
#include <map>

using namespace std;

class Piece{
    public:
        enum type{
            notype, pawn, knight, bishop, rook, queen, king
        };

        enum color{
            nocolor, white, black
        };

        const std::map<type, char> pieceToChar = {
            {notype, '0'},
            {pawn, 'p'},
            {knight, 'n'},
            {bishop, 'b'},
            {rook, 'r'},
            {queen, 'q'},
            {king, 'k'}
        };
        
        Piece(type, color);
        Piece();

        int getType();

        int getColor();

        string toString();

        char toChar();

    private:
        type mType;
        color mColor;
};