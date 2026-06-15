#include "InstanceProcessor.h"

#include <cmath>

using namespace std;

void process(Instance &instance)
{
  // unificando depots + customers
  instance.allNodes = instance.depots;

  instance.allNodes.insert(
    instance.allNodes.end(),
    instance.customers.begin(),
    instance.customers.end()
  );

  instance.numDepots = instance.depots.size();
  instance.numCustomers = instance.customers.size();

  int n = instance.allNodes.size();

  // matriz de distancias
  instance.dist.assign(n, vector<double>(n, 0.0));

  // se calculan distancias euclidianas
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      double dx = instance.allNodes[i].x - instance.allNodes[j].x;
      double dy = instance.allNodes[i].y - instance.allNodes[j].y;

      instance.dist[i][j] = sqrt(dx * dx + dy * dy);
    }
  }
}