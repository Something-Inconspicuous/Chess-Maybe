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

int Bot::mSearch(int depth, int alpha, int beta){
    if(depth <= 0){
        int eval = evali(mGame->getBoard(), mGame->getTurnToMove() == Piece::white ? 1 : -1);
        return eval;
    }


    std::vector<Move> moves = mGame->getAllLegalMoves();
    //std::cout << moves.size() << "\n";
    //std::cout << mGame->getTurnToMove() << "\n";

    if(moves.size() == 0){
        if(mGame->playerInCheck(mGame->getTurnToMove())){
            return -INT_MAX; //checkmate
        }
        return 0; //stalemate
    } 
    
    Board* lastPos = new Board(mGame->getBoard());
    
    for(Move move : moves){
        mGame->makeMove(move);
        mGame->changeTurn();

        int eval = -mSearch(depth - 1, -beta, -alpha);

        //unmake move
        delete mGame->getBoardP();
        mGame->getBoardP() = new Board(*lastPos);
        mGame->changeTurn();

        if(eval >= beta){
            delete lastPos;
            return beta;
        }
        alpha = std::max(eval, alpha);
    }
    delete lastPos;
    return alpha;
}



int Bot::evali(Board brd, const int perspective)
{
    int eval = 0;

    //TODO: add evaluations
    eval += matDif(brd);

    return perspective * eval;
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
    Move moveToMake = moves.at(0);
    //Move bMoveToMake = moves.at(0);
    int alpha = -INT_MAX;
    int beta = INT_MAX;
    int curEval;

    for(Move move : moves){
        mGame->changeTurn(botAsWhite ? Piece::white : Piece::black);

        std::string str = mGame->moveToString(move);

        mGame->makeMove(move);
        mGame->changeTurn();
        //std::cout << mGame->boardAsString() << "\n";
        //std::cout << mGame->getAllLegalMoves().size() << "\n";

        //curEval = -mSearch(depth - 1, -INT_MAX, INT_MAX); //accurate results for every move; slower
        curEval = -mSearch(depth - 1, -beta, -alpha); //inaccurate results for moves with worse evals that are searched after a move with better eval; much, much faster
        //NOTE - this does not change what move is found, as the bot picks the first one with the best eval it has found
        //so the second option if identical when looking for just the best move and not any other lines, and is much faster.+
        //std::cout << "found that move " << str << " has eval " << curEval <<"\n";

        delete (mGame->getBoardP());
        mGame->getBoardP() = NULL;

        Board b = Board(lastPos);

        //mGame->getBoard() = b;
        mGame->getBoardP() = new Board(b);
        mGame->changeTurn();
        
        if(curEval > alpha){
            alpha = curEval;
            moveToMake = move;
        }
        //if(curEval < beta){
        //    beta = curEval;
            //bMoveToMake = move;
        //}

        if(alpha == INT_MAX){
            //mate has been found!
            break;
        }
        
    }
    //std::cout << "done searchinig: found best evals of " << wBestEval << " and " << bBestEval << "\n";

    if(botAsWhite){
        mMoveToMake = moveToMake;
        //std::cout << "return " << wBestEval << "\n";
        return alpha;
    } else{
        mMoveToMake = moveToMake;
        //std::cout << "return " << bBestEval << "\n";
        return -alpha;
    }
    //std::cout << "how did we get here" << std::endl; 
    return 0;
}
