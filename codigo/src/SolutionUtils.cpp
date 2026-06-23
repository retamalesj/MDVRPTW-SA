#include "SolutionUtils.h"
#include "Evaluator.h"
#include "Helpers.h"

#include <unordered_set>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

void writeSolution(
    unsigned int SEED,
    const Solution &sol,
    const Instance &instance,
    double ALPHA)
{
  EvaluationResult eval = evaluateWithDetails(sol, instance, ALPHA);

  ostringstream out;

  out << "\n========== SOLUCION ==========\n\n";
  out << "Semilla: " << SEED << '\n';

  out << "Instancia: " << instance.name << '\n';

  out << "Valor Funcion Objetivo: "
       << eval.objectiveValue << '\n';

  out << "Distancia total recorrida: "
       << eval.totalDistance << '\n';

  out << "Penalizacion tiempo: "
       << eval.totalTimePenalty << '\n';

  out << "Vehiculos usados: "
       << eval.routeMetrics.size() << "\n\n";

  out << "=== RUTAS ===\n";

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

    out << "\nDeposito "
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

      out << "\nVehiculo " << (rm.routeId + 1) << '\n';

      out << "Ruta: "
           << instance.allNodes[depot].id;

      for (int c : route.customers)
      {
        out << " -> "
             << instance.allNodes[c].id;
      }

      out << " -> "
           << instance.allNodes[depot].id
           << '\n';

      out << "Carga: "
           << rm.load
           << " / "
           << instance.capacity
           << '\n';

      out << "Distancia: "
           << rm.distance
           << '\n';

      out << "Tiempo: "
           << rm.time
           << '\n';
    }
  }

  set<string> penalizedNodes;

  out << "\n=== PENALIZACIONES DE TIEMPO ===\n";
  if (eval.timePenalties.empty())
  {
    out << "Ninguna\n";
  }
  else
  {
    vector<TimePenalty> sorted = eval.timePenalties;

    sort(sorted.begin(), sorted.end(),
        [](const TimePenalty &a, const TimePenalty &b)
        {
          return extractNumber(a.nodeId) < extractNumber(b.nodeId);
        });

    for (const TimePenalty &p : sorted)
    {
      if (!p.isDepot) penalizedNodes.insert(p.nodeId);

      out << (p.isDepot ? "Deposito " : "Cliente ")
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

  out << "\nTotal nodos penalizados: " << penalizedNodes.size() << "\n";
  

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

  string text = out.str();

  cout << text;

  string filename = "./Soluciones/instancias_" + to_string(instance.numCustomers) + "/" + instance.name + ".txt";
  ofstream file(filename);

  if (file)
  {
      file << text;
  }
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