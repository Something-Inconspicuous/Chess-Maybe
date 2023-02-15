#ifndef LETTERSMANIP_HPP
#define LETTERSMANIP_HPP
#include "string"

/// @brief a bunch of methods for manipulating characters
namespace LettersManip{
    /// @brief Converts the case of the charater to the oppsite. 
    /// only aplies to letters
    /// @param a {char} the character to switch casing of. 
    /// @return {char} a new char with the new casing
    char convertCase(char);

    /// @brief Converts letters to lowercase
    /// @param a {char} the letter to convert
    /// @return the lowercase letter
    char toLowerCase(char);

    /// @brief Converts letters to uppercase
    /// @param a {char} the letter to convert
    /// @return the uppercase letter
    char toUpperCase(char);
};
#endif