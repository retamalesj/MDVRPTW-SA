#pragma once

#include "Solution.h"
#include "Instance.h"

/**
 * @brief Escribe la solución en formato texto (salida estándar o archivo).
 *
 * Genera un reporte con la solución encontrada, incluyendo la semilla usada,
 * métricas de la solución y tiempo de ejecución.
 *
 * @param SEED Semilla utilizada en el algoritmo.
 * @param sol Solución obtenida por Simulated Annealing.
 * @param instance Instancia del problema.
 * @param ALPHA Factor de penalización de ventanas de tiempo.
 * @param totalTime Tiempo total de ejecución del algoritmo.
 */
void writeSolution(
  unsigned int SEED,
  const Solution& sol,
  const Instance& instance,
  double ALPHA,
  double totalTime
);

/**
 * @brief Verifica si una solución es factible.
 *
 * Comprueba restricciones del MDVRPTW como capacidad de vehículos
 *
 * @param sol Solución a evaluar.
 * @param instance Instancia del problema.
 * @return true si la solución es factible, false en caso contrario.
 */
bool isFeasible(
  const Solution& sol,
  const Instance& instance
);

/**
 * @brief Guarda la solución en un .txt que de forma facil se puede copiar a Excel.
 *
 * Genera un archivo .txt con la información de la solución necesaria
 * que facilita el armar tablas de resultados en Excel
 *
 * @param SEED Semilla utilizada en el algoritmo.
 * @param sol Solución obtenida.
 * @param instance Instancia del problema.
 * @param ALPHA Factor de penalización de ventanas de tiempo.
 * @param totalTime Tiempo total de ejecución del algoritmo.
 */
void writeSolutionExcel(
  unsigned int SEED,
  const Solution& sol,
  const Instance& instance,
  double ALPHA,
  double totalTime
);