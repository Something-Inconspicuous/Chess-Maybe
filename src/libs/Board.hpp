#include "Piece.hpp"
#include "Move.hpp"

class Board{
    public:
        Board();
        ~Board();

        static Board* startingBoard();

        /// @brief Create Board from a FEN string (the program assumes white to move and all castles available).
        /// 
        /// See https://ia802908.us.archive.org/26/items/pgn-standard-1994-03-12/PGN_standard_1994-03-12.txt
        /// for more information on FEN and a formal specification
        /// @param fen the FEN string to create the board from 
        Board(std::string);

        std::string toString();

        /// @brief returns the piece stored at specified index
        /// @param index {int} the index of the desired piece
        /// @return a piece object
        /// @throws {IndexOutOfBoundError} if the given index is negative or above the size of mPieces
        Piece getPiece(int);

        /// @brief sets the stored piece at a specified index to a specified piece
        /// @param index {int} the index of the desired square
        /// @param piece {Piece} the piece to place at the desired square
        void setPiece(int, Piece);

        void makeMove(Move move);

    private:
        Piece* mPieces[64] = {};
};