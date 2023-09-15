#include <iostream>
#include "string.h"
#include "algorithm"
#include "thread"
#include "../libs/LettersManip.hpp"
#include "Game.hpp"
#include "../engine/Engine.hpp"

//#define BOT

using namespace std;

inline void clrscr() {
    //for(int i = 0; i < 50; i++){
    //    std::cout<<"\n";
    //}
    //std::cout<<std::"\n";
    std::cout << "\033[H\033[2J" << std::endl;

}

Move getMove(Game& game){
    getMove:
    clrscr();
    cout << game.boardAsString();
    cout << (game.getTurnToMove() == Piece::white ? "White" : "Black") << " to move." << "\n";

    string inp;
    Move move;

    cout << "Starting square: ";
    cin >> inp;
    if(inp == "STOP"){
        exit(EXIT_SUCCESS);
    }

    move.fileFrom = game.charToFile(inp[0]);
    move.rankFrom = game.charToRank(inp[1]);

    if(move.fileFrom == -1 || move.rankFrom == -1){
        cout << "invalid square" << "\n";
        std::this_thread::sleep_for(1000ms);
        goto getMove;
    }
    
    
    //show the legal moves
    vector<Move> moves = game.getLegalMovesFor(move.fileFrom, move.rankFrom);
    if(moves.size() == 0){
        cout << "no legal moves" << "\n";
        std::this_thread::sleep_for(1000ms);
        goto getMove;
    }
    clrscr();
    cout<< game.boardAsString(moves) << "\n";

    cout << "Ending square: ";
    cin >> inp;
    if(inp == "STOP"){
        exit(EXIT_SUCCESS);
    }

    move.fileTo = game.charToFile(inp[0]);
    move.rankTo = game.charToRank(inp[1]);

    if(move.fileTo == -1 || move.rankTo == -1){
        cout << "invalid square" << "\n";
        goto getMove;
    }

    return move;
}

bool playerTurn(Game& game, const Piece::color playerColor){
    game.changeTurn(playerColor);

    cout << (playerColor == Piece::white ? "white" : "black") << " to move" << "\n";

    vector<Move> allLegalMoves = game.getAllLegalMoves();
    if(allLegalMoves.size() == 0){
        if(game.playerInCheck(playerColor))
            cout << "Checkmate!" << "\n";
        else
            cout << "Stalemate!" << "\n";
        return true;
    }

    //get a move from the user
    getAMove:
    Move move;
    bool moveIsValid = false;
    move = getMove(game);
    moveIsValid = std::find(allLegalMoves.begin(), allLegalMoves.end(), move) != allLegalMoves.end();
    if(!moveIsValid){
        cout << "illigal move" << "\n";
        goto getAMove;
    }


    //make the move
    game.makeMove(move);
    
    cout << game.boardAsString() << "\n";
    return false;
}

// Hi people -Your biggest fan, Cow
int main(int argc, char* argv[]){

    if(argc > 2){
        printf("%s [-bw|-bb]", argv[0]);
        return 1;
    }

    bool botIsActive;
    bool botIsWhite;

    //if -bw is passed to command line, bot is white
    if ((argc == 2) && _stricmp(argv[1], "-bw") == 0){
        botIsWhite = 1;
        botIsActive = 1;
    } else if ((argc == 2) && _stricmp(argv[1], "-bb") == 0){
        botIsWhite = 0;
        botIsActive = 1;
    } else {
        botIsActive = 0;
    }

    if(botIsActive) {


        gameStartBot:

        Game* game = new Game(Game::START_FEN);

        bool gameIsGoing = true;
        Piece::color turn = Piece::black;
        //start as black so that it is changed to white for the first move
        do{
            turn = turn == Piece::white ? Piece::black : Piece::white;

            if((turn == Piece::white) == botIsWhite){
                Move move;
                Engine::search(*game, 4, move);

                game->makeMove(move);

                vector<Move> allLegalMoves = game->getAllLegalMoves();
                if(allLegalMoves.size() == 0){
                    if(game->playerInCheck(turn))
                        cout << "Checkmate!" << "\n";
                    else
                        cout << "Stalemate!" << "\n";
                    gameIsGoing = false;
                }

                turn = game->getTurnToMove();
            } else {
                if(playerTurn(*game, turn)){
                    gameIsGoing = false;
                }
            }
        } while (gameIsGoing);

        delete game;

    } else {
        //clrscr();
        //all of this is testing right now
        gameStart:

        /*
            Dear Developer,
            I am writing this note to you today to announce my love for you. 
            Please excuse this long comment in the middle of your code base, but I think this is exremely  romantic.
            To be more specific, I wanted to go on a coffe date with you at starbucks.
            I've been eyeing this code base since you've started (clearly) and now I am being brave enough to show how much I love your thick codebase.
            The indents in this codebase add such a nice curve to your code and looking at the overview on the side of vs code is so attractive.
            From, your biggest fan, @x86Cow
        */
        /*
        * what the f***
        */

        //Game game("rnbqkbnr/pppppppp/7r/7K/8/8/PPPPPPPP/RNBQ1BNR");
        Game game(Game::START_FEN);
        cout << game.boardAsString() << "\n";

        //vector<Move> ms = game.getLegalMovesFor(7, 4);
        //cout << game.boardAsString(ms);
        //return 0;
        
        bool gameIsGoing = true;
        Piece::color turn = Piece::black;
        //start as black so that it is changed to white for the first move
        do{
            turn = turn == Piece::white ? Piece::black : Piece::white;

            bool gameDidEnd = playerTurn(game, turn);

            if(gameDidEnd){
                gameIsGoing = false;
            }
        } while (gameIsGoing);

        playAgain:
        string inp;
        cout << "Play again? ";
        cin >> inp;
        //trim the string
        while(inp[0] == ' '){
            inp.replace(0, 1, "");
        }
        inp[0] = LettersManip::toLowerCase(inp[0]);

        if(inp[0] == 'y'){
            goto gameStart;
        } else if(inp[0] == 'n'){
            return 0;
        } else{
            cout << "invalid input" << "\n";
            goto playAgain;
        }

    }
} 