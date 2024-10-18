#include<string>
#include"state.hpp"

class Board {
  public:
  Board(const std::string& fen_string) noexcept;
  Board() noexcept : Board(STARTING_POSITION_FEN) {};
  ~Board() noexcept;
  std::string get_fen() const noexcept;

  private:
  State* state;
};