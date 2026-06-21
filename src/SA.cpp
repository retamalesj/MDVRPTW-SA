#include "SA.h"
#include "Evaluator.h"
#include "Moves.h"
#include "SolutionUtils.h"

#include <random>
#include <cmath>

using namespace std;

Solution simulatedAnnealing(
  const Solution &initialSolution,
  const Instance &instance,
  const Parameters& parameters,
  mt19937& rng)
{
  Solution current = initialSolution;
  Solution Sbest = initialSolution;

  double currentCost = evaluate(current, instance, parameters.ALPHA, parameters.BETA);

  double bestCost = currentCost;

  double temperature = parameters.initialTemperature;

  uniform_real_distribution<double> probabilityDist(0.0, 1.0);

  uniform_real_distribution<double> move_probability(0.0, 1.0);

  int noImprovement = 0;

  for (int iter = 1; iter <= parameters.maxIterations; iter++)
  {
    Solution neighbor = current;

    bool success = false;

    double r = move_probability(rng);

    if (r < 0.7) { success = swapMove(neighbor, rng); }
    else if (r < 0.9) { success = relocateMove(neighbor, rng); }
    else { success = splitMove(neighbor, rng); }

    if (!success) continue;
    
    if (!isFeasible(neighbor, instance)) continue;

    double neighborCost = evaluate(neighbor, instance, parameters.ALPHA, parameters.BETA);

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

    bool improved = false;

    if (accept)
    {
      current = neighbor;
      currentCost = neighborCost;

      if (currentCost < bestCost)
      {
        Sbest = current;
        bestCost = currentCost;
        improved = true;
        noImprovement = 0;
      }
    }

    if (!improved) noImprovement++;

    // enfriamiento
    if (iter % parameters.coolingInterval == 0) temperature *= parameters.coolingRate;

    // recalentamiento
    if (noImprovement > parameters.maxStagnation)
    {
      temperature = parameters.initialTemperature * 0.3;
      noImprovement = 0;
    }
  }

  return Sbest;
}