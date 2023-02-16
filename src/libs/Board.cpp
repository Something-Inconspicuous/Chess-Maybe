#include "Board.hpp"
#include "LettersManip.hpp"

using namespace std;
using namespace LettersManip;

const int Board::offsets[8][2] = {
            {1, 0}, //right
            {-1, 0}, //left
            {0, 1}, //up
            {0, -1}, //down
            {1, 1}, //up-right
            {-1, 1}, //up-left
            {1, -1}, //down-right
            {-1, -1}, //down-left
        };

Board::Board(){
    // Create an empty board
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 8; file++){
            delete mPieces[file][rank];
            mPieces[file][rank] = NULL;
        }
    }
}

Board* Board::startingBoard(){
    // Create a board in the standard starting position
    return new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

Board::Board(string fen){
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 8; file++){
            delete mPieces[file][rank];
            mPieces[file][rank] = NULL;
        }
    }

    map<char, Piece::type> dict = {
        {'p', Piece::pawn},
        {'n', Piece::knight},
        {'b', Piece::bishop},
        {'r', Piece::rook},
        {'q', Piece::queen},
        {'k', Piece::king}
    };

    int rank = 7, file = 0;

    for(int i = 0; i < fen.length(); i++){
        char c = fen[i];

        if(c == '/'){
            rank--;
            file = 0;
        } else{
            if(c >= '0' && c <= '9'){
                file += c - '0';
            } else{
                Piece::color col = c >= 'A' && c <= 'Z' ? Piece::white : Piece::black;


                mPieces[file][rank] = new Piece(dict[toLowerCase(c)], col);
                file++;
            }
        }
    }
}

Board::~Board(){
    // Not(~) Board function clears the board
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 8; file++){
            delete mPieces[file][rank];
            mPieces[file][rank] = NULL;
        }
    }
}

string Board::toString(){
    // renders the Board for printing
    string brd = "";
    brd = "";
    for(int rank = 7; rank >= 0; rank--){
        brd += std::to_string(rank + 1) + " - + - + - + - + - + - + - + - +\n";
        brd += "| ";
        for (int file = 0; file < 8; file++){
            if(mPieces[file][rank] != NULL){
                brd += mPieces[file][rank]->toChar();
                //brd += std::to_string(i*8 + j);
                brd += " | ";
            } else{
                brd += "  | ";
            }
        }
        brd += "\n";
    }
    brd += "a - b - c - d - e - f - g - h - +\n";
    
    return brd;
}

string Board::toString(vector<Move> moves){
    auto indexOf = [moves](int f, int r){
        for(int i = 0; i < moves.size(); i++){
            Move m = moves.at(i);

            if(m.rankTo == r && m.fileTo == f){
                return i;
            }    
        }
        return -1;
    };

    if(moves.size() == 0){
        return this->toString();
    }

    // renders the Board for printing
    string brd = "";
    brd = "";
    for(int rank = 7; rank >= 0; rank--){
        brd += std::to_string(rank + 1) + " - + - + - + - + - + - + - + - +\n";
        brd += "| ";
        for (int file = 0; file < 8; file++){
            if(mPieces[file][rank] != NULL){
                brd += mPieces[file][rank]->toChar();
                
                if(file == moves.at(0).fileFrom && rank == moves.at(0).rankFrom){
                    brd += "@| ";
                } else{
                    if(indexOf(file, rank) != -1){
                        brd += "*| ";
                    } else{
                        brd += " | "; 
                    }
                }           
            } else{

                if(indexOf(file, rank) != -1){
                    brd += "* | ";
                } else{
                    brd += "  | ";
                }
            }
        }
        brd += "\n";
    }
    brd += "a - b - c - d - e - f - g - h - +\n";
    
    return brd;
}

Piece Board::getPiece(int file, int rank){
    if(file < 0 || file > 7)
        throw invalid_argument("file: Index out of bounds");
    else if(rank < 0 || rank > 7)
        throw invalid_argument("rank: Index out of bounds");

    if(mPieces[file][rank]){
        return *mPieces[file][rank];
    }
    return Piece();
}

void Board::makeMove(Move move){
    //cout<<move.fileFrom<<":"<<move.rankFrom<<"->"<<move.fileTo<<":"<<move.rankTo;

    if(move.fileFrom < 0 || move.fileFrom > 7){
        throw invalid_argument("move.fileFrom: Index out of bounds");
    } else if(move.fileTo < 0 || move.fileTo > 7){
        throw invalid_argument("move.fileTo: Index out of bounds");
    } else if(move.rankFrom < 0 || move.rankFrom > 7){
        throw invalid_argument("move.rankFrom: Index out of bounds");
    } else if(move.rankTo < 0 || move.rankTo > 7){
        throw invalid_argument("move.rankTo: Index out of bounds");
    }

    //after swapping, the piece on the square from is now stored in the square to
    std::swap(mPieces[move.fileTo][move.rankTo], mPieces[move.fileFrom][move.rankFrom]);
    
    delete mPieces[move.fileFrom][move.rankFrom];
    mPieces[move.fileFrom][move.rankFrom] = NULL;
}

