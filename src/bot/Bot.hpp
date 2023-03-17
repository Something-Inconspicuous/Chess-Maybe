#include "vector"
#include "thread"
#include "../main/Game.hpp"

class Bot{
    private:
        static const std::map<Piece::type, int> matVal;

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
        static int evali(Board brd, const int perspective);

        /// @brief Counts the difference in material. White's is positive, blacks is negative.
        /// An equal board will give a result of 0;
        /// @param brd the board to evaluate
        /// @return an int evaluation of the board's matierial difference
        static int matDif(Board brd);
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