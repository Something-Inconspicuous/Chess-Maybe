#include "Piece.hpp"

using namespace std;

class Board{
    public:
        Board();
        ~Board();

        Board(string);

        string toString();

        Piece getPiece(int);

        const int directionAddValues[8] = {};
    private:
        Piece* mPieces[64] = {};
};