#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Solver/Solver.hpp"
#include "Variable/Variable.hpp"
#include "ConstraintGraph/ConstraintGraph.hpp"
#include "Heuristic/Heuristic.hpp"
#include "Penalty/Penalty.hpp"
#include <fstream>

using SolverPtr = std::shared_ptr<Solver>;
using VarPtr = std::shared_ptr<Variable>;
using ConstraintGraphPtr = std::shared_ptr<ConstraintGraph>;
using HeuristicPtr = std::shared_ptr<Heuristic>;
using PenaltyPtr = std::shared_ptr<Penalty>;
