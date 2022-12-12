#include "Board.hpp"

Board::Board(const std::vector<std::vector<int>>& board_config, const unsigned num_moves, std::shared_ptr<Board> prev)
    : board_config{ board_config }, num_moves{ num_moves }, prev{ prev } {
}

size_t Board::get_board_dim() {
    return this->board_config[0].size();
}

std::ostream& operator<<(std::ostream& ostrm, const Board& board) {
    for (size_t i = 0; i < board.board_config.size(); i++) {
        for (size_t j = 0; j < board.board_config[i].size(); j++) {
            ostrm <<
                (board.board_config[i][j] > -1 ? std::to_string(board.board_config[i][j]) : "*")
                << "\t";
        }
        ostrm << std::endl;
    }
    return ostrm;
}

size_t Board::BoardConfigHashFunction::operator()(std::vector<std::vector<int>> const& board_config) const {
    size_t hash = board_config.size();
    for (const std::vector<int>& row : board_config) {
        for (int val : row) {
            hash ^= val + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
    }
    return hash;
}

bool Board::BoardConfigEqualsFunction::operator()(std::vector<std::vector<int>> const& left, std::vector<std::vector<int>>const& right) const {
    for (size_t i = 0; i < left.size(); i++) {
        for (size_t j = 0; j < left.size(); j++) {
            if (left[i][j] != right[i][j]) {
                return false;
            }
        }
    }
    return true;
}