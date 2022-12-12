#pragma once
#include "../Board.hpp"
#include <utility>

enum Move {
    LEFT, UP, RIGHT, DOWN
};

struct BoardFactory {
    static std::shared_ptr<Board> move_board(std::shared_ptr<Board>, Move);
    static std::shared_ptr<Board> init_board(const std::vector<std::vector<int>>&);
    static std::vector<std::vector<int>> get_goal_board(const size_t);
};
