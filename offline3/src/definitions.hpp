#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Solver/Solver.hpp"
#include "Variable/Variable.hpp"
#include "ConstraintGraph/ConstraintGraph.hpp"
#include "ConstructiveHeuristic/ConstructiveHeuristic.hpp"
#include "ConstructiveHeuristic/LargestDegreeHeuristic/LargestDegreeHeuristic.hpp"
#include "ConstructiveHeuristic/LargestEnrollmentHeuristic/LargestEnrollmentHeuristic.hpp"
#include "ConstructiveHeuristic/SaturationDegreeHeuristic/SaturationDegreeHeuristic.hpp"
#include "PerturbativeHeuristic/PerturbativeHeuristic.hpp"
#include "Penalty/Penalty.hpp"
#include <fstream>
#include <algorithm>

using SolverPtr = std::shared_ptr<Solver>;
using VarPtr = std::shared_ptr<Variable>;
using ConstraintGraphPtr = std::shared_ptr<ConstraintGraph>;
using ConstraintGraphPtrWk = std::weak_ptr<ConstraintGraph>;

using ConHeuPtr = std::shared_ptr<ConstructiveHeuristic>;
using DegreeHeuPtr = std::shared_ptr<LargestDegreeHeuristic>;
using EnrollHeuPtr = std::shared_ptr<LargestEnrollmentHeuristic>;
using SatHeuPtr = std::shared_ptr<SaturationDegreeHeuristic>;

using PerHeuPtr = std::shared_ptr<PerturbativeHeuristic>;

using PenaltyPtr = std::shared_ptr<Penalty>;
