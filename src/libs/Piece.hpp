#include "string"
#include <map>


class Piece{
    public:
        /// @brief the type of piece a piece is (pawn, king, etc.).
        /// 0 corrosponds to no type
        enum type{
            notype, pawn, knight, bishop, rook, queen, king
        };

        /// @brief the color of a piece. 0 corrosponds to no color
        enum color{
            nocolor, white, black
        };

        /// @brief creates a piece with a specified type and color
        /// @param nType  {Piece:type} the type the piece will have
        /// @param nColor {Piece::color} the color the piece will have
        Piece(type nType, color nColor);

        /// @brief creates a piece with type @ref notype and color @ref nocolor
        Piece();

        /// @brief gives the type of the piece
        /// @return the type of the piece
        type getType();

        /// @brief gives the color of the piece
        /// @return the color of the piece
        color getColor();

        /// @brief changes a piece's type
        /// @param promotion the type to change the piece to
        /// @return 0 if the piece can be promoted to the given type
        int promoteTo(type promotion);

        /// @brief returns the string form of the piece in the format "color type"
        /// e.g. white bishop
        /// @return the string form of a piece
        std::string toString();

        /// @brief returns the character form of a piece.
        ///
        /// The piece type is represented as the first letter of its type (knights use N).
        /// The color of the piece is represented by the case of the character.
        /// Uppercase is white while lower case is black.
        /// if either type or color is untyped/0, the method will return '0'
        /// @return the character representation of a piece
        char toChar();

        /// @brief dictionary as to what character represents what piece type
        /// @param type {Piece::type} the type of the piece
        /// @return the character that corrosponds to the piece type
        static const std::map<Piece::type, char> pieceToChar;

    private:
        /// @brief the type of the piece
        type mType;

        /// @brief the color of the piece
        color mColor;
};