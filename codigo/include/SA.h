#pragma once

#include "Solution.h"
#include "Instance.h"

#include <random>

/**
 * @brief Parámetros del algoritmo Simulated Annealing.
 */
struct Parameters
{
  /// Constante de penalización para violaciones de tiempo.
  double ALPHA;

  /// Temperatura inicial del algoritmo.
  double initialTemperature;

  /// Tasa de enfriamiento (Ti+1 = Ti * coolingRate).
  double coolingRate;

  /// Número máximo de iteraciones.
  int maxIterations;

  /// Intervalo de iteraciones entre enfriamientos.
  int coolingInterval;

  /// Número máximo de iteraciones sin mejora (estancamiento).
  int maxStagnation;
};

/**
 * @brief Ejecuta el algoritmo Simulated Annealing para el MDVRPTW.
 *
 * A partir de una solución inicial, explora el espacio de soluciones
 * aplicando un proceso de enfriamiento controlado para minimizar la
 * función objetivo del problema, junto a un proceso de recalentamiento
 * para exploración en caso de estancamiento.
 *
 * @param initialSolution Solución inicial.
 * @param instance Instancia del problema.
 * @param parameters Parámetros del algoritmo.
 * @param rng Generador aleatorio.
 * @return Mejor solución encontrada Sbest.
 */
Solution simulatedAnnealing(
  const Solution& initialSolution,
  const Instance& instance,
  const Parameters& parameters,
  mt19937& rng
);