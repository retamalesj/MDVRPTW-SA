#pragma once

#include "Solution.h"
#include "Instance.h"

#include <random>

Solution buildRandomSolution(
  const Instance& instance,
  unsigned int seed = 42
);