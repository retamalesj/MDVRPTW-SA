#pragma once

#include "Solution.h"
#include "Instance.h"

#include <random>

using namespace std;

bool relocateMove(
  Solution& sol,
  mt19937& rng);

bool swapMove(
  Solution& sol,
  mt19937& rng);

bool splitMove(
  Solution& sol,
  const Instance& instance,
  mt19937& rng);