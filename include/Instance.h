#pragma once

#include <string>
#include <vector>

struct Node {
    std::string id;

    double x;
    double y;

    int demand;

    double e;
    double l;
    double serviceTime;

    bool isDepot;
};

struct Instance {
    std::string name;

    int numDepots;
    int vehiclesPerDepot;
    int capacity;

    std::vector<Node> depots;
    std::vector<Node> customers;
};