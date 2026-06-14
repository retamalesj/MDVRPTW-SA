#pragma once

#include <vector>
#include "Instance.h"

struct Model
{
  // Todos los nodos en un solo arreglo:
  // [0..m-1] depósitos
  // [m..] clientes
  std::vector<Node> allNodes;

  // Matriz de distancias
  std::vector<std::vector<double>> dist;

  int numDepots = 0;
  int numCustomers = 0;
};