#include "Parser.h"
#include "Helpers.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <iostream>

using namespace std;

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