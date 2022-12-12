#pragma once
#include <vector>
#include "../Variable/Variable.hpp"
#include "../Constraint/Constraint.hpp"

using VariablePtr = std::shared_ptr<Variable>;
using ConstraintPtr = std::shared_ptr<Constraint>;

struct CSP {
    std::vector<VariablePtr> variables;
    std::vector<ConstraintPtr> constraints;
};