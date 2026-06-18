#pragma once

#include "Solution.h"

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
  mt19937& rng);