#pragma once

#include "Solution.h"
#include "Instance.h"

#include <random>

/**
 * @brief Construye una solución inicial aleatoria para el MDVRPTW.
 *
 * Genera una solución factible inicial asignando clientes de forma aleatoria
 * a rutas disponibles, respetando la estructura de la instancia.
 *
 * @param instance Instancia del problema.
 * @param rng Generador de números aleatorios.
 * @return Solución inicial generada aleatoriamente.
 */
Solution buildRandomSolution(
  const Instance& instance,
  mt19937& rng
);