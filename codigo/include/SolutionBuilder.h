#pragma once

#include "Solution.h"
#include "Instance.h"

#include <random>

Solution buildRandomSolution(
  const Instance& instance,
  mt19937& rng
);