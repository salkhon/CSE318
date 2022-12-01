#include "Board.hpp"

Board::Board(const std::vector<std::vector<int>>& board, const unsigned num_moves, std::shared_ptr<Board> prev)
    : board{ board }, num_moves{ num_moves }, prev{ prev } {
}

size_t Board::get_board_dim() {
    return this->board[0].size();
}

std::ostream& Board::operator<<(std::ostream& ostrm) {
    for (size_t i = 0; i < this->board.size(); i++) {
        for (size_t j = 0; j < this->board[i].size(); j++) {
            ostrm <<
                (this->board[i][j] > -1 ? std::to_string(this->board[i][j]) : "*")
                << "\t";
        }
        ostrm << std::endl;
    }
}
