#include "vector"
#include "thread"
#include "Game.hpp"

class Bot{
    private:
        std::vector<std::thread> mThreads;

        Game* mGame;

        Board storeBoard;

        Move mMoveToMake;

        /// @brief Evaluates a given board. negative is good for black while 
        /// positive is good for white
        /// @param brd the board to evaluate the position of
        /// @return the evaluation as an int
        static int evali(Board brd);

        /// @brief Counts the difference in material. White's is positive, blacks is negative.
        /// An equal board will give a result of 0;
        /// @param brd 
        /// @return 
        static int matDif(Board brd);
    public:
        /// @brief creates the bot with that will play the given game
        /// @param game the game for the bot to play in
        Bot(Game& game);
        ~Bot();

        void makeStoredMove();

        int search(int depth);

        /// @brief Evaluates a given board. negative is good for black while
        /// positive is good for white
        /// @param board the board to evaluate
        /// @return the evaluation in points
        static float evalf(Board board);
};