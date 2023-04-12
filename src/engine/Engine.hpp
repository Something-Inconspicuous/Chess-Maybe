#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "map"
#include "../main/Game.hpp"

namespace Engine{
    extern const int outNumWeight;
    extern const int mobilityWeight;

    extern const std::map<Piece::type, int> matVal;

    /// @brief the positional score for every square for white pawns
    extern const int wPawnPosVal[8][8];

    /// @brief the positional score for every square for black pawns
    extern const int bPawnPosVal[8][8];

    /// @brief the positional score for every square for white knights
    extern const int wKnightPosVal[8][8];

    /// @brief the positional score for every square for black knights
    extern const int bKnightPosVal[8][8];

    /// @brief the positional score for every square for white bishops
    extern const int wBishopPosVal[8][8];

    /// @brief the positional score for every square for black bishops
    extern const int bBishopPosVal[8][8]; 

    /// @brief the positional score for every square for white rooks
    extern const int wRookPosVal[8][8];

    /// @brief the positional score for every square for black bishops
    extern const int bRookPosVal[8][8];

    /// @brief the positional score for every square for white queens
    extern const int wQueenPosVal[8][8];

    /// @brief the positional score for every square for black queens
    extern const int bQueenPosVal[8][8];

    /// @brief the positional score for every square for the white king earlier in the game
    extern const int wKingBegPosVal[8][8];

    /// @brief the positional score for every square for the black king earlier in the game
    extern const int bKingBegPosVal[8][8];

    /// @brief the positional score for every square for the white king later in the game
    extern const int wKingEndPosVal[8][8];

    /// @brief the positional score for every square for the black king later in the game
    extern const int bKingEndPosVal[8][8];

    /// @brief Gives a heuristic evaluation of a game's position
    /// @param game the game to evaluate the position of
    /// @return the evaluation
    int evali(Game& game);

    /// @brief Search function, searching to a given depth an returning the position's
    /// evaluation based on the search's results. Stores the best move in a given move
    /// @param game the game to search in
    /// @param depth the depth to search to
    /// @param moveToStore where to store the best move
    /// @return the evaluation of the position
    int search(Game& game, int depth, Move& moveToStore);
    
    /// @brief Not to be used outside of the @ref Engine namespace
    inline namespace privates{
        /// @brief Recursive search function, searching to a given depth and returning the position's
        /// evaluation based on the search's results
        /// @param game the game to search for moves in
        /// @param depth the depth to search to
        /// @param alpha upperbound for alphabeta pruning
        /// @param beta lowerbound for alphabeta pruning
        /// @param startingDepth the starting depth, so that the search can know how deep it is
        /// @return An int evaluation of the position based on how good the position could be in @ref depth moves
        int mSearch(Game game, int depth, int alpha, int beta, const int startingDepth);
    }

    inline namespace literals{
        constexpr inline int  operator""_ply(unsigned long long x){
            return x * 2;
        }
    }
} // namespace Engine


#endif