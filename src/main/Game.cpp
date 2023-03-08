#include "Game.hpp"
#include "../libs/LettersManip.hpp"
#include "stdexcept"
#include "algorithm"

#define forRank for(int rank = 0; rank < 8; rank++)
#define forFile for(int file = 0; file < 8; file++)

using namespace std;

const string Game::START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

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

bool Game::moveIsGoingTo(Move move, int file, int rank){
    return move.fileTo == file && move.rankTo == rank;
}

bool Game::moveIsGoingTo(vector<Move> moves, int file, int rank){
    return std::find_if(moves.begin(), moves.end(), 
        [this, file, rank](Move move){ return this->moveIsGoingTo(move, file, rank); }
    ) != moves.end();
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

    if(fileFrom < 0 || fileFrom > 7)
        throw invalid_argument(std::string(__FILE__) + "." + std::to_string(__LINE__) + ": fileFrom: Index out of bounds");
    if(rankFrom < 0 || rankFrom > 7)
        throw invalid_argument(std::string(__FILE__) + "." + std::to_string(__LINE__) + ": rankFrom: Index out of bounds");
    
    std::vector<Move> moves;
    
    Piece::type pieceType = (mBoard->getPiece(fileFrom, rankFrom).getType());
    //cout<<mBoard->getPiece(fileFrom, rankFrom).toString()<<endl;

    if(mBoard->getPiece(fileFrom, rankFrom).getColor() == mTurnToMove){
        if(mBoard->getPiece(fileFrom, rankFrom).getColor() != Piece::nocolor && pieceType != Piece::notype){
            //"ray" piece moves
            if(pieceType == Piece::queen || pieceType == Piece::rook || pieceType == Piece::bishop){
                vector<Move> rayMoves = generateRayMoves(fileFrom, rankFrom, pieceType != Piece::bishop, pieceType != Piece::rook);
                moves.insert(moves.end(), rayMoves.begin(), rayMoves.end());
            } else

            //knight moves
            if(pieceType == Piece::knight){
                vector<Move> knightMoves = generateKnightMoves(fileFrom, rankFrom);
                moves.insert(moves.end(), knightMoves.begin(), knightMoves.end());
            } else

            //pawn moves
            if(pieceType == Piece::pawn){
                vector<Move> pawnMoves = generatePawnMoves(fileFrom, rankFrom, 
                    mBoard->getPiece(fileFrom, rankFrom).getColor() == Piece::white ? 1 : -1);
                moves.insert(moves.end(), pawnMoves.begin(), pawnMoves.end());
            } else
            
            //king moves
            if(pieceType == Piece::king){
                for(int dir = 0; dir < 8; dir++){
                    int file = fileFrom + Board::offsets[dir][0];
                    int rank = rankFrom + Board::offsets[dir][1];
                    if(rank < 0 || rank > 7 || file < 0 || file > 7)
                        continue;

                    if(mBoard->getPiece(file, rank).getColor()
                    != mTurnToMove){
                        Move move;
                        move.fileFrom = fileFrom;
                        move.rankFrom = rankFrom;
                        move.fileTo = file;
                        move.rankTo = rank;

                        moves.push_back(move);
                    }
                }
            }
        }
    }

    return moves;
}

std::vector<Move> Game::generateRayMoves(int file, int rank, bool orthoganal, bool diagonal){
    vector<Move> moves;
 
    //when looking for orthoganal directions, we need to look at the first four, else, skip them
    int dirStart = orthoganal ? 0 : 4;

    //when looking for diagonal directions, we need to look at the last four, else, skip them
    int dirEnd = diagonal ? 8 : 4;

    for(int dir = dirStart; dir < dirEnd; dir++){
        for(int dist = 1; dist < 8; dist++){
            int fileTo = file + dist*Board::offsets[dir][0];
            int rankTo = rank + dist*Board::offsets[dir][1];

            if(fileTo > 7 || fileTo < 0 || rankTo > 7 || rankTo < 0){
                //we have hit the edge the board, so move to the next direction
                break;
            }

            if(mBoard->getPiece(file, rank).getColor() == mTurnToMove){
                //there is one of our pieces blocking us, so move too the next direction
                break;
            }

            Move move;

            move.fileFrom = file;
            move.rankFrom = rank;
            move.fileTo = fileTo;
            move.rankTo = rankTo;

            moves.push_back(move);

            if(mBoard->getPiece(file, rank).getColor() != Piece::nocolor){
                //we are capturing a piece, move to the next direction
                break;
            }
        }
    }
    return moves;
}

std::vector<Move> Game::generateKnightMoves(int file, int rank){
    vector<Move> moves;
    for(int longDir = 0; longDir < 4; longDir++){
        for(int shortDir = 0; shortDir < 2; shortDir++){
            int fileToCheck = file + Board::offsets[longDir][0]*2 + Board::offsets[longDir < 2 ? shortDir + 2 : shortDir][0];
            int rankToCheck = rank + Board::offsets[longDir][1]*2 + Board::offsets[longDir < 2 ? shortDir + 2 : shortDir][1];

            if(fileToCheck > 7 || fileToCheck < 0 || rankToCheck > 7 || rankToCheck < 0)
                continue;
            
            if(mBoard->getPiece(fileToCheck, rankToCheck).getColor() != mTurnToMove){
                Move move;
                move.fileFrom = file;
                move.fileTo = fileToCheck;
                move.rankFrom = rank;
                move.rankTo = rankToCheck;
                moves.push_back(move);
            }
        }
    }
    return moves;
}

std::vector<Move> Game::generatePawnMoves(int file, int rank, int forward){
    if(forward != 1 && forward != -1)
        throw invalid_argument(std::string(__FILE__) + "." + std::to_string(__LINE__) + ": forward cannot be " + (forward + "") + " must be 1 or -1");

    vector<Move> moves;
    if(mBoard->getPiece(file, rank + forward).getColor() == Piece::nocolor){
        //there is no piece in front of the pawn, so it can move forward
        Move move;

        move.fileFrom = file;
        move.rankFrom = rank;
        move.fileTo = file;
        move.rankTo = rank + forward;

        moves.push_back(move);
        
        if(rank == (forward == 1 ? 1 : 6)){
            if(mBoard->getPiece(file, rank + forward*2).getColor() == Piece::nocolor){
                //there is no piece in front of the pawn, so it can move forward
                Move move;

                move.fileFrom = file;
                move.rankFrom = rank;
                move.fileTo = file;
                move.rankTo = rank + forward*2;

                moves.push_back(move);
                
            }
        }
        
    }

    //checks diagonals
    if(file + 1 <= 7){
        if(mBoard->getPiece(file + 1, rank + forward).getColor() ==
        (mTurnToMove == Piece::white ? Piece::black : Piece::white)){
            Move move;
            move.fileFrom = file;
            move.rankFrom = rank;
            move.fileTo = file + 1;
            move.rankTo = rank + forward;

            moves.push_back(move);
        }
    }

    if(file - 1 >= 0){
        if(mBoard->getPiece(file - 1, rank + forward).getColor() ==
        (mTurnToMove == Piece::white ? Piece::black : Piece::white)){
            Move move;
            move.fileFrom = file;
            move.rankFrom = rank;
            move.fileTo = file - 1;
            move.rankTo = rank + forward;

            moves.push_back(move);
        }
    }
    return moves;
}

std::vector<Move> Game::getLegalMovesFor(int file, int rank){
    vector<Move> moves;
    moves = getMovesFor(file, rank);
    vector<Move> filteredMoves;

    //remove illegal moves
    for(Move move : moves){
        //cout<<"checking legality for move " << moveToString(move)<<endl;
        bool isLegal = this->checkLegality(move);
        //cout << isLegal <<endl;
        if(isLegal){
            //cout << __FILE__ << "."<<__LINE__ << endl;
            filteredMoves.push_back(move);
        }
    }

    return filteredMoves;
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

bool Game::squareIsAttacked(int file, int rank){
    //return moveIsGoingTo(mAttackingMoves, file, rank);

    //checking for orthoganal attacks from rooks and queens
    for(int dir = 0; dir < 4; dir++){
        for(int dist = 0; dist < 8; dist++){
            int fileToCheck = file + dist*Board::offsets[dir][0];
            int rankToCheck = rank + dist*Board::offsets[dir][1];

            if(fileToCheck < 0 || fileToCheck > 7 || rankToCheck < 0 || rankToCheck > 7)
                break;

            if(mBoard->getPiece(fileToCheck, rankToCheck).getColor() == mTurnToMove)
                break;

            Piece::type pieceType = mBoard->getPiece(fileToCheck, rankToCheck).getType();
            if(pieceType == Piece::queen || pieceType == Piece::rook)
                return true;
        }
    }

    //checking for diagonal attacks from bishops and queens
    for(int dir = 4; dir < 8; dir++){
        for(int dist = 0; dist < 8; dist++){
            int fileToCheck = file + dist*Board::offsets[dir][0];
            int rankToCheck = rank + dist*Board::offsets[dir][1];

            if(fileToCheck < 0 || fileToCheck > 7 || rankToCheck < 0 || rankToCheck > 7)
                break;
                
            if(mBoard->getPiece(fileToCheck, rankToCheck).getColor() == mTurnToMove)
                break;

            Piece::type pieceType = mBoard->getPiece(fileToCheck, rankToCheck).getType();
            if(pieceType == Piece::queen || pieceType == Piece::bishop)
                return true;
        }
    }

    //checking for knight attacks
    for(int longDir = 0; longDir < 4; longDir++){
        for(int shortDir = 0; shortDir < 2; shortDir++){
            int fileToCheck = file + Board::offsets[longDir][0]*2 + Board::offsets[longDir < 2 ? shortDir + 2 : shortDir][0];
            int rankToCheck = rank + Board::offsets[longDir][1]*2 + Board::offsets[longDir < 2 ? shortDir + 2 : shortDir][1];

            if(fileToCheck > 7 || fileToCheck < 0 || rankToCheck > 7 || rankToCheck < 0)
                continue;
            
            if(mBoard->getPiece(fileToCheck, rankToCheck).getColor() != mTurnToMove &&
                mBoard->getPiece(fileToCheck, rankToCheck).getType() == Piece::knight){
                return true;
            }
        }
    }

    //checking for pawn attacks
    if(file + 1 <= 7){
        int forward = mTurnToMove == Piece::white ? 1 : -1;

        //check if there could be a pawn behind the square
        if(rank - forward >= 0 && rank - forward <= 7)
            if(mBoard->getPiece(file + 1, rank - forward).getColor() != mTurnToMove &&
                mBoard->getPiece(file + 1, rank - forward).getType() == Piece::pawn)
                return true;
    }
    if(file - 1 >= 0){
        int forward = mTurnToMove == Piece::white ? 1 : -1;

        //check if there could be a pawn behind the square
        if(rank - forward >= 0 && rank - forward <= 7)
            if(mBoard->getPiece(file - 1, rank - forward).getColor() != mTurnToMove &&
                mBoard->getPiece(file - 1, rank - forward).getType() == Piece::pawn)
                return true;
    }

    //checking for king attacks
    for(int dir = 0; dir < 8; dir++){
        int fileToCheck = file + Board::offsets[dir][0];
        int rankToCheck = rank + Board::offsets[dir][1];

        if(fileToCheck < 0 || fileToCheck > 7 || rankToCheck < 0 || rankToCheck > 7)
            continue;

        if(mBoard->getPiece(fileToCheck, rankToCheck).getColor() != mTurnToMove &&
            mBoard->getPiece(fileToCheck, rankToCheck).getType() == Piece::king)
            return true;
    }

    //if no piece that could attack the square was found, return false;
    return false;
}

vector<Move> Game::getAttacksFor(int fileFrom, int rankFrom){
    std::vector<Move> moves;
    
    Piece::type pieceType = (mBoard->getPiece(fileFrom, rankFrom).getType());
    //cout<<mBoard->getPiece(fileFrom, rankFrom).toString()<<endl;
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

                    //no longer check if our piece is blocking

                    Move move;
                    move.fileFrom = fileFrom;
                    move.rankFrom = rankFrom;
                    move.fileTo = file;
                    move.rankTo = rank;
                    moves.push_back(move);
                    if(mBoard->getPiece(file, rank).getColor() != Piece::nocolor){
                        //if there is a piece, it will block further defense, so stop here
                        break;
                    }
                }
            }
        } //else
        //knight moves
        if(pieceType == Piece::knight){
            //knight moves are unchanged
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
            //checks diagonals only
            if(fileFrom + 1 <= 7){
                Move move;
                move.fileFrom = fileFrom;
                move.rankFrom = rankFrom;
                move.fileTo = fileFrom + 1;
                move.rankTo = rankFrom + forward;

                moves.push_back(move);
            }

            if(fileFrom - 1 >= 0){
                Move move;
                move.fileFrom = fileFrom;
                move.rankFrom = rankFrom;
                move.fileTo = fileFrom - 1;
                move.rankTo = rankFrom + forward;

                moves.push_back(move);
                
            }
        }
    }

    return moves; 
}

void Game::updateAttackingMoves(){
    forRank{
        forFile{
            vector<Move> movesToAdd = getAttacksFor(file, rank);

            mAttackingMoves.insert(mAttackingMoves.end(), movesToAdd.begin(), movesToAdd.end());
        }
    }
}

bool Game::checkLegality(Move move){
    int* kingFile = mTurnToMove == Piece::white ? &mBoard->wKingFile : &mBoard->bKingFile;
    int* kingRank = mTurnToMove == Piece::white ? &mBoard->wKingRank : &mBoard->bKingRank;

    Board storeBoard(*mBoard);

    mBoard->makeMove(move);


    //TODO: I have an idea for checking for checks
    //later this should be changed so that it checks if the king can be attacked by checking
    //all moves that another piece could make
    //so for example, from the king we check if there are any knights at knight opposition
    //forRank{
    //    forFile{
    //        if(mBoard->getPiece(file, rank).getColor() == mTurnToMove)
    //            continue;
    //        
    //        vector<Move> moves = getAttacksFor(file, rank);
    //        bool kingInCheck = moveIsGoingTo(moves, *kingFile, *kingRank);
    //        if(kingInCheck){
    //            delete mBoard;
    //            mBoard = new Board(storeBoard);
    //            return false;
    //        }
    //    }
    //}
    if(squareIsAttacked(*kingFile, *kingRank)){
        delete mBoard;
        mBoard = new Board(storeBoard);
        return false;
    }
    delete mBoard;
    mBoard = new Board(storeBoard);
    return true;
}