#pragma once
#include <vector>

struct Variable {
    std::vector<int> domain;

    Variable(const std::vector<int>&);
};
