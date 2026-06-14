#include "ModelBuilder.h"

#include <cmath>

using namespace std;

Model buildModel(const Instance &instance)
{
  Model model;

  // unificando depots + customers
  model.allNodes = instance.depots;

  model.allNodes.insert(
    model.allNodes.end(),
    instance.customers.begin(),
    instance.customers.end()
  );

  model.numDepots = instance.depots.size();
  model.numCustomers = instance.customers.size();

  int n = model.allNodes.size();

  // matriz de distancias
  model.dist.assign(n, vector<double>(n, 0.0));

  // se calculan distancias euclidianas
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      double dx = model.allNodes[i].x - model.allNodes[j].x;
      double dy = model.allNodes[i].y - model.allNodes[j].y;

      model.dist[i][j] = sqrt(dx * dx + dy * dy);
    }
  }

  return model;
}