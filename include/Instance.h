#pragma once

#include <string>
#include <vector>

using namespace std;

struct Node {
    string id;

    double x;
    double y;

    int demand;

    double e; // inicio ventana de tiempo
    double l; // fin ventana de tiempo
    double serviceTime;

    bool isDepot;
};

struct Instance {
    string name;

    int numDepots;
    int numCustomers;
    int vehiclesPerDepot;
    int capacity;

    vector<Node> depots;
    vector<Node> customers;

    // Todos los nodos en un solo arreglo:
    // [0..m-1] depósitos
    // [m..] clientes
    vector<Node> allNodes; // unificación de depósitos y clientes
    
    vector<vector<double>> dist; // matriz de distancias
};