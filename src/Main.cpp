/**
 * 
 * 
 * @author Something Inconspicuous
*/

#include <iostream>
#include "Piece.hpp"

using namespace std;

int main(){
    cout << "testity test" << endl;

    Piece p(Piece::bishop, Piece::white); //this is the line that breaks everything
    cout << p.toString() << endl;

    return 0;
} 