#include "Evaluator.h"

using namespace std;

const double ALPHA = 100.0;
const double BETA = 100.0;

double evaluateSolution(
  const Solution &sol,
  const Model &model,
  int capacity)
{
  double totalDistance = 0.0;
  double capacityPenalty = 0.0;
  double timePenalty = 0.0;

  for (const Route &route : sol.routes)
  {
    if (route.customers.empty())
      continue;

    int depot = route.depot;

    double currentTime = 0.0;
    int load = 0;

    int first = route.customers.front();

    totalDistance += model.dist[depot][first];
    currentTime += model.dist[depot][first];

    for (size_t i = 0; i < route.customers.size(); i++)
    {
      int current = route.customers[i];

      const Node &node = model.allNodes[current];

      load += node.demand;

      // Ventana temprana
      if (currentTime < node.e)
      {
        currentTime = node.e;
      }

      // Ventana tardía
      if (currentTime > node.l)
      {
        timePenalty += currentTime - node.l; // tardanza
      }

      currentTime += node.serviceTime;

      // Cliente -> siguiente cliente
      if (i < route.customers.size() - 1)
      {
        int next = route.customers[i + 1];

        totalDistance += model.dist[current][next];
        currentTime += model.dist[current][next];
      }
    }

    // Último cliente -> depot
    int last = route.customers.back();

    totalDistance += model.dist[last][depot];

    // Capacidad
    if (load > capacity)
    {
      capacityPenalty += load - capacity; // cargado - capacidad 
    }
  }

  return totalDistance + ALPHA * capacityPenalty + BETA * timePenalty;
}