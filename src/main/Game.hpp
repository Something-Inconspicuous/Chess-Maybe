#include "../../src/libs/Board.hpp"

class Game{
private:
    /// @brief the color whose turn it is to move
    Piece::color mTurnToMove;

    /// @brief a pointer to a manually allocated board
    Board* mBoard;

    /// @brief a list (as a vector) that keeps track of what squares the enemy attacks
    std::vector<Move> mAttackingMoves;

    int mEnPassantFile;

    /// @brief white can castle short
    bool wCastSh;
    /// @brief white can castle long
    bool wCastLo;
    /// @brief black can castle short
    bool bCastSh;
    /// @brief black can castle long
    bool bCastLo;

    /// @brief changes the turn to move to the opposite color
    void cTurn();

    /// @brief changes the turn to move to the given color
    /// @param col the color to set the turn to move to
    void cTurn(const Piece::color col);

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

    /// @brief generates the moves that a ray piece could take if on a given square
    /// @param file the file of the given square
    /// @param rank the rank of the given square
    /// @param orthoganal whether or not to check for orthoganal moves
    /// @param diagonal whether or not to check for diagonal moves
    /// @return a list (as a vector) of every move found
    std::vector<Move> generateRayMoves(int file, int rank, bool orthoganal, bool diagonal);

    /// @brief creates all moves that a knight could take if on the given square
    /// @param file the file of the given square
    /// @param rank the rank of the given square
    /// @return a list (as a vector) of every move found
    std::vector<Move> generateKnightMoves(int file, int rank);

    /// @brief creates all the moves that a pawn could take if on a given square
    /// @param file the file of the given square
    /// @param rank the rank of the given square
    /// @param forward either 1 or -1; the direction that it is 'forward' for the purpose of pawn moves
    /// @return a list (as a vector) of every move found
    std::vector<Move> generatePawnMoves(int file, int rank, int forward);

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

    /// @brief gives the color whose turn it is to move
    /// @return the turn to move
    Piece::color getTurnToMove();

    /// @brief Changes the turn to move to either the given turn or the other turn if
    /// no turn is given
    /// @param col the color whose turn to change the turn to move to to
    void inline changeTurn(const Piece::color col = Piece::nocolor){
        if(col == Piece::nocolor)   this->cTurn();
        else                        this->cTurn(col);
    }

    /// @brief Checks if a given player is in check
    /// @param player the color player (white or black) to check if they're in check
    /// @return true of the given player's king is attacked, false otherwise
    bool inline playerInCheck(const Piece::color player){
        if(player == Piece::white)  return squareIsAttacked(mBoard->wKingFile, mBoard->wKingRank);
        else                        return squareIsAttacked(mBoard->bKingFile, mBoard->bKingRank);
    }

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

    /// @brief gets the legal moves for every square
    /// @return a list (as a vector) of all moves that can be legally played
    std::vector<Move> getAllLegalMoves();

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

    /// @brief teturns a pointer to the board
    /// @return the voard's memory address
    Board*& getBoardP();

    void test();
};