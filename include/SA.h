#pragma once

#include "Solution.h"
#include "Instance.h"

#include <random>

struct Parameters
{
  double ALPHA; // Constante de penalización del tiempo
  double BETA; // Constante de penalización de la capacidad

  double initialTemperature;
  double coolingRate; // Ti+1 = Ti* coolingRate

  int maxIterations;
  int coolingInterval; // Cada cuantas iteraciones se enfría
};

Solution simulatedAnnealing(
  const Solution& initialSolution,
  const Instance& instance,
  const Parameters& parameters,
  mt19937& rng
);