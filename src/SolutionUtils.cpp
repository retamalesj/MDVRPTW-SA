#include "SolutionUtils.h"
#include "Evaluator.h"

#include <unordered_set>
#include <iostream>

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

  cout << "Penalizacion capacidad: "
       << eval.totalCapacityPenalty << '\n';

  cout << "Vehiculos usados: "
       << eval.routeMetrics.size() << "\n\n";

  cout << "=== RUTAS ===\n";

  for (const RouteMetrics &rm : eval.routeMetrics)
  {
    const Route &route = sol.routes[rm.routeId];

    if (route.customers.empty())
      continue;

    int depot = route.depot;

    cout << "\nDeposito "
         << instance.allNodes[depot].id
         << " (X="
         << instance.allNodes[depot].x
         << ", Y="
         << instance.allNodes[depot].y
         << ")\n";

    cout << "Vehiculo " << (rm.routeId + 1) << '\n';

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

  cout << "\n=== PENALIZACIONES DE CAPACIDAD ===\n";

  if (eval.capacityPenalties.empty())
  {
    cout << "Ninguna\n";
  }
  else
  {
    for (const CapacityPenalty &p : eval.capacityPenalties)
    {
      cout << "Ruta "
           << p.routeId
           << ": carga="
           << p.load
           << ", capacidad="
           << p.capacity
           << ", exceso="
           << p.violation
           << '\n';
    }
  }
}