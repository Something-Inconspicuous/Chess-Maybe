#include "Piece.hpp"
#include "Move.hpp"
#include "vector"

class Board{
    public:
        /// @brief the file the white king is on; used for quick lookups
        int wKingFile;

        /// @brief the rank the white king is on; used for quick lookups
        int wKingRank;

        /// @brief the file the black king is on; used for quick lookups
        int bKingFile;

        /// @brief the rank the black king is on; used for quick lookups
        int bKingRank;

        Board();
        ~Board();

        static Board* startingBoard();

        /// @brief Create Board from a FEN string (the program assumes white to move and all castles available).
        /// 
        /// See https://ia802908.us.archive.org/26/items/pgn-standard-1994-03-12/PGN_standard_1994-03-12.txt
        /// for more information on FEN and a formal specification
        /// @param fen the FEN string to create the board from 
        Board(std::string);

        /// @brief Copy constructer, copies the pieces on the board
        /// @param board the board to copy
        Board(const Board& board);

        Board clone();
        
        /// @brief the rank and file offsets to move a direction
        /// @param direction which direction to get the offset of
        /// @param isRank whether or not the offset is for the file or rank (0 for file, 1 for rank)
        static const int offsets[8][2];

        /// @brief returns the board in text form
        /// @return the board in string form
        std::string toString();

        /// @brief returns the board in string form, showing all of the given moves
        /// @param moves {vector<Move>} the moves to display
        /// @return the board in string form
        std::string toString(std::vector<Move> moves);

        /// @brief returns the piece stored at specified index
        /// @param file {int} the file of the desired piece
        /// @param rank {int} the rank of the desired piece
        /// @return a piece object
        /// @throws @ref invalid_argument if the given index is negative or above the size of mPieces
        Piece getPiece(int file, int rank);

        /// @brief returns a reference to the piece at a given square
        /// @param file the file of the given square
        /// @param rank the rank of the given square
        /// @return a reference to the piece at the given square
        /// @see #pat(int, int)
        inline Piece& at(const int file, const int rank){
            return *mPieces[file][rank];
        }

        /// @brief Returns a reference to a pointer to the piece at a given square.
        /// Sounds dumb but it makes it modifyable (board.pat(1, 1) = NULL works, for example)
        /// @param file the file of the given square
        /// @param rank the rank of the given square
        /// @return a reference to a pointer to the piece
        inline Piece*& pat(const int file, const int rank){
            return mPieces[file][rank];
        }

        /// @brief moves a piece on the board
        /// @param move Move the move to play
        /// @throws @ref invalid argument if the given move has invalid starting or ending squares
        void makeMove(Move move);

    private:
        Piece* mPieces[8][8] = {};

        //enum direction{
        //    right, left, up, down, up_right, up_left, down_right, down_left 
        //};
};