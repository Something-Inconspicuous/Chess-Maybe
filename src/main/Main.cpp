#include <iostream>
#include "..\..\src\libs\Board.hpp"
#include "string"

using namespace std;

void clrscr(){
    cout << string(50, '\n') << endl;
}

int main(){
    cout << "testity test" << endl;

    clrscr();

    Board* board = new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    cout << (*board).toString() + "" << endl;

    delete board;
    return 0;
} 