#include "Game.hpp"
#include "../libs/LettersManip.hpp"

using namespace std;

Game::Game(string fen){
    mTurnToMove = Piece::white;
    mBoard = new Board(fen);
}

Game::~Game(){
    delete mBoard;
}


void Game::changeTurn(){
    mTurnToMove = mTurnToMove == Piece::white ? Piece::black : Piece::white;
}

void Game::makeMove(Move move){
    mBoard->makeMove(move);
}

string Game::boardAsString(){
    return mBoard->toString();
}

string Game::boardAsString(std::vector<Move> moves){
    return mBoard->toString(moves);
}

std::vector<Move> Game::getMovesFor(int fileFrom, int rankFrom){
    
    std::vector<Move> moves;
    
    Piece::type pieceType = (mBoard->getPiece(fileFrom, rankFrom).getType());
    //cout<<mBoard->getPiece(fileFrom, rankFrom).toString()<<endl;

    if(mBoard->getPiece(fileFrom, rankFrom).getColor() == mTurnToMove){
        if(mBoard->getPiece(fileFrom, rankFrom).getColor() != Piece::nocolor && pieceType != Piece::notype){
            //"ray" piece moves
            if(pieceType == Piece::queen || pieceType == Piece::rook || pieceType == Piece::bishop){
                //if the piece is a bishop, we only look at the last 4 diagonal directions
                int dirStart = pieceType == Piece::bishop ? 4 : 0;
                //if the piece is a rook, we only look at the first 4 orthoganal directions
                int dirEnd = pieceType == Piece::rook ? 4 : 8;

                for(int dir = dirStart; dir < dirEnd; dir++){
                    for(int dist = 1; dist < 8; dist++){
                        int file = fileFrom + dist*Board::offsets[dir][0];
                        int rank = rankFrom + dist*Board::offsets[dir][1];

                        if(file > 7 || file < 0 || rank > 7 || rank < 0){
                            //we have hit the edge the board, so move to the next direction
                            break;
                        }

                        if(mBoard->getPiece(file, rank).getColor() == mTurnToMove){
                            //there is one of our pieces blocking us, so move too the next direction
                            break;
                        }

                        Move move;

                        move.fileFrom = fileFrom;
                        move.rankFrom = rankFrom;
                        move.fileTo = file;
                        move.rankTo = rank;

                        moves.push_back(move);

                        if(mBoard->getPiece(file, rank).getColor() != Piece::nocolor){
                            //we are capturing a piece, move to the next direction
                            break;
                        }
                    }
                }
            } //else
            //knight moves
            if(pieceType == Piece::knight){
                for(int longDir = 0; longDir < 4; longDir++){
                    for(int shortDir = 0; shortDir < 2; shortDir++){
                        int fileToCheck = fileFrom + Board::offsets[longDir][0]*2 + Board::offsets[longDir < 2 ? shortDir + 2 : shortDir][0];
                        int rankToCheck = rankFrom + Board::offsets[longDir][1]*2 + Board::offsets[longDir < 2 ? shortDir + 2 : shortDir][1];

                        if(fileToCheck > 7 || fileToCheck < 0 || rankToCheck > 7 || rankToCheck < 0){
                            //square is outside board
                        } else{
                            if(mBoard->getPiece(fileToCheck, rankToCheck).getColor() != mTurnToMove){
                                Move move;
                                move.fileFrom = fileFrom;
                                move.fileTo = fileToCheck;
                                move.rankFrom = rankFrom;
                                move.rankTo = rankToCheck;
                                moves.push_back(move);
                            }
                        }
                    }
                }
            } else

            if(pieceType == Piece::pawn){
                int forward = mTurnToMove == Piece::white ? 1 : -1;

                if(mBoard->getPiece(fileFrom, rankFrom + forward).getColor() == Piece::nocolor){
                    //there is no piece in front of the pawn, so it can move forward
                    Move move;

                    move.fileFrom = fileFrom;
                    move.rankFrom = rankFrom;
                    move.fileTo = fileFrom;
                    move.rankTo = rankFrom + forward;

                    moves.push_back(move);
                    
                    //if(rankFrom == (foward == 1 ? 1 : 6))
                    if(mBoard->getPiece(fileFrom, rankFrom + forward*2).getColor() == Piece::nocolor){
                        //there is no piece in front of the pawn, so it can move forward
                        Move move;

                        move.fileFrom = fileFrom;
                        move.rankFrom = rankFrom;
                        move.fileTo = fileFrom;
                        move.rankTo = rankFrom + forward*2;

                        moves.push_back(move);
                        
                    }
                }
            }
        }
    }

    return moves;
}


//representation methods

char Game::fileToChar(int file){
    if(file < 0 || file > 7){
        return '0';
    }

    return 'a' + file;
}

char Game::rankToInt(int rank){
    return '0' + rank + 1;
}

int Game::charToFile(char file){
    if(file < 'a' || file > 'h'){
        return -1;
    }
    return (int)(file - 'a');
}

int Game::charToRank(char rank){
    return (int)(rank - '0') - 1;
}

std::string Game::moveToString(Move move){
    std::string str = "";
    
    Piece pieceMoving = mBoard->getPiece(move.fileFrom, move.rankFrom);

    if(pieceMoving.getType() != Piece::pawn){
        str += LettersManip::toUpperCase((Piece::pieceToChar.at(pieceMoving.getType())));
    }

    //if the move is a capture, mark it as such
    if(mBoard->getPiece(move.fileTo, move.rankTo).getType() != Piece::notype){
        if(pieceMoving.getType() == Piece::pawn){
            str += fileToChar(move.fileFrom);
        }
        str += "x";
    }

    str += fileToChar(move.fileTo);
    str += rankToInt(move.rankTo);
    
    return str;
}

std::string Game::movesToString(std::vector<Move> moves){
    if(moves.size() == 0){
        return "no moves found";
    }

    std::string str = "";
    for(Move move : moves){
        str += this->moveToString(move) + "\n";
    }

    return str;
}

Board& Game::getBoard(){
    return *mBoard;
}