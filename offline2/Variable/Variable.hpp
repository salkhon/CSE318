#pragma once
#include "../defs.hpp"
#include <vector>

/**
 * @brief Variable class with domain, board position and assigned value.
 */
struct Variable {
    const int id;
    const int row, col;
    std::vector<int> domain;
    int val;

    Variable(int, int, int, std::vector<int>);
    bool is_assigned();
    void erase_assignment();
};
