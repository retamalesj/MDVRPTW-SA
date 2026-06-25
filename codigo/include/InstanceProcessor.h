#pragma once

#include "Instance.h"

/**
 * @brief Procesa una instancia del problema MDVRPTW.
 *
 * Unifica depósitos y clientes en un único vector de nodos y
 * construye la matriz de distancias euclidianas entre todos los nodos.
 *
 * @param instance Instancia del problema que será modificada
 */
void process(Instance& instance);