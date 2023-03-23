#include "Bot.hpp"
#include "math.h"
#include "algorithm"
#include "climits"
//#include "iostream"

#define forRank for(int rank = 0; rank < 8; rank++)
#define forFile for(int file = 0; file < 8; file++)

const int Bot::outNumWeight = 5;
const int Bot::mobilityWeight = 10;

const std::map<Piece::type, int> Bot::matVal = {
    {Piece::notype, 0},
    {Piece::pawn, 100},
    {Piece::knight, 320},
    {Piece::bishop, 330},
    {Piece::rook, 500},
    {Piece::queen, 900},
    {Piece::king, 0} //king will contribute no matieral value as both players will have one
};

//SECTION - positional tables

//NOTE - the positional tables look reversed by rank because white's back is at 0, while the table's bottom is at 7

const int Bot::wPawnPosVal[8][8] = {
     0,  0,  0,  0,  0,  0,  0,  0, //rank 0
     5, 10, 10,-20,-20, 10, 10,  5,
     5, -5,-10,  0,  0,-10, -5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5,  5, 10, 25, 25, 10,  5,  5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
     0,  0,  0,  0,  0,  0,  0,  0  //rank 7
};

const int Bot::bPawnPosVal[8][8] = {
     0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
     5,  5, 10, 25, 25, 10,  5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5, -5,-10,  0,  0,-10, -5,  5,
     5, 10, 10,-20,-20, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0
};

const int Bot::wKnightPosVal[8][8] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50,
};

const int Bot::bKnightPosVal[8][8] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50,
};

const int Bot::wBishopPosVal[8][8] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
};

const int Bot::bBishopPosVal[8][8] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
};

const int Bot::wRookPosVal[8][8] = {
     0,  0,  0,  5,  5,  0,  0,  0
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     5, 10, 10, 10, 10, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0,
};

const int Bot::bRookPosVal[8][8] = {
     0,  0,  0,  0,  0,  0,  0,  0,
     5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     0,  0,  0,  5,  5,  0,  0,  0
};

const int Bot::wQueenPosVal[8][8] = {
   -20,-10,-10, -5, -5,-10,-10,-20, 
   -10,  0,  5,  0,  0,  0,  0,-10,
   -10,  5,  5,  5,  5,  5,  0,-10,
     0,  0,  5,  5,  5,  5,  0, -5,
    -5,  0,  5,  5,  5,  5,  0, -5,
   -10,  0,  5,  5,  5,  5,  0,-10,
   -10,  0,  0,  0,  0,  0,  0,-10,
   -20,-10,-10, -5, -5,-10,-10,-20,
};

const int Bot::bQueenPosVal[8][8] = {
   -20,-10,-10, -5, -5,-10,-10,-20,
   -10,  0,  0,  0,  0,  0,  0,-10,
   -10,  0,  5,  5,  5,  5,  0,-10,
    -5,  0,  5,  5,  5,  5,  0, -5,
     0,  0,  5,  5,  5,  5,  0, -5,
   -10,  5,  5,  5,  5,  5,  0,-10,
   -10,  0,  5,  0,  0,  0,  0,-10,
   -20,-10,-10, -5, -5,-10,-10,-20
};

const int Bot::wKingBegPosVal[8][8] = {
    20, 30, 10,  0,  0, 10, 30, 20,
    20, 20,  0,  0,  0,  0, 20, 20,
   -10,-20,-20,-20,-20,-20,-20,-10,
   -20,-30,-30,-40,-40,-30,-30,-20,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
};

const int Bot::bKingBegPosVal[8][8] = {
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -20,-30,-30,-40,-40,-30,-30,-20,
   -10,-20,-20,-20,-20,-20,-20,-10,
    20, 20,  0,  0,  0,  0, 20, 20,
    20, 30, 10,  0,  0, 10, 30, 20
};

const int Bot::wKingEndPosVal[8][8] = {
   -50,-30,-30,-30,-30,-30,-30,-50,
   -30,-30,  0,  0,  0,  0,-30,-30,
   -30,-10, 20, 30, 30, 20,-10,-30,
   -30,-10, 30, 40, 40, 30,-10,-30,
   -30,-10, 30, 40, 40, 30,-10,-30,
   -30,-10, 20, 30, 30, 20,-10,-30,
   -30,-20,-10,  0,  0,-10,-20,-30,
   -50,-40,-30,-20,-20,-30,-40,-50,

};

const int Bot::bKingEndPosVal[8][8] = {
   -50,-40,-30,-20,-20,-30,-40,-50,
   -30,-20,-10,  0,  0,-10,-20,-30,
   -30,-10, 20, 30, 30, 20,-10,-30,
   -30,-10, 30, 40, 40, 30,-10,-30,
   -30,-10, 30, 40, 40, 30,-10,-30,
   -30,-10, 20, 30, 30, 20,-10,-30,
   -30,-30,  0,  0,  0,  0,-30,-30,
   -50,-30,-30,-30,-30,-30,-30,-50
};
//!SECTION

int Bot::mSearch(int depth, int alpha, int beta){
    if(depth <= 0){
        int eval = evali(*mGame, mGame->getTurnToMove() == Piece::white ? 1 : -1);
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

int Bot::evali(Game& game, const int perspective){
    Board& brd = game.getBoard();
    int eval = 0;
    int endgameWeight = 7800; //starting material
    int matScore = 0;
    int onScore = 0; //exists to encourage having more pieces over stronger pieces
    int posScore = 0;

    forRank{
        forFile{ 
            Piece piece = brd.getPiece(file, rank);
            
            if(piece.getColor() == Piece::nocolor){
                continue;
            }

            const bool isWhite = piece.getColor() == Piece::white;

            const int matValOfPiece = matVal.at(piece.getType());

            //record material
            if(isWhite){
                matScore += matValOfPiece;
                onScore += outNumWeight;
            } else{
                matScore -= matValOfPiece;
                onScore -= outNumWeight;
            }

            endgameWeight -= matValOfPiece;

            //TODO: position
            

            switch (piece.getType()){
                case Piece::pawn:
                    //TODO: check for doubled and linked pawns, adjust score accordingly
                    if(isWhite){
                        posScore += wPawnPosVal[file][rank];
                    } else{
                        posScore -= bPawnPosVal[file][rank];
                    }
                    break;

                case Piece::knight:
                    if(isWhite){
                        posScore += wKnightPosVal[file][rank];
                    } else{
                        posScore -= bKnightPosVal[file][rank];
                    }
                    break;

                case Piece::bishop:
                    if(isWhite){
                        posScore += wBishopPosVal[file][rank];
                    } else{
                        posScore -= bBishopPosVal[file][rank];
                    }
                    break;

                case Piece::rook:
                    if(isWhite){
                        posScore += wRookPosVal[file][rank];
                    } else{
                        posScore -= bRookPosVal[file][rank];
                    }
                    break;
                    
                case Piece::queen:
                    if(isWhite){
                        posScore += wQueenPosVal[file][rank];
                    } else{
                        posScore -= wQueenPosVal[file][rank];
                    }
                    break;
                
                default:
                    break;
            }
        }
    }

    //material
    eval += matScore + onScore;

    //king position
    const float endgamePercent = endgameWeight * 0.000128205f; //get the endgame-ness as a percent
    //the .00128... number is 1/7800 btw

    const float beggamePercent = 1 - endgamePercent; //the opposate of the endgame-ness

    posScore += (int)(wKingBegPosVal[brd.wKingFile][brd.bKingRank] * beggamePercent + wKingEndPosVal[brd.wKingFile][brd.wKingRank] * endgamePercent);
    posScore -= (int)(bKingBegPosVal[brd.bKingFile][brd.bKingRank] * beggamePercent + bKingEndPosVal[brd.bKingFile][brd.bKingRank] * endgamePercent);

    //position
    eval += posScore;

    //mobility
    eval += game.getAllLegalMoves().size() * mobilityWeight; //white's mobility
    game.changeTurn();
    eval -= game.getAllLegalMoves().size() * mobilityWeight; //black's mobility
    game.changeTurn();

    return perspective * eval;
}

int Bot::posDif(Board brd){
    int posScore = 0;

    forRank{
        forFile{
            Piece piece = brd.getPiece(file, rank);
            if(piece.getColor() == Piece::nocolor){
                continue;
            }

            const bool isWhite = piece.getColor() == Piece::white;

            switch (piece.getType()){
                case Piece::pawn:
                    if(isWhite){
                        posScore += wPawnPosVal[file][rank];
                    } else{
                        posScore -= bPawnPosVal[file][rank];
                    }
                    break;

                case Piece::knight:
                    if(isWhite){
                        posScore += wKnightPosVal[file][rank];
                    } else{
                        posScore -= bKnightPosVal[file][rank];
                    }
                    break;

                case Piece::bishop:
                    if(isWhite){
                        posScore += wBishopPosVal[file][rank];
                    } else{
                        posScore -= bBishopPosVal[file][rank];
                    }
                    break;

                case Piece::rook:
                    if(isWhite){
                        posScore += wRookPosVal[file][rank];
                    } else{
                        posScore -= bRookPosVal[file][rank];
                    }
                    break;
                    
                case Piece::queen:
                    if(isWhite){
                        posScore += wQueenPosVal[file][rank];
                    } else{
                        posScore -= wQueenPosVal[file][rank];
                    }
                    break;
                
                default:
                    break;
            }
        }
    }

    return posScore;
}

Bot::Bot(Game &game)
{
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
