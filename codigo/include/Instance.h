#pragma once

#include <string>
#include <vector>

using namespace std;

/**
 * @brief Representa un nodo de la instancia.
 *
 * Un nodo puede corresponder a un depósito o a un cliente.
 */
struct Node {
    /// Identificador del nodo.
    string id;

    /// Coordenada X.
    double x;

    /// Coordenada Y.
    double y;

    /// Demanda del cliente (0 para depósitos).
    int demand;

    /// Inicio de la ventana de tiempo.
    double e;

    /// Fin de la ventana de tiempo.
    double l;

    /// Tiempo de servicio en el nodo.
    double serviceTime;

    /// Indica si el nodo corresponde a un depósito o cliente.
    bool isDepot;
};

/**
 * @brief Representa una instancia del problema MDVRPTW.
 */
struct Instance {
    /// Nombre de la instancia.
    string name;

    /// Número de depósitos.
    int numDepots;

    /// Número de clientes.
    int numCustomers;

    /// Número de vehículos disponibles por depósito.
    int vehiclesPerDepot;

    /// Capacidad máxima de cada vehículo.
    int capacity;

    /// Lista de depósitos.
    vector<Node> depots;

    /// Lista de clientes.
    vector<Node> customers;

    // Todos los nodos en un solo arreglo:
    // [0..m-1] depósitos
    // [m..] clientes
    vector<Node> allNodes; // unificación de depósitos y clientes
    
    vector<vector<double>> dist; // matriz de distancias
};