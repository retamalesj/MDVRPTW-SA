#include "Parser.h"
#include "Helpers.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <iostream>

using namespace std;

/**
 * @brief Busca una sección específica dentro del archivo.
 *
 * Avanza línea por línea hasta encontrar el nombre de la sección indicada.
 *
 * @param file Archivo abierto en modo lectura.
 * @param section Nombre de la sección a buscar.
 * @throws runtime_error si la sección no se encuentra.
 */
static void findSection(ifstream &file, const string &section)
{
  string line;

  while (getline(file, line))
  {
    if (trim(line) == section)
      return;
  }

  throw runtime_error("Sección no encontrada: " + section);
}

/**
 * @brief Parsea una línea del archivo y la convierte en un nodo.
 *
 * Convierte una línea de texto en un objeto Node con sus atributos
 * (id, coordenadas, demanda y ventanas de tiempo...).
 *
 * @param line Línea del archivo.
 * @param isDepot Indica si el nodo corresponde a un depósito.
 * @return Nodo construido a partir de la línea.
 */
static Node parseNode(const string &line, bool isDepot)
{
  Node node;

  stringstream ss(line);

  ss >> node.id >> node.x >> node.y >> node.demand >> node.e >> node.l >> node.serviceTime;

  if (ss.fail())
    throw runtime_error("Línea inválida: " + line);

  node.isDepot = isDepot;

  return node;
}

/**
 * @brief Lee una instancia del problema MDVRPTW desde un archivo.
 *
 * El archivo debe contener:
 * - Nombre de la instancia
 * - Parámetros generales (depósitos, vehículos por deposito, capacidad del vehiculo)
 * - Sección DEPOSITOS
 * - Sección CLIENTES
 *
 * @param filename Ruta del archivo de entrada.
 * @return Instancia construida en memoria.
 */
Instance readInstance(const string &filename)
{
  ifstream file(filename);

  if (!file) throw runtime_error("No se pudo abrir: " + filename);

  Instance instance;
  string line;

  // Nombre
  while (getline(file, line) && line.empty()) {}
  instance.name = line;

  // Parámetros
  while (getline(file, line))
  {
    if (line.find("DEPOSITOS:") != string::npos)
    {
      sscanf(
        line.c_str(),
        "DEPOSITOS: %d VEHICULOS_POR_DEPOSITO: %d CAPACIDAD: %d",
        &instance.numDepots,
        &instance.vehiclesPerDepot,
        &instance.capacity
      );
      break;
    }
  }

  findSection(file, "DEPOSITOS");
  getline(file, line); // encabezado

  for (int i = 0; i < instance.numDepots;)
  {
    getline(file, line);

    if (line.empty()) continue;

    instance.depots.push_back(parseNode(line, true));
    ++i;
  }

  findSection(file, "CLIENTES");
  getline(file, line); // encabezado

  while (getline(file, line))
  {
    if (line.empty()) continue;

    instance.customers.push_back(parseNode(line, false));
  }

  return instance;
}