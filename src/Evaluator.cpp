#include "Evaluator.h"

using namespace std;

double evaluateSolution(
  const Solution &sol,
  const Model &model,
  int capacity,
  double ALPHA,
  double BETA
)
{
  double totalDistance = 0.0;
  double capacityPenalty = 0.0;
  double timePenalty = 0.0;

  for (const Route &route : sol.routes)
  {
    if (route.customers.empty())
      continue;

    int depot = route.depot;

    double t = 0.0;
    int load = 0;

    int first = route.customers.front();

    totalDistance += model.dist[depot][first];
    t += model.dist[depot][first];

    for (size_t i = 0; i < route.customers.size(); i++)
    {
      int current = route.customers[i];

      const Node &node = model.allNodes[current];

      load += node.demand;

      // Ventana temprana
      if (t < node.e)
      {
        t = node.e;
      }

      // Ventana tardía
      if (t > node.l)
      {
        timePenalty += t - node.l; // tardanza
      }

      t += node.serviceTime;

      // Cliente -> siguiente cliente
      if (i < route.customers.size() - 1)
      {
        int next = route.customers[i + 1];

        totalDistance += model.dist[current][next];
        t += model.dist[current][next];
      }
    }

    // Último cliente -> depot
    int last = route.customers.back();

    totalDistance += model.dist[last][depot];

    // Capacidad
    if (load > capacity) capacityPenalty += load - capacity; // Carga - Capacidad 

  }

  return totalDistance + ALPHA * timePenalty + BETA * capacityPenalty;
}