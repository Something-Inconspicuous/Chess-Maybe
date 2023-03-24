#ifndef BOT_HPP
#define BOT_HPP

#include "vector"
#include "thread"
#include "../main/Game.hpp"

class [[deprecated("Replaced by the Engine namespace")]] Bot{
    private:
        static const int outNumWeight;
        static const int mobilityWeight;

        static const std::map<Piece::type, int> matVal;

        /// @brief the positional score for every square for white pawns
        static const int wPawnPosVal[8][8];

        /// @brief the positional score for every square for black pawns
        static const int bPawnPosVal[8][8];

        /// @brief the positional score for every square for white knights
        static const int wKnightPosVal[8][8];

        /// @brief the positional score for every square for black knights
        static const int bKnightPosVal[8][8];

        /// @brief the positional score for every square for white bishops
        static const int wBishopPosVal[8][8];

        /// @brief the positional score for every square for black bishops
        static const int bBishopPosVal[8][8]; 

        /// @brief the positional score for every square for white rooks
        static const int wRookPosVal[8][8];

        /// @brief the positional score for every square for black bishops
        static const int bRookPosVal[8][8];

        /// @brief the positional score for every square for white queens
        static const int wQueenPosVal[8][8];

        /// @brief the positional score for every square for black queens
        static const int bQueenPosVal[8][8];

        /// @brief the positional score for every square for the white king earlier in the game
        static const int wKingBegPosVal[8][8];

        /// @brief the positional score for every square for the black king earlier in the game
        static const int bKingBegPosVal[8][8];

        /// @brief the positional score for every square for the white king later in the game
        static const int wKingEndPosVal[8][8];

        /// @brief the positional score for every square for the black king later in the game
        static const int bKingEndPosVal[8][8];

        //std::vector<std::thread> mThreads;

        Game* mGame;

        Board storeBoard;

        Move mMoveToMake;

        /// @brief searches for the best move up to a given depth
        /// @param depth the depth to search
        /// @param alpha alpha for alpha-beta pruning
        /// @param beta beta for alpha-beta pruning
        /// @return an evaluation
        /// @see https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
        int mSearch(int depth, int alpha, int beta);

        /// @brief Evaluates a given board. negative is good for black while 
        /// positive is good for white
        /// @param brd the board to evaluate the position of
        /// @param perspective the perspective to evaluate from
        /// @return the evaluation as an int
        static int evali(Game& game, const int perspective);

        /// @brief Counts the difference in material. White's is positive, black's is negative.
        /// An equal board will give a result of 0.
        /// @param brd the board to evaluate
        /// @return an int evaluation of the board's matierial difference
        static int matDif(Board brd);

        /// @brief Evaluates the difference in position. White's is positive, black's is negative.
        /// An equal board will give a result of 0.
        /// @param brd the board to evaluate
        /// @return an int evaluation of the board's positional difference
        static int posDif(Board brd);
    public:
        /// @brief creates the bot with that will play the given game
        /// @param game the game for the bot to play in
        Bot(Game& game);
        ~Bot();
        
        void makeStoredMove();

        inline Move getStoredMove(){
            return mMoveToMake;
        }

        void store();

        /// @brief searches for the best move based on how the bot will evaluate a position
        /// @param depth the depth to search at
        /// @return the evaluation of the best move found
        int search(int depth);

        /// @brief Evaluates a given board. negative is good for black while
        /// positive is good for white
        /// @param board the board to evaluate
        /// @return the evaluation in points
        static float evalf(Board board);
};
#endif