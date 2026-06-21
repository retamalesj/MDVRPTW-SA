#include "Helpers.h"

#include <algorithm>
#include <cctype>

using namespace std;

string trim(const string &str)
{
  auto begin = find_if_not(
    str.begin(),
    str.end(),
    [](unsigned char c)
    {
      return isspace(c);
    });

  auto end = find_if_not(
    str.rbegin(),
    str.rend(),
    [](unsigned char c)
    {
      return isspace(c);
    })
    .base();

  if (begin >= end)
  {
    return "";
  }

  return string(begin, end);
}

int extractNumber(const string &id)
{
  return stoi(id.substr(id.find_first_of("0123456789")));
}