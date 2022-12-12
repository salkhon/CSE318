#include "BoardFactory.hpp"

std::pair<size_t, size_t> get_blank_idx(const std::vector<std::vector<int>>& board) {
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board[i].size(); j++) {
            if (board[i][j] == Board::BLANK) {
                return std::make_pair(i, j);
            }
        }
    }
    throw "No Blank Found in Board";
}

std::shared_ptr<Board> BoardFactory::move_board(std::shared_ptr<Board> prev_board, Move move) {
    auto [row, col] = get_blank_idx(prev_board->board_config);
    std::shared_ptr<Board> board_ptr;
    std::vector<std::vector<int>> board{ prev_board->board_config };

    if (move == LEFT && col > 0) {
        std::swap(board[row][col], board[row][col - 1]);
        board_ptr = std::make_shared<Board>(board, prev_board->num_moves + 1, prev_board);
    } else if (move == UP && row > 0) {
        std::swap(board[row][col], board[row - 1][col]);
        board_ptr = std::make_shared<Board>(board, prev_board->num_moves + 1, prev_board);
    } else if (move == RIGHT && col < prev_board->get_board_dim() - 1) {
        std::swap(board[row][col], board[row][col + 1]);
        board_ptr = std::make_shared<Board>(board, prev_board->num_moves + 1, prev_board);
    } else if (move == DOWN && row < prev_board->get_board_dim() - 1) {
        std::swap(board[row][col], board[row + 1][col]);
        board_ptr = std::make_shared<Board>(board, prev_board->num_moves + 1, prev_board);
    } else {
        board_ptr = nullptr;
    }

    return board_ptr;
}

std::shared_ptr<Board> BoardFactory::init_board(const std::vector<std::vector<int>>& board_config) {
    return std::make_shared<Board>(board_config, 0, nullptr);
}

std::vector<std::vector<int>> BoardFactory::get_goal_board(const size_t dim) {
    std::vector<std::vector<int>> board(dim, std::vector<int>(dim, 0));
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            board[i][j] = i * dim + j + 1;
        }
    }
    board[dim - 1][dim - 1] = Board::BLANK;
    return board;
}
