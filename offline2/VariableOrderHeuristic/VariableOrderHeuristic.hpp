#pragma once
#include "../Variable/Variable.hpp"
#include <memory>

struct VariableOrderHeuristic {
    std::shared_ptr<Variable> next_var();
};