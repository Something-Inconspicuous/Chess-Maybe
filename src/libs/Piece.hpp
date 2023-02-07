#include "string"
#include <map>


class Piece{
    public:
        enum type{
            notype, pawn, knight, bishop, rook, queen, king
        };

        enum color{
            nocolor, white, black
        };

       
        
        Piece(type, color);
        Piece();

        type getType();

        color getColor();

        std::string toString();

        char toChar();


    private:
        type mType;
        color mColor;

        const std::map<Piece::type, char> pieceToChar = {
            {Piece::notype, '0'},
            {Piece::pawn, 'p'},
            {Piece::knight, 'n'},
            {Piece::bishop, 'b'},
            {Piece::rook, 'r'},
            {Piece::queen, 'q'},
            {Piece::king, 'k'}
        };
};