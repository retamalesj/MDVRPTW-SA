#pragma once

#include "Solution.h"
#include "Instance.h"

/**
 * @brief Evalúa una solución del problema MDVRPTW devolviendo solo valor de la FO.
 *
 * Calcula la función objetivo considerando la distancia total recorrida y
 * la penalización asociada a las violaciones de las ventanas de tiempo.
 *
 * @param sol Solución a evaluar.
 * @param instance Instancia del problema.
 * @param ALPHA Factor de penalización para las violaciones de ventanas de tiempo.
 * @return Valor de la función objetivo de la solución.
 */
double evaluate(
    const Solution& sol,
    const Instance& instance,
    double ALPHA
);

/**
 * @brief Métricas obtenidas para una ruta durante la evaluación.
 */
struct RouteMetrics
{
    /// Identificador de la ruta.
    int routeId;

    /// Identificador del depósito asociado a la ruta.
    int depotId;

    /// Distancia total recorrida por la ruta.
    double distance;

    /// Tiempo total empleado por la ruta.
    double time;

    /// Carga total transportada en la ruta.
    int load;
};

/**
 * @brief Información de una violación de ventana de tiempo.
 */
struct TimePenalty
{
    /// Identificador del nodo donde ocurre la violación.
    string nodeId;

    /// Indica si el nodo corresponde a un depósito.
    bool isDepot;

    /// Tiempo de llegada al nodo.
    double arrivalTime;

    /// Inicio de la ventana de tiempo.
    double windowStart;

    /// Fin de la ventana de tiempo.
    double windowEnd;

    /// Magnitud de la violación de la ventana de tiempo.
    double violation;
};

/**
 * @brief Resultado detallado de la evaluación de una solución.
 */
struct EvaluationResult
{
    /// Valor de la función objetivo.
    double objectiveValue;

    /// Distancia total recorrida.
    double totalDistance;

    /// Penalización total por violaciones de ventanas de tiempo.
    double totalTimePenalty;

    /// Métricas de cada ruta evaluada.
    vector<RouteMetrics> routeMetrics;

    /// Detalle de las violaciones de ventanas de tiempo.
    vector<TimePenalty> timePenalties;
};

/**
 * @brief Evalúa una solución del problema MDVRPTW y devuelve información detallada.
 *
 * Además de calcular el valor de la función objetivo, retorna métricas por
 * ruta y el detalle de todas las violaciones de las ventanas de tiempo
 * detectadas durante la evaluación. Sirve para mostrar la solución final.
 *
 * @param sol Solución a evaluar.
 * @param instance Instancia del problema.
 * @param ALPHA Factor de penalización para las violaciones de ventanas de tiempo.
 * @return Resultado detallado de la evaluación.
 */
EvaluationResult evaluateWithDetails(
    const Solution& sol,
    const Instance& instance,
    double ALPHA
);