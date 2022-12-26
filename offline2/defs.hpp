#pragma once
#include "ConstraintGraph/ConstraintGraph.hpp"
#include "CSPSolver/CSPSolver.hpp"
#include "Variable/Variable.hpp"
#include "VariableOrderHeuristic/VariableOrderHeuristic.hpp"
#include <memory>

using ConstraintGraphPtr = std::shared_ptr<ConstraintGraph>;
using CSPSolverPtr = std::shared_ptr<CSPSolver>;
using VariablePtr = std::shared_ptr<Variable>;
using VOHPtr = std::shared_ptr<VariableOrderHeuristic>;
