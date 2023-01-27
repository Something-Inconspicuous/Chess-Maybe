#include "string"
#include <map>

using namespace std;

class Piece{
    public:
        Piece(int, int);
        Piece();

        //piece types
        static const int NONE = 0;
        static const int PAWN = 1;
        static const int KNIGHT = 2;
        static const int BISHOP = 3;
        static const int ROOK = 4;
        static const int QUEEN = 5;
        static const int KING = 6;
        static const int WHITE = 1;
        static const int BLACK = 2;

        static const std::map<char, int> pieceRep;
        
        bool isColor(int);

        int type();

        int color();


        string toString();

        char toChar();

    private:
        int mType;
        int mColor;
};