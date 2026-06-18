#include "SA.h"
#include "Evaluator.h"
#include "Moves.h"

#include <random>
#include <cmath>

using namespace std;

Solution simulatedAnnealing(
  const Solution &initialSolution,
  const Instance &instance,
  double ALPHA,
  double BETA,
  int maxIterations,
  int coolingInterval,
  unsigned int seed)
{
  mt19937 rng(seed);

  Solution current = initialSolution;
  Solution Sbest = initialSolution;

  double currentCost = evaluate(current, instance, ALPHA, BETA);

  double bestCost = currentCost;

  double temperature = 1000.0;
  double coolingRate = 0.995;

  uniform_real_distribution<double> probabilityDist(0.0, 1.0);

  uniform_int_distribution<int> moveDist(0, 1);

  for (int iter = 1; iter <= maxIterations; iter++)
  {
    Solution neighbor = current;

    bool success = false;

    int move = moveDist(rng);

    if (move == 0)
    {
      success = swapMove(neighbor, rng);
    }
    else
    {
      success = relocateMove(neighbor, rng);
    }

    if (!success) continue;

    double neighborCost = evaluate(neighbor, instance, ALPHA, BETA);

    double delta = neighborCost - currentCost;

    bool accept = false;

    if (delta < 0)
    {
      accept = true;
    }
    else
    {
      double acceptanceProbability = exp(-delta / temperature);

      if (probabilityDist(rng) < acceptanceProbability) accept = true;
    }

    if (accept)
    {
      current = neighbor;
      currentCost = neighborCost;

      if (currentCost < bestCost)
      {
        Sbest = current;
        bestCost = currentCost;
      }
    }

    if (iter % coolingInterval == 0) temperature *= coolingRate;
  }

  return Sbest;
}