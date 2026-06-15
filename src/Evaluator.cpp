#include "Evaluator.h"

using namespace std;

double evaluate(
  const Solution &sol,
  const Instance &instance,
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

    totalDistance += instance.dist[depot][first];
    t += instance.dist[depot][first];

    for (size_t i = 0; i < route.customers.size(); i++)
    {
      int current = route.customers[i];

      const Node &node = instance.allNodes[current];

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

        totalDistance += instance.dist[current][next];
        t += instance.dist[current][next];
      }
    }

    // Último cliente -> depot
    int last = route.customers.back();

    totalDistance += instance.dist[last][depot];
    t += instance.dist[last][depot];

    const Node& depotNode = instance.allNodes[depot];

    // penalización de tardanza si retorna tarde
    if (t > depotNode.l)
    {
      timePenalty += t - depotNode.l;
    }

    // Capacidad
    if (load > instance.capacity) capacityPenalty += load - instance.capacity; // Carga - Capacidad 

  }

  return totalDistance + ALPHA * timePenalty + BETA * capacityPenalty;
}

EvaluationResult evaluateWithDetails(
  const Solution &sol,
  const Instance &instance,
  double ALPHA,
  double BETA
)
{
  EvaluationResult result;

  double totalDistance = 0.0;
  double capacityPenalty = 0.0;
  double timePenalty = 0.0;

  int routeId = 0;

  for (const Route &route : sol.routes)
  {
    if (route.customers.empty())
      continue;

    int depot = route.depot;

    double t = 0.0;
    int load = 0;

    double routeDistance = 0.0; // ✔ NUEVO

    int first = route.customers.front();

    routeDistance += instance.dist[depot][first];
    totalDistance += instance.dist[depot][first];

    t += instance.dist[depot][first];

    for (size_t i = 0; i < route.customers.size(); i++)
    {
      int current = route.customers[i];

      const Node &node = instance.allNodes[current];

      load += node.demand;

      // Ventana temprana
      if (t < node.e)
      {
        t = node.e;
      }

      // Ventana tardía
      if (t > node.l)
      {
        double violation = t - node.l;

        timePenalty += violation;

        result.timePenalties.push_back({
          node.id,
          node.isDepot,
          t,
          node.e,
          node.l,
          violation
        });
      }

      t += node.serviceTime;

      // Cliente -> siguiente cliente
      if (i < route.customers.size() - 1)
      {
        int next = route.customers[i + 1];

        routeDistance += instance.dist[current][next];
        totalDistance += instance.dist[current][next];

        t += instance.dist[current][next];
      }
    }

    // Último cliente -> depot
    int last = route.customers.back();

    routeDistance += instance.dist[last][depot];
    totalDistance += instance.dist[last][depot];

    t += instance.dist[last][depot];

    const Node& depotNode = instance.allNodes[depot];

    // penalización de tardanza si retorna tarde
    if (t > depotNode.l)
    {
      double violation = t - depotNode.l;

      timePenalty += violation;

      result.timePenalties.push_back({
        depotNode.id,
        depotNode.isDepot,
        t,
        depotNode.e,
        depotNode.l,
        violation
      });
    }

    // Capacidad
    if (load > instance.capacity)
    {
      int violation = load - instance.capacity;

      capacityPenalty += violation;

      result.capacityPenalties.push_back({
        depot,
        load,
        instance.capacity,
        violation
      });
    }

    // metricas por ruta
    result.routeMetrics.push_back({
      routeId,
      depot,
      routeDistance,
      t,
      load
    });

    routeId++;
  }

  result.totalDistance = totalDistance;
  result.totalTimePenalty = timePenalty;
  result.totalCapacityPenalty = capacityPenalty;

  result.objectiveValue =
    totalDistance +
    ALPHA * timePenalty +
    BETA * capacityPenalty;

  return result;
}