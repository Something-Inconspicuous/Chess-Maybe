#include "Move.hpp"

struct Move;

bool Move::operator==(Move cMove){
    return cMove.fileFrom == this->fileFrom && cMove.fileTo == this->fileTo
        && cMove.rankFrom == this->rankFrom && cMove.rankTo == this->rankTo;
}

void Move::operator=(const Move nMove){
    this->fileFrom = nMove.fileFrom;
    this->fileTo = nMove.fileTo;
    this->rankFrom = nMove.rankFrom;
    this->rankTo = nMove.rankTo;
}
