#include "Board.hpp"

Board::Board(const std::vector<std::vector<int>>& board, const unsigned num_moves, std::unique_ptr<Board> prev)
    : board{ board }, num_moves{ num_moves }, prev{ std::move(prev) } {
}
