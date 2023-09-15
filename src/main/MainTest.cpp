#ifdef DEBUG 

#include <iostream>
#include "algorithm"
#include "../engine/Engine.hpp"
#include "../libs/LettersManip.hpp"

using namespace Engine::literals;

int main(){
    
    Game game = Game("r2qkb1r/pp2nppp/3p4/2pNN1B1/2BnP3/3P4/PPP2PPP/R2bK2R");
    std::cout << game.boardAsString() << "\n";
    
    
    //return 0;

    //Bot bot = Bot(game);

    

    std::cout << "searching all" << "\n";
    //bot.store();
    //int eval = bot.search(4_ply);
    int eval;
    Move m;
    eval = Engine::search(game, 2_ply, m);
    std::cout << "searched" << "\n";
    std::cout << "best move has eval " << eval << "\n";
    //Move m = bot.getStoredMove();
    
    game.makeMove(m);
    

    std::cout << m.fileFrom << ":" << m.rankFrom << "->" << m.fileTo << ":" << m.rankTo << "\n";

    
    
    
    
    std::cout << "after move\n" << game.boardAsString() << "\n";

    std::cout << std::endl;
    return 0;
}

#endif