#pragma once

#include <vector>

using namespace std;

struct Route
{
  int depot;
  vector<int> customers;
};

struct Solution
{
  vector<Route> routes;
};