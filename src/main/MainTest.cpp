#include <iostream>
#include "algorithm"
#include "../bot/Bot.hpp"
#include "../libs/LettersManip.hpp"

int main(){
    
    Game game("r2qkb1r/pp2nppp/3p4/2pNN1B1/2BnP3/3P4/PPP2PPP/R2bK2R");
    std::cout << game.boardAsString() << "\n";

    Bot bot(game);

    std::cout << "searching all" << "\n";
    bot.store();
    int eval = bot.search(1);
    std::cout << "searched" << "\n";
    //std::cout << "best move has eval " << eval << "\n";
    Move m = bot.getStoredMove();
    

    std::cout << m.fileFrom << ":" << m.rankFrom << "->" << m.fileTo << ":" << m.rankTo << "\n";
    
    

    std::cout << "after move\n" << game.boardAsString() << "\n";

    return 0;
}