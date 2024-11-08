#include<string>
#include"piece.hpp"

/// The FEN string for a starting position.
const std::string STARTING_POSITION_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

/**
 * @brief Class used to store data that can be interpreted from and converted to a FEN string
 * \code {.cpp}
 * State state();
 * \endcode
 * @see State::State() noexcept
 * @see State::State(const std::string& fen_string) noexcept
 */
class State {
  public:
  /**
   * @brief Creates an object from the specified `fen_string`
   * \code {.cpp}
   * State state(STARTING_POSITION_FEN);
   * \endcode
   * 
   * @param fen_string A fen string, in accordance with chess notation
   */
  State(const std::string& fen_string) noexcept;

  /**
   * @brief Creates an object using \ref STARTING_POSITION_FEN "STARTING_POSITION_FEN"
   * \code {.cpp}
   * State state();
   * \endcode
   * @overload
   */
  inline State() noexcept : State(STARTING_POSITION_FEN) {};

  /**
   * @brief Destroys the State object and deallocates the heap memory used by \ref State::board "State::board" and \ref State::castle_rights "State::castle_rights"
   */
  ~State() noexcept;

  /**
   * @brief Converts the data stored in this object to a FEN string
   * \code {.cpp}
   * std::string fen_string = state.to_fen_string();
   * \endcode
   * 
   * @return the corresponding FEN string
   */
  std::string to_fen_string() const noexcept;

  /**
   * @brief Getter for this object's \ref State::board "board" attribute. \n
   * \n
   * The index of any square can be calculated using \ref Square::from_vec(const std::vector<char>& vec) "Square::from(const std::vector<char>& vec) noexcept"
   * \code {.cpp}
   * Piece* board = state.get_board();
   * std::vector<char> vec();
   * vec.push_back('a');
   * vec.push_back('1');
   * unsigned char index = Square::from_vec(vec); // Get the numerical notation of the A1 square
   * board[index]; // Gets the piece on the A1 square
   * \endcode
   * All items are set to whichever piece was found at that position in the FEN string given upon creation of this State object.
   * 
   * @return A pointer to the first element in this board
   * @note The array ALWAYS has a length of 64 items
   */
  Piece::piece* get_board() const noexcept;

  /**
   * @brief Getter for this object's \ref State::ply_player "ply_player" attribute
   * \code {.cpp}
   * Piece::Color* ply_player = state.get_ply_player();
   * *ply_player = Piece::Color::BLACK; // Sets the player whose turn it is to black
   * \endcode
   * 
   * @return A pointer to the color of the player (not an array)
   */
  Piece::Color* get_ply_player() noexcept;

  /**
   * @brief Getter for this object's \ref State::castle_rights "castle_rights" attribute.
   * \code {.cpp}
   * bool* castle_rights = state.get_castle_rights();
   * castle_rights[0] = true; // Sets castling rights for the white kingside to true
   * castle_rights[1] = true; // Sets castling rights for the white queenside to true
   * castle_rights[2] = true; // Sets castling rights for the black kingside to true
   * castle_rights[3] = true; // Sets castling rights for the black queenside to true
   * \endcode
   * By default, all items in `castle_rights` are set to true unless specified otherwise in the FEN string used to generate this State object.
   * 
   * @return A pointer to the first element of the castling rights
   * @note The array ALWAYS has a length of 4 items
   */
  bool* get_castle_rights() const noexcept;

  /**
   * @brief Getter for this object's \ref State::en_passant "en_passant" attribute
   * \code {.cpp}
   * unsigned char* en_passant = state.get_en_passant();
   * std::vector<char> vec = Square::from_byte(*en_passant);
   * vec.at(0); // The column of the en_passant square
   * vec.at(1); // The row of the en_passant square (may be a null pointer or error if the en_passant square was a Square::NULL_SQUARE)
   * ;// If is a Square::NULL_SQUARE, then vec.at(0) will be '-'
   * \endcode
   * 
   * 
   * @return An 8-bit unsigned integer which can be parsed by \ref Square::from_byte(const unsigned char& byte) "Square::from_byte(const unsigned char& byte) noexcept"
   */
  unsigned char* get_en_passant() noexcept;

  /**
   * @brief Getter for this object's \ref State::halfmove "halfmove" attribute
   * \code {.cpp}
   * unsigned short* halfmoves = state.get_halfmove_clock();
   * \endcode
   * 
   * @return A 16-bit unsigned integer.
   */
  unsigned short* get_halfmove_clock() noexcept;

  /**
   * @brief Getter for this object's \ref State::fullmove "fullmove" attribute
   * \code {.cpp}
   * unsigned int* fullmoves = state.get_fullmove_clock();
   * \endcode
   * 
   * @return A 32-bit unsigned integer
   */
  unsigned int* get_fullmove_clock() noexcept;

  // ----------------------------------

  private:
  /**
   * @brief The board object. An array of pieces of length 64. Heap-allocated upon construction. Deallocated upon destruction.
   */
  Piece::piece* board;
  /**
   * @brief The player whose turn it is to play. A single number. Stack-allocated.
   */
  Piece::Color ply_player = Piece::Color::WHITE;
  /**
   * @brief The current rights to castle for each player. Heap-allocated upon construction. Deallocated upon destruction.
   * Each item is in order of how they would appear in a FEN string. castle_rights[0] is white kingside castle, ...
   * A FEN string specifies castle rights in the `KQkq` order.
   */
  bool* castle_rights;
  /**
   * @brief The current possible en_passant square. By default, unless specified, is \ref Square::NULL_SQUARE "Square::NULL_SQUARE". Stack-allocated.
   */
  unsigned char en_passant = Square::NULL_SQUARE;
  /**
   * @brief The current number of halfmoves since the last pawn advance or piece capture. Used to enforce the 50-move-rule. Stack-allocated.
   */
  unsigned short halfmove = 0;
  /**
   * @brief The current number of moves. Stack-allocated.
   */
  unsigned int fullmove = 1;
};