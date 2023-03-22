#include "Move.hpp"

struct Move;

bool Move::operator==(Move cMove){
    return cMove.fileFrom == this->fileFrom && cMove.fileTo == this->fileTo
        && cMove.rankFrom == this->rankFrom && cMove.rankTo == this->rankTo
        && cMove.promotion == this->promotion;
}