#include "Engine.hpp"
#include "math.h"
#include "algorithm"
#include "climits"

#define forRank for(int rank = 0; rank < 8; rank++)
#define forFile for(int file = 0; file < 8; file++)

const int Engine::outNumWeight = 5;
const int Engine::mobilityWeight = 10;

const std::map<Piece::type, int> Engine::matVal = {
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

const int Engine::wPawnPosVal[8][8] = {
     0,  0,  0,  0,  0,  0,  0,  0, //rank 0
     5, 10, 10,-20,-20, 10, 10,  5,
     5, -5,-10,  0,  0,-10, -5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5,  5, 10, 25, 25, 10,  5,  5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
     0,  0,  0,  0,  0,  0,  0,  0  //rank 7
};

const int Engine::bPawnPosVal[8][8] = {
     0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
     5,  5, 10, 25, 25, 10,  5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5, -5,-10,  0,  0,-10, -5,  5,
     5, 10, 10,-20,-20, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0
};

const int Engine::wKnightPosVal[8][8] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50,
};

const int Engine::bKnightPosVal[8][8] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50,
};

const int Engine::wBishopPosVal[8][8] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
};

const int Engine::bBishopPosVal[8][8] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
};

const int Engine::wRookPosVal[8][8] = {
     0,  0,  0,  5,  5,  0,  0,  0
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     5, 10, 10, 10, 10, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0,
};

const int Engine::bRookPosVal[8][8] = {
     0,  0,  0,  0,  0,  0,  0,  0,
     5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     0,  0,  0,  5,  5,  0,  0,  0
};

const int Engine::wQueenPosVal[8][8] = {
   -20,-10,-10, -5, -5,-10,-10,-20, 
   -10,  0,  5,  0,  0,  0,  0,-10,
   -10,  5,  5,  5,  5,  5,  0,-10,
     0,  0,  5,  5,  5,  5,  0, -5,
    -5,  0,  5,  5,  5,  5,  0, -5,
   -10,  0,  5,  5,  5,  5,  0,-10,
   -10,  0,  0,  0,  0,  0,  0,-10,
   -20,-10,-10, -5, -5,-10,-10,-20,
};

const int Engine::bQueenPosVal[8][8] = {
   -20,-10,-10, -5, -5,-10,-10,-20,
   -10,  0,  0,  0,  0,  0,  0,-10,
   -10,  0,  5,  5,  5,  5,  0,-10,
    -5,  0,  5,  5,  5,  5,  0, -5,
     0,  0,  5,  5,  5,  5,  0, -5,
   -10,  5,  5,  5,  5,  5,  0,-10,
   -10,  0,  5,  0,  0,  0,  0,-10,
   -20,-10,-10, -5, -5,-10,-10,-20
};

const int Engine::wKingBegPosVal[8][8] = {
    20, 30, 10,  0,  0, 10, 30, 20,
    20, 20,  0,  0,  0,  0, 20, 20,
   -10,-20,-20,-20,-20,-20,-20,-10,
   -20,-30,-30,-40,-40,-30,-30,-20,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
};

const int Engine::bKingBegPosVal[8][8] = {
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -30,-40,-40,-50,-50,-40,-40,-30,
   -20,-30,-30,-40,-40,-30,-30,-20,
   -10,-20,-20,-20,-20,-20,-20,-10,
    20, 20,  0,  0,  0,  0, 20, 20,
    20, 30, 10,  0,  0, 10, 30, 20
};

const int Engine::wKingEndPosVal[8][8] = {
   -50,-30,-30,-30,-30,-30,-30,-50,
   -30,-30,  0,  0,  0,  0,-30,-30,
   -30,-10, 20, 30, 30, 20,-10,-30,
   -30,-10, 30, 40, 40, 30,-10,-30,
   -30,-10, 30, 40, 40, 30,-10,-30,
   -30,-10, 20, 30, 30, 20,-10,-30,
   -30,-20,-10,  0,  0,-10,-20,-30,
   -50,-40,-30,-20,-20,-30,-40,-50,

};

const int Engine::bKingEndPosVal[8][8] = {
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


int Engine::privates::mSearch(Game game, int depth, int alpha, int beta, const int startingDepth){
    if(depth <= 0){
        int eval = game.getTurnToMove() == Piece::white ? 1 : -1 * evali(game);
        return eval;
    }


    std::vector<Move> moves = game.getAllLegalMoves();
    //std::cout << moves.size() << "\n";
    //std::cout << game.getTurnToMove() << "\n";

    if(moves.size() == 0){
        if(game.playerInCheck(game.getTurnToMove())){
            return -INT_MAX + (startingDepth - depth); //checkmate
        }
        return 0; //stalemate
    } 
    
    Board* lastPos = new Board(game.getBoard());
    
    for(Move move : moves){
        game.makeMove(move);
        game.changeTurn();

        int eval = -mSearch(game, depth - 1, -beta, -alpha, startingDepth);

        //unmake move
        delete game.getBoardP();
        game.getBoardP() = new Board(*lastPos);
        game.changeTurn();

        if(eval >= beta){
            delete lastPos;
            return beta;
        }
        alpha = std::max(eval, alpha);
    }
    delete lastPos;
    return alpha;
}

int Engine::evali(Game& game){
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
    constexpr long double matFrac = 1.0L/7800.0L; // 1/7800, or 1/the starting material
    const float endgamePercent = endgameWeight * matFrac; //get the endgame-ness as a percent

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

    return eval;
}

int Engine::search(Game& game, int depth, Move& moveToStore){
    Board lastPos(game.getBoard()); //precaution
    //std::cout << game.boardAsString() << "\n";
    bool botAsWhite = game.getTurnToMove() == Piece::white;

    std::vector<Move> moves = game.getAllLegalMoves();

    if(moves.size() == 0){
        return -INT_MAX;
    }
    Move moveToMake = moves.at(0);
    //Move bMoveToMake = moves.at(0);
    int alpha = -INT_MAX;
    int beta = INT_MAX;
    int curEval;

    for(Move move : moves){
        game.changeTurn(botAsWhite ? Piece::white : Piece::black);

        //std::string str = game.moveToString(move);

        game.makeMove(move);
        game.changeTurn();
        //std::cout << game.boardAsString() << "\n";
        //std::cout << game.getAllLegalMoves().size() << "\n";

        //curEval = -mSearch(depth - 1, -INT_MAX, INT_MAX); //accurate results for every move; slower
        curEval = -mSearch(game, depth - 1, -beta, -alpha, depth); //inaccurate results for moves with worse evals that are searched after a move with better eval; much, much faster
        //NOTE - this does not change what move is found, as the bot picks the first one with the best eval it has found
        //so the second option if identical when looking for just the best move and not any other lines, and is much faster.+
        //std::cout << "found that move " << str << " has eval " << curEval <<"\n";

        delete (game.getBoardP());
        game.getBoardP() = NULL;

        Board b = Board(lastPos);

        //game.getBoard() = b;
        game.getBoardP() = new Board(b);
        game.changeTurn();
        
        if(curEval > alpha){
            alpha = curEval;
            moveToMake = move;
        }
        //if(curEval < beta){
        //    beta = curEval;
            //bMoveToMake = move;
        //}

        if(alpha == INT_MAX - 1){
            //mate in 1 has been found!
            break;
        }
        
    }
    //std::cout << "done searchinig: found best evals of " << wBestEval << " and " << bBestEval << "\n";

    if(botAsWhite){
        moveToStore = moveToMake;
        //std::cout << "return " << wBestEval << "\n";
        return alpha;
    } else{
        moveToStore = moveToMake;
        //std::cout << "return " << bBestEval << "\n";
        return -alpha;
    }
    //std::cout << "how did we get here" << std::endl; 
    return 0;
}
