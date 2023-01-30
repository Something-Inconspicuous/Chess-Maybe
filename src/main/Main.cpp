#include <iostream>
#include "../../src/libs/Board.hpp"

using namespace std;

int main(){
    cout << "testity test" << endl;

    Board* board = new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    cout << (*board).toString() + "" << endl;

    delete board;
    return 0;
} 