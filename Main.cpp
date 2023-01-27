//g++ Piece.cpp Main.cpp -o Main

#include <iostream>
#include "Piece.h"

using namespace std;

int main(){
    cout << "testity test" << endl;

    Piece p(Piece::BISHOP, Piece::WHITE); //this is the line that breaks everything
    cout << p.toString() << endl;

    return 0;
} 