#pragma once

#include <string>
#include "Instance.h"

/**
 * @brief Lee una instancia del problema MDVRPTW desde un archivo.
 *
 * Parsea el archivo de entrada y construye una estructura Instance con
 * depósitos, clientes y parámetros del problema.
 *
 * @param filename Ruta del archivo de la instancia.
 * @return Instancia cargada en memoria.
 */
Instance readInstance(const std::string& filename);