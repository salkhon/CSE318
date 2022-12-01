#include "Solver.hpp"

Solver::Solver(const size_t dim)
    : dim{ dim } {
}


int Solver::hamming_dist(std::shared_ptr<Board> board_ptr, std::shared_ptr<Board> goal_board_ptr = nullptr) {
    if (!goal_board_ptr) {
        goal_board_ptr = BoardFactory::init_board(BoardFactory::get_goal_board(this->dim));
    }
}

int Solver::manhattan_dist(std::shared_ptr<Board> board_ptr, std::shared_ptr<Board> goal_board_ptr = nullptr) {
    if (!goal_board_ptr) {
        goal_board_ptr = BoardFactory::init_board(BoardFactory::get_goal_board(this->dim));
    }
}

void Solver::solve(std::shared_ptr<Board> board_ptr) {

}