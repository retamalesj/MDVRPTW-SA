#pragma once

#include "Solution.h"
#include "Model.h"

double evaluateSolution(
    const Solution& sol,
    const Model& model,
    int capacity,
    double ALPHA,
    double BETA
);