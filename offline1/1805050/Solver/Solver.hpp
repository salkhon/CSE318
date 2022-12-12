#pragma once
#include <memory>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <stack>
#include <string>
#include "../Board/Board.hpp"
#include "../Board/BoardFactory/BoardFactory.hpp"

struct Solver {
    const size_t DIM;
    const std::vector<std::vector<int>> INIT_BOARD_CONFIG;
    const std::vector<std::vector<int>> GOAL_BOARD_CONFIG;

    size_t explored_nodes;
    size_t expanded_nodes;

    Solver(const size_t, std::vector<std::vector<int>>);
    int hamming_dist(std::shared_ptr<Board>);
    int manhattan_dist(std::shared_ptr<Board>);
    bool is_solvable();

    void solve();

private:
    void solve_helper(std::function< bool(std::shared_ptr<Board>, std::shared_ptr<Board>) >);
    void print_moves(std::shared_ptr<Board>, bool = false);
};