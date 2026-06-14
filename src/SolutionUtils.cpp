#include "SolutionUtils.h"

#include <unordered_set>
#include <iostream>

using namespace std;

bool isValidSolution(const Solution &sol, const Model &model)
{
  unordered_set<int> visited;

  int numNodes = model.allNodes.size();
  int numDepots = model.numDepots;

  int firstCustomer = numDepots;

  for (const auto &route : sol.routes)
  {
    for (int c : route.customers)
    {
      // índice fuera de rango
      if (c < 0 || c >= numNodes)
      {
        cout << "Cliente fuera de rango: " << c << "\n";
        return false;
      }

      // no debe ser depósito
      if (c < firstCustomer)
      {
        cout << "Nodo inválido (es depósito): " << c << "\n";
        return false;
      }

      // clientes duplicados
      if (visited.count(c))
      {
        cout << "Cliente repetido: " << c << "\n";
        return false;
      }

      visited.insert(c);
    }
  }

  // todos los clientes deben estar presentes
  for (int i = firstCustomer; i < numNodes; i++)
  {
    if (!visited.count(i))
    {
      cout << "Cliente faltante: " << i << "\n";
      return false;
    }
  }

  return true;
}