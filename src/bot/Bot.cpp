#include "Bot.hpp"
#include "math.h"
#include "algorithm"
#include "climits"
//#include "iostream"

#define forRank for(int rank = 0; rank < 8; rank++)
#define forFile for(int file = 0; file < 8; file++)

const std::map<Piece::type, int> Bot::matVal = {
    {Piece::notype, 0},
    {Piece::pawn, 100},
    {Piece::knight, 300},
    {Piece::bishop, 300},
    {Piece::rook, 500},
    {Piece::queen, 900},
    {Piece::king, 0} //king will contribute no matieral value as both players will have one
};

int Bot::mSearch(int depth, int alpha, int beta, bool isw){
    
    //std::cout << "copied board" << "\n";

    if(depth <= 0){
        //std::cout << "depth reached" << std::endl;
        return evali(mGame->getBoard());
    }
    
    Board* lastPos = new Board(mGame->getBoard());
    std::vector<Move> moves = mGame->getAllLegalMoves();

    if(moves.size() == 0){
        delete lastPos;
        if(mGame->playerInCheck(Piece::white)){
            return -INT_MAX; //mate for black
        }
        if(mGame->playerInCheck(Piece::black)){
            return INT_MAX; //mate for white
        }
        return 0; //stalemate
    } 
    int eval;
    if(isw){
        eval = -INT_MAX;
        for(Move move : moves){
            mGame->makeMove(move); //make the move
            mGame->changeTurn();
            eval = std::max(eval, mSearch(depth - 1, alpha, beta, false)); //search from there

            //unmake the move
            delete mGame->getBoardP();
            mGame->getBoard() = Board(*lastPos);

            //alpha-beta pruning stuff
            alpha = std::max(alpha, eval);
            if(eval >= beta){
                break;
            }
        }
        delete lastPos;
        return eval;
    } else{
        eval = INT_MAX;
        for(Move move : moves){
            mGame->makeMove(move); //make the move
            mGame->changeTurn();

            int eEval = mSearch(depth - 1, alpha, beta, false);

            eval = std::min(eval, eEval); //search from there

            //unmake the move
            delete mGame->getBoardP();
            mGame->getBoard() = Board(*lastPos);

            //alpha-beta pruning stuff
            beta = std::min(beta, eval);
            if(eval <= alpha){
                break;
            }
        }
        delete lastPos;
        return eval;
    }
}

int Bot::evali(Board brd)
{
    int eval = 0;

    //TODO: add evaluations
    eval += matDif(brd);

    return eval;
}

int Bot::matDif(Board brd){
    int matScore = 0;
    forRank{
        forFile{
            Piece piece = brd.getPiece(file, rank);
            if(piece.getColor() == Piece::nocolor){
                continue;
            }

            if(piece.getColor() == Piece::white){
                matScore += matVal.at(piece.getType());
            } else{
                matScore -= matVal.at(piece.getType());
            }
        }
    }

    return matScore;
}

Bot::Bot(Game& game){
    mGame = new Game(game);
    mMoveToMake = Move();
}

Bot::~Bot(){
    storeBoard = Board(); // replaces the board with an empty board

    //std::cout << "deleting bot's game: " << mGame << "\n";
    delete mGame;
    //std::cout << "bot's game deleted" << "\n";
    mGame = NULL;
    //std::cout << "bot's game nullified" << "\n";
}

void Bot::makeStoredMove(){
    mGame->makeMove(mMoveToMake);
}

void Bot::store(){
    storeBoard = Board(*mGame->getBoardP());
}

int Bot::search(int depth){
    Board lastPos(mGame->getBoard()); //precaution
    //std::cout << mGame->boardAsString() << "\n";
    bool botAsWhite = mGame->getTurnToMove() == Piece::white;

    std::vector<Move> moves = mGame->getAllLegalMoves();

    if(moves.size() == 0){
        return -INT_MAX;
    }
    Move wMoveToMake = moves.at(0);
    Move bMoveToMake = moves.at(0);
    int wBestEval = -INT_MAX;
    int bBestEval = INT_MAX;
    int curEval;

    for(Move move : moves){

        mGame->makeMove(move);

        curEval = mSearch(depth - 1, -INT_MAX, INT_MAX, mGame->getTurnToMove() == Piece::white);

        delete (mGame->getBoardP());
        mGame->getBoardP() = NULL;

        Board b = Board(lastPos);

        //mGame->getBoard() = b;
        mGame->getBoardP() = new Board(b);
        
        if(curEval > wBestEval){
            wBestEval = curEval;
            wMoveToMake = move;
        }
        if(curEval < bBestEval){
            bBestEval = curEval;
            bMoveToMake = move;
        }
        
    }
    //std::cout << "done searchinig: found best evals of " << wBestEval << " and " << bBestEval << "\n";

    if(botAsWhite){
        mMoveToMake = wMoveToMake;
        //std::cout << "return " << wBestEval << "\n";
        return wBestEval;
    } else{
        mMoveToMake = bMoveToMake;
        //std::cout << "return " << bBestEval << "\n";
        return bBestEval;
    }
    //std::cout << "how did we get here" << std::endl; 
    return 0;
}

float Bot::evalf(Board board){
    return (float)(evali(board) * 0.01);
}

