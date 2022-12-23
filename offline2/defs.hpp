#pragma once
#include "Constraint/Constraint.hpp"
#include "CSP/CSP.hpp"
#include "CSPSolver/CSPSolver.hpp"
#include "Variable/Variable.hpp"
#include "VariableOrderHeuristic.hpp"
#include <memory>

using ConstraintPtr = std::shared_ptr<Constraint>;
using CSPPtr = std::shared_ptr<CSP>;
using CSPSolverPtr = std::shared_ptr<CSPSolver>;
using VariablePtr = std::shared_ptr<Variable>;
using VOHPtr = std::shared_ptr<VariableOrderHeuristic>;
