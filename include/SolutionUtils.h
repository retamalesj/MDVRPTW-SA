#pragma once

#include "Solution.h"
#include "Instance.h"

void writeSolution(
  unsigned int SEED,
  const Solution& sol,
  const Instance& instance,
  double ALPHA,
  double BETA
);

bool isFeasible(
  const Solution& sol,
  const Instance& instance
);