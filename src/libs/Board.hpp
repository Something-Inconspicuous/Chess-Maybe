#include "Piece.hpp"

using namespace std;

class Board{
    public:
        Board();
        ~Board();

        Board(string);

        string toString();

        /// @brief returns a pointer to the piece stored at specified index
        /// @param index {int} the index of the desired piece
        /// @return a pointer to a piece object
        /// @throws {IndexOutOfBoundError} if the given index is negative or above the size of mPieces
        Piece* getPiece(int);

        const int directionAddValues[8] = {};
    private:
        Piece* mPieces[64] = {};
};