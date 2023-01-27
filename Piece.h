#include "string"

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
        static const int WHITE = 8;
        static const int BLACK = 16;
        
        bool isColor(int color);

        int type();

        int color();


        //string toString();

    private:
        int mPieceValue;
};