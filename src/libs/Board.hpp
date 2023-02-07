#include "Piece.hpp"
#include "Move.hpp"
#include "vector"

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
        /// @param file {int} the file of the desired piece
        /// @param rank {int} the rank of the desired piece
        /// @return a piece object
        /// @throws {IndexOutOfBoundError} if the given index is negative or above the size of mPieces
        Piece getPiece(int file, int rank);

        void makeMove(Move move);

        std::vector<Move> getMovesFor(int file, int rank);

    private:
        Piece* mPieces[8][8] = {};

        //enum direction{
        //    right, left, up, down, up_right, up_left, down_right, down_left 
        //};
        

        /// @brief the rank and file offsets to move a direction
        /// @param direction which direction to get the offset of
        /// @param isRank whether or not the offset is for the file or rank (0 for file, 1 for rank)
        const int offsets[8][2] = {
            {1, 0}, //right
            {-1, 0}, //left
            {0, 1}, //up
            {0, -1}, //down
            {1, 1}, //up-right
            {-1, 1}, //up-left
            {1, -1}, //down-right
            {-1, -1}, //down-left
        };
};