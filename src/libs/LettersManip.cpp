#include "LettersManip.hpp"

using namespace std;

char LettersManip::convertCase(char a){
    if(a >= 'a' && a <= 'z'){
        a = toUpperCase(a); 
    }else if(a >= 'A' && a <= 'Z'){
        a = toLowerCase(a);
    }
    return a;
}

char LettersManip::toUpperCase(char a){
    if(a >= 'a' && a <= 'z'){
        a = 'A' + (a - 'a'); 
    }
    return a;
}

char LettersManip::toLowerCase(char a){
    if(a >= 'A' && a <= 'Z'){
        a = 'a' + (a - 'A');
    }
    return a;
}