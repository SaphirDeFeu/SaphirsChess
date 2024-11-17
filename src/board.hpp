#pragma once
#include<string>
#include"state.hpp"

/**
 * Namespace for use to translate movements into the program's chosen syntax
 */
namespace Movement {
  using move = unsigned short;
  /**
   * @brief Converts a UCI movement to the program's chosen representation
   * \code {.cpp}
   * std::string s = "e2e4"; // move from e2 to e4 square
   * unsigned short u = Movement::from_uci(s); // returns 0 000 011 100 001 100 (-4e2e)
   * \endcode
   * @param _ucir Any UCI movement following the format `crCRp` where `c`=start column ; `r`=start row ; `C`=target column ; `R`=target row ; `p`=promotion (can be omitted)
   * @return Unsigned short of notation: `xPPPTTTTTTSSSSSS` where `P`=Promotion ; `T`=Target ; `S`=Start
   */
  move from_uci(const std::string& _ucir) noexcept;

  /**
   * @brief Converts this program's chosen movement representation to human readable UCI notation
   * \code {.cpp}
   * unsigned short u = 0b0000011100001100; // see Movement::from_uci(const std::string& _ucir)
   * std::string s = Movement::from_u16(u);
   * \endcode
   * @param _us Unsigned short of notation: `xPPPTTTTTTSSSSSS` where `P`=Promotion ; `T`=Target ; `S`=Start
   * @return Corresponding UCI movement following the format `crCRp` where `c`=start column ; `r`=start row ; `C`=target column ; `R`=target row ; `p`=promotion (can be omitted)
   */
  std::string from_u16(const move& _us) noexcept;
}

/**
 * Class used to interpret and interact with a chess board
 */
class Board {
  public:
  Board(const std::string& fen_string) noexcept;
  Board() noexcept : Board(STARTING_POSITION_FEN) {};
  ~Board() noexcept;
  /**
   * @brief Calculates a FEN string from the current state
   * @return a FEN string
   */
  std::string get_fen() const noexcept;
  /**
   * @brief Creates a nice-looking* string of the current state
   * @return the string corresponding to the current state
   */
  std::string display() const noexcept;

  /**
   * @brief Generates legal moves for this position
   */
  void generate_legal_moves() noexcept;

  /**
   * @brief Makes a move to the board that can be backtracked with \ref Board::unmake_move "Board::unmake_move"
   * @param _m A movement parsed from UCI into the program's trace (see \ref Movement::from_uci "Movement::from_uci()")
   */
  void make_move(const Movement::move& _m) noexcept;

  /**
   * @brief Backtracks the last move done on this board
   */
  void unmake_move() noexcept;

  /**
   * @brief Runs the test suite at a depth of `depth` plies, outputting the number of positions at each ply
   * @param depth The number of plies to look into
   * @return Amount of positions found
   */
  size_t perft(size_t depth) noexcept;

  private:

  /**
   * @brief Generates sliding moves in accordance to row_offsets and col_offsets. Moves generated will be outputted into \ref Board::legal_moves "Board::legal_moves"
   * @param s A pointer to the state to generate the moves from
   * @param row_offsets Must correspond on a square-basis to col_offsets, used to describe offsets to use as a basis for move generating.
   * @param col_offsets See row_offsets
   * @param sq The original starting square
   * @param og_piece The original starting piece
   * @param len Length of the arrays `row_offsets` and `col_offsets`
   * @param legal_moves A pointer to a vector to store the moves into
   */
  static void generate_sliding_moves(State* s, int* row_offsets, int* col_offsets, const int& sq, const Piece::piece& og_piece, int len, std::vector<Movement::move>* legal_moves) noexcept;

  /**
   * @brief Removes pseudo legal moves from the available legal moves
   */
  void remove_pseudolegal_moves() noexcept;

  /**
   * @brief Generates pseudo legal moves of the current position
   * @param s A pointer to a State to analyse
   * @return The pseudolegal moves of the position
   */
  std::vector<Movement::move> generate_pseudolegal_moves(State* s) noexcept;

  State* state;
  std::vector<Movement::move> legal_moves = std::vector<Movement::move>();
  /**
   * Tracks all the moves done for each ply during this game
   */
  std::vector<State*> states = std::vector<State*>();
};