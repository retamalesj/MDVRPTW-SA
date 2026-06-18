#include "Moves.h"

using namespace std;

bool relocateMove(
    Solution &sol,
    mt19937 &rng)
{
  if (sol.routes.size() < 2)
    return false;

  uniform_int_distribution<int> routeDist(0, sol.routes.size() - 1);

  int originRouteId = routeDist(rng);
  int destinationRouteId = routeDist(rng);

  while (originRouteId == destinationRouteId)
  {
    destinationRouteId = routeDist(rng);
  }

  Route &originRoute = sol.routes[originRouteId];
  Route &destinationRoute = sol.routes[destinationRouteId];

  if (originRoute.customers.empty())
    return false;

  uniform_int_distribution<int> customerDist(0, originRoute.customers.size() - 1);

  int customerPos = customerDist(rng);
  int customer = originRoute.customers[customerPos];

  originRoute.customers.erase(originRoute.customers.begin() + customerPos);

  uniform_int_distribution<int> insertPosDist(0, destinationRoute.customers.size());

  int insertPos = insertPosDist(rng);

  destinationRoute.customers.insert(destinationRoute.customers.begin() + insertPos, customer);

  // si la ruta de origen queda vacía se elimina.
  if (sol.routes[originRouteId].customers.empty())
  {
    sol.routes.erase(sol.routes.begin() + originRouteId);
  }

  return true;
}

bool swapMove(
  Solution &sol,
  mt19937 &rng)
{
  if (sol.routes.empty())
    return false;

  uniform_int_distribution<int> routeDist(0, sol.routes.size() - 1);

  // se selecciona ruta aleatoria
  int routeId = routeDist(rng);
  Route &route = sol.routes[routeId];

  if (route.customers.size() < 2) return false; // no hay suficientes clientes para el swap

  uniform_int_distribution<int> customerDist(0, route.customers.size() - 1);

  int i = customerDist(rng);
  int j = customerDist(rng);

  while (i == j) j = customerDist(rng);

  swap(route.customers[i], route.customers[j]);

  return true;
}

// bool splitMove(
//     Solution &sol,
//     mt19937 &rng)
// {
//   // implementación
// }