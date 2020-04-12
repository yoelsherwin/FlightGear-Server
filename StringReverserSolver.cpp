//
// Created by yoel on 08/01/2020.
//

#include <cstring>
#include "StringReverserSolver.h"

string solve(string problem) {
  string ans = "";
  for (int i = problem.size() - 1; i >= 0; --i) {
    ans += problem[i];
  }
  return ans;
}
string StringReverserSolver::solve(string problem) {
  string ans = "";
  for (int i = problem.size() - 1; i >= 0; --i) {
    if (problem[i] != '\n' && problem[i] != '\r')
      ans += problem[i];
  }
  ans += '\n';
  return ans;
}
