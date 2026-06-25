#pragma once

#include "Solution.h"
#include "Instance.h"

#include <random>

using namespace std;

/**
 * @brief Aplica un movimiento Relocate sobre una solución.
 *
 * Selecciona aleatoriamente un cliente de una ruta origen y lo inserta
 * en una posición aleatoria de otra ruta distinta.
 *
 * @param sol Solución a modificar.
 * @param rng Generador de números aleatorios.
 * @return true si el movimiento fue aplicado, false en caso contrario.
 */
bool relocateMove(
  Solution& sol,
  mt19937& rng);

/**
 * @brief Aplica un movimiento de intercambio (swap) dentro de una ruta.
 *
 * Selecciona dos clientes aleatorios dentro de la misma ruta e intercambia
 * sus posiciones.
 *
 * @param sol Solución a modificar.
 * @param rng Generador de números aleatorios.
 * @return true si el movimiento fue aplicado, false en caso contrario.
 */
bool swapMove(
  Solution& sol,
  mt19937& rng);

/**
 * @brief Divide una ruta en dos rutas (split move).
 *
 * Selecciona una ruta con al menos dos clientes y la divide en dos partes,
 * creando una nueva ruta con parte de los clientes.
 *
 * @param sol Solución a modificar.
 * @param instance Instancia del problema (usada para límites de vehículos).
 * @param rng Generador de números aleatorios.
 * @return true si el movimiento fue aplicado, false en caso contrario.
 */
bool splitMove(
  Solution& sol,
  const Instance& instance,
  mt19937& rng);