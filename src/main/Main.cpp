#include <iostream>
#include "algorithm"
#include "../libs/LettersManip.hpp"
#include "Game.hpp"

using namespace std;

inline void clrscr() {
    //for(int i = 0; i < 50; i++){
    //    std::cout<<"\n";
    //}
    //std::cout<<std::endl;
    std::cout << "\033[H\033[2J" << std::endl;
}

Move getMove(Game& game){
    getMove:
    clrscr();
    cout << game.boardAsString();

    string inp;
    char c;
    Move move;

    cout << "start file: ";
    cin >> inp;

    try{
        move.fileFrom = std::stoi(inp);
    } catch(invalid_argument){
        c = inp[0];

        move.fileFrom = Game::charToFile(c);
    }
    

    cout << "start rank: ";
    cin >> inp;

    c = inp[0];
    move.rankFrom = Game::charToRank(c);
    
    //show the legal moves
    vector<Move> moves = game.getLegalMovesFor(move.fileFrom, move.rankFrom);
    if(moves.size() == 0){
        cout << "no legal moves" <<endl;
        goto getMove;
    }
    clrscr();
    cout<< game.boardAsString(moves) <<endl;

    cout << "end file: ";
    cin >> inp;

    try{
        move.fileTo = std::stoi(inp);
    } catch(invalid_argument){
        c = inp[0];
        move.fileTo = Game::charToFile(c);
        //cout<<move.fileTo<<endl;
    }

    cout << "end rank: ";
    cin >> inp;
    
    c = inp[0];
    move.rankTo = Game::charToRank(c);

    return move;
}

bool playerTurn(Game& game, const Piece::color playerColor){
    game.changeTurn(playerColor);

    cout << (playerColor == Piece::white ? "white" : "black") << " to move" << endl;

    vector<Move> allLegalMoves = game.getAllLegalMoves();
    if(allLegalMoves.size() == 0){
        if(game.playerInCheck(playerColor))
            cout << "Checkmate!" << endl;
        else
            cout << "Stalemate!" << endl;
        return true;
    }

    //get a move from the user
    getAMove:
    Move move;
    bool moveIsValid = false;
    move = getMove(game);
    moveIsValid = std::find(allLegalMoves.begin(), allLegalMoves.end(), move) != allLegalMoves.end();
    if(!moveIsValid){
        cout << "illigal move" << endl;
        goto getAMove;
    }


    //make the move
    game.makeMove(move);
    
    cout << game.boardAsString() << endl;
    return false;
}

// Hi people -Your biggest fan, Cow
int main(){
    //clrscr();
    //all of this is testing right now
    gameStart:
    //Game game("rnbqkbnr/pppppppp/7r/7K/8/8/PPPPPPPP/RNBQ1BNR");
    Game game(Game::START_FEN);
    cout << game.boardAsString() << endl;

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
        cout << "invalid input" << endl;
        goto playAgain;
    }
} 