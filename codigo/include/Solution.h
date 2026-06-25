#pragma once

#include <vector>

using namespace std;

/**
 * @brief Representa una ruta de un vehículo en la solución.
 *
 * Cada ruta está asociada a un depósito y contiene una secuencia
 * ordenada de clientes a visitar.
 */
struct Route
{
  /// Identificador del depósito asociado a la ruta.
  int depot;

  /// Lista ordenada de clientes visitados en la ruta.
  vector<int> customers;
};

/**
 * @brief Representa una solución del problema MDVRPTW.
 *
 * Una solución está compuesta por múltiples rutas, una por cada vehículo utilizado.
 */
struct Solution
{
  /// Conjunto de rutas que componen la solución.
  vector<Route> routes;
};