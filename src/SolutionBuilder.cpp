#include "SolutionBuilder.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>

using namespace std;

Solution buildRandomSolution(
    const Model &model,
    int vehiclesPerDepot,
    int capacity,
    unsigned int seed)
{
  mt19937 rng(seed);

  Solution sol;

  int numDepots = model.numDepots;
  int numNodes = model.allNodes.size();

  int firstCustomer = numDepots;

  int maxRoutes = numDepots * vehiclesPerDepot;

  // Lista de clientes
  vector<int> customers;

  for (int i = firstCustomer; i < numNodes; i++)
  {
    customers.push_back(i);
  }

  shuffle(customers.begin(), customers.end(), rng);

  // Carga de cada ruta
  vector<int> load;

  // Para elegir depósito al crear una ruta nueva
  uniform_int_distribution<int> depotDist(0, numDepots - 1);

  for (int c : customers)
  {
    int demand = model.allNodes[c].demand;

    bool assigned = false;

    // Intentar insertar en una ruta existente
    vector<int> candidates(sol.routes.size());

    iota(candidates.begin(), candidates.end(), 0);

    shuffle(candidates.begin(), candidates.end(), rng);

    for (int rIdx : candidates)
    {
      if (load[rIdx] + demand <= capacity)
      {
        sol.routes[rIdx].customers.push_back(c);
        load[rIdx] += demand;

        assigned = true;
        break;
      }
    }

    // Si no cabe en ninguna, crear una nueva ruta
    if (!assigned)
    {
      if ((int)sol.routes.size() < maxRoutes)
      {
        Route route;

        // Buscar depósito más cercano al cliente c
        int bestDepot = 0;
        double bestDist = model.dist[0][c];

        cout << "\nCliente: " << model.allNodes[c].id << '\n';

        cout << "Depot "
             << model.allNodes[0].id
             << " -> distancia = "
             << model.dist[0][c]
             << '\n';

        for (int d = 1; d < model.numDepots; d++)
        {
          cout << "Depot "
               << model.allNodes[d].id
               << " -> distancia = "
               << model.dist[d][c]
               << '\n';

          if (model.dist[d][c] < bestDist)
          {
            bestDist = model.dist[d][c];
            bestDepot = d;
          }
        }

        cout << "Seleccionado: "
             << model.allNodes[bestDepot].id
             << " (distancia = "
             << bestDist
             << ")\n";

        route.depot = bestDepot;
        route.customers.push_back(c);

        sol.routes.push_back(route);
        load.push_back(demand);
      }
      else
      {
        // Ya no quedan vehículos disponibles
        // Lo metemos donde menos daño haga
        int bestRoute = 0;

        for (int i = 1; i < (int)load.size(); i++)
        {
          if (load[i] < load[bestRoute])
          {
            bestRoute = i;
          }
        }

        sol.routes[bestRoute].customers.push_back(c);
        load[bestRoute] += demand;
      }
    }
  }

  return sol;
}