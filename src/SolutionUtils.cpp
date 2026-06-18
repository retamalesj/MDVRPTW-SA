#include "SolutionUtils.h"
#include "Evaluator.h"

#include <unordered_set>
#include <iostream>
#include <map>

using namespace std;

void writeSolution(
    unsigned int SEED,
    const Solution &sol,
    const Instance &instance,
    double ALPHA,
    double BETA)
{
  EvaluationResult eval = evaluateWithDetails(sol, instance, ALPHA, BETA);

  cout << "\n========== SOLUCION ==========\n\n";
  cout << "Semilla: " << SEED << '\n';

  cout << "Instancia: " << instance.name << '\n';

  cout << "Valor Funcion Objetivo: "
       << eval.objectiveValue << '\n';

  cout << "Distancia total recorrida: "
       << eval.totalDistance << '\n';

  cout << "Penalizacion tiempo: "
       << eval.totalTimePenalty << '\n';

  cout << "Vehiculos usados: "
       << eval.routeMetrics.size() << "\n\n";

  cout << "=== RUTAS ===\n";

  // Agrupar por depósito
  map<int, vector<const RouteMetrics *>> byDepot;

  for (const RouteMetrics &rm : eval.routeMetrics)
  {
    const Route &route = sol.routes[rm.routeId];
    byDepot[route.depot].push_back(&rm);
  }

  for (const auto &entry : byDepot)
  {
    int depot = entry.first;

    cout << "\nDeposito "
         << instance.allNodes[depot].id
         << " (X="
         << instance.allNodes[depot].x
         << ", Y="
         << instance.allNodes[depot].y
         << ")";

    for (const RouteMetrics *rmPtr : entry.second)
    {
      const RouteMetrics &rm = *rmPtr;
      const Route &route = sol.routes[rm.routeId];

      cout << "\nVehiculo " << (rm.routeId + 1) << '\n';

      cout << "Ruta: "
           << instance.allNodes[depot].id;

      for (int c : route.customers)
      {
        cout << " -> "
             << instance.allNodes[c].id;
      }

      cout << " -> "
           << instance.allNodes[depot].id
           << '\n';

      cout << "Carga: "
           << rm.load
           << " / "
           << instance.capacity
           << '\n';

      cout << "Distancia: "
           << rm.distance
           << '\n';

      cout << "Tiempo: "
           << rm.time
           << '\n';
    }
  }

  cout << "\n=== PENALIZACIONES DE TIEMPO ===\n";

  if (eval.timePenalties.empty())
  {
    cout << "Ninguna\n";
  }
  else
  {
    for (const TimePenalty &p : eval.timePenalties)
    {
      cout << (p.isDepot ? "Deposito " : "Cliente ")
           << p.nodeId
           << ": llegada="
           << p.arrivalTime
           << ", ventana=["
           << p.windowStart
           << ", "
           << p.windowEnd
           << "]"
           << ", tardanza="
           << p.violation
           << '\n';
    }
  }

  // cout << "\n=== PENALIZACIONES DE CAPACIDAD ===\n";

  // if (eval.capacityPenalties.empty())
  // {
  //   cout << "Ninguna\n";
  // }
  // else
  // {
  //   for (const CapacityPenalty &p : eval.capacityPenalties)
  //   {
  //     cout << "Ruta "
  //          << p.routeId
  //          << ": carga="
  //          << p.load
  //          << ", capacidad="
  //          << p.capacity
  //          << ", exceso="
  //          << p.violation
  //          << '\n';
  //   }
  // }
}

bool isFeasible(
  const Solution &sol,
  const Instance &instance)
{
  for (const Route &route : sol.routes)
  {
    int load = 0;

    for (int customer : route.customers)
    {
      load += instance.allNodes[customer].demand;
    }

    if (load > instance.capacity)
    {
      return false;
    }
  }

  return true;
}