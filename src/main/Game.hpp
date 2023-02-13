#include "../../src/libs/Board.hpp"

class Game{
private:
    Piece::color mTurnToMove;
    Board* mBoard;

    void changeTurn();
public:
    /// @brief creates a game with the board in a position from a given fen string
    /// @param fen the starting position of the game
    Game(std::string);
    ~Game();

    void makeMove(Move);

    std::string boardAsString();

    std::string boardAsString(std::vector<Move> moves);

    std::vector<Move> getMovesFor(int fileFrom, int rankFrom);
};