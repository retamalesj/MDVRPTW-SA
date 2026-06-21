#pragma once

#include "Solution.h"
#include "Instance.h"

double evaluate(
    const Solution& sol,
    const Instance& instance,
    double ALPHA
);

struct RouteMetrics
{
    int routeId;
    int depotId;

    double distance;
    double time;
    int load;
};

struct TimePenalty
{
    string nodeId;
    bool isDepot;

    double arrivalTime;
    double windowStart;
    double windowEnd;

    double violation;
};

struct CapacityPenalty
{
    int routeId;

    int load;
    int capacity;

    int violation;
};

struct EvaluationResult
{
    double objectiveValue;
    double totalDistance;
    double totalTimePenalty;
    double totalCapacityPenalty;

    vector<RouteMetrics> routeMetrics;
    vector<TimePenalty> timePenalties;
    vector<CapacityPenalty> capacityPenalties;
};

EvaluationResult evaluateWithDetails(
    const Solution& sol,
    const Instance& instance,
    double ALPHA
);
