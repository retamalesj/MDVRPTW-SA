#pragma once

#include "Solution.h"
#include "Instance.h"

Solution simulatedAnnealing(
  const Solution& initialSolution,
  const Instance& instance,
  double ALPHA,
  double BETA,
  int maxIterations,
  int coolingInterval,
  mt19937& rng
);