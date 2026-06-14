#pragma once

#include "Model.h"
#include "Solution.h"

#include <random>

Solution buildRandomSolution(
  const Model& model,
  int vehiclesPerDepot,
  int capacity,
  unsigned int seed = 42
);