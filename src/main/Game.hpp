#include "../../src/libs/Board.hpp"

class Game{
private:
    /// @brief the color whose turn it is to move
    Piece::color mTurnToMove;

    /// @brief a pointer to a manually allocated board
    Board* mBoard;

    /// @brief a list (as a vector) that keeps track of what squares the enemy attacks
    std::vector<Move> mAttackingMoves;

    std::vector<Board> previousBoardStates;

    /// @brief changes the turn to move to the opposite color
    void inline changeTurn();

    /// @brief checks whether a move's ending square is the same as a given file and rank
    /// @param move the move to check
    /// @param file the file of the square to check
    /// @param rank the rank of the square to check
    /// @return true if the square's end is the given square, false otherwise
    bool moveIsGoingTo(Move move, int file, int rank);

    /// @brief checks if there are *any* moves in the given vector that end at the given square
    /// @param moves the vector of moves to check
    /// @param file the file of the square to check
    /// @param rank thew rank of the square to check
    /// @return true if there are any moves that go to the given square, false otherwise
    bool moveIsGoingTo(std::vector<Move> moves, int file, int rank);

    /// @brief checks if a sqaure is attacked/defended by an enemy piece
    /// @param file the file of the square to check
    /// @param rank the rank of the square to check
    /// @return true if the square is attacked/defended by an enemy piece, false otherwise
    bool squareIsAttacked(int file, int rank);

    /// @brief finds all the moves that a piece on a square could attack/defend
    /// @param file the file of the square
    /// @param rank the rank of the square
    /// @return a list (as a vector) of all the moves 
    std::vector<Move> getAttacksFor(int file, int rank);

    /// @brief updates the value of @ref mAttackingMoves
    void updateAttackingMoves();
    
    /// @brief checks if a move is legal
    /// @param move the move to check
    /// @return true if the move is legal, false otherwise
    bool checkLegality(Move move);
public:
    const static std::string START_FEN;

    /// @brief creates a game with the board in a position from a given fen string
    /// @param fen the starting position of the game
    Game(std::string fen);
    ~Game();

    /// @brief plays a move on the board
    /// @param move {Move} the move to play
    void makeMove(Move move);

    /// @brief unmakes a move
    void unMakeMove();

    /// @brief creates a string of the board with all of the squares created in ASCII ""art""
    /// @return a string representation of the board
    std::string boardAsString();

    /// @brief creates a string of the board with all of the squares created in ASCII ""art""
    /// while showing the given moves with asterieks
    /// @param moves the moves to display as potential moves on the board
    /// @return a string representation of the board
    std::string boardAsString(std::vector<Move> moves);

    /// @brief gets the possible moves for a square based on how that piece can move
    /// @param fileFrom {int} the file to move from
    /// @param rankFrom {int} the rank to move from
    /// @return a list (as a vector) of the moves that can be played from the given square
    std::vector<Move> getMovesFor(int fileFrom, int rankFrom);

    /// @brief gets the legal moves for a square
    /// @param file the file to move from
    /// @param rank the rank to move from
    /// @return a list (as a vector) of the moves that can legally be played
    std::vector<Move> getLegalMovesFor(int file, int rank);

    /// @brief returns the letter of a file
    /// @param file {int} the internal int value of the file
    /// @return the character representing the file
    char fileToChar(int file);

    /// @brief returns the number of a rank
    /// @param rank {int} the internal int value of the rank
    /// @return the number (as a char) of the rank
    char rankToInt(int rank);

    /// @brief 
    /// @param move 
    /// @return 
    //Move stringToMove(std::string move);

    /// @brief gives the string representation of a move
    /// @param move the move to give the string representation of
    /// @return the human name of the move (Nf3, Qb3\# h4+, O-O, etc.)
    /// @note checks, checkmates, and castles have not been added yet
    std::string moveToString(Move move);

    /// @brief gives a string for multiple moves
    /// @param moves the list of moves to get as a string as a vector
    /// @return the human names for each move on it's own line
    std::string movesToString(std::vector<Move> moves);

    /// @brief converts a character to the corrosponding file int
    /// @param file the char to convert 
    /// @return the int that corrosponds to the move
    static int charToFile(char file);

    /// @brief converts a character to the corrosponding rank int
    /// @param rank the char to convert
    /// @return the int the corrosponds to the move
    static int charToRank(char rank);

    /// @brief returns a reference to the board
    /// @return the board
    Board& getBoard();

    void test();
};