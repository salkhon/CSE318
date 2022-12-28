#pragma once
#include <vector>
#include <memory>
#include <ostream>

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
    friend std::ostream& operator<< (std::ostream& ostrm, const Variable& var);
};

using VariablePtr = std::shared_ptr<Variable>;