#pragma once

#include <string>

using namespace std;

/**
 * @brief Elimina los espacios en blanco al inicio y al final de una cadena.
 *
 * @param str Cadena de entrada.
 * @return Cadena sin espacios en blanco en los extremos.
 */
string trim(const string& str);

/**
 * @brief Extrae el número contenido en un identificador.
 *
 * Obtiene la parte numérica de una cadena cuyo formato contiene un prefijo
 * seguido de un número (por ejemplo, "C12" o "D3").
 * Se usa para extraer el número del ID del Depot ya que su id viene como string "D1" por ejemplo.
 * 
 *
 * @param id Identificador del cual extraer el número.
 * @return Número entero contenido en el identificador.
 */
int extractNumber(const string &id);