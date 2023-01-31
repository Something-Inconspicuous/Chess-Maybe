#include <iostream>
#include "../../src/libs/Board.hpp"

using namespace std;

int main(){
    cout << "testity test" << endl;

    Board* board = Board::startingBoard();

    cout << (*board).toString() + "" << endl;

    delete board;
    return 0;
} 