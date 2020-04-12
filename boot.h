//
// Created by yoel on 08/01/2020.
//

#ifndef MILESTONE2__BOOT_H_
#define MILESTONE2__BOOT_H_
#include <iostream>
#include "server_side.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "StringReverserSolver.h"
#include "BFS.h"
#include "DFS.h"
#include "SearchSolver.h"
#include "AStar.h"
namespace boot {
class Main {
 public:
  Main() {}
  int main1(int argc, char **argv) {
    CacheManager<string, string> *cm = new FileCacheManager();
    Solver<Matrix, string> *solver = new SearchSolver(new AStar<Point>());
    MyClientHandler *c = new MyClientHandler(cm, solver);
    MySerialServer<Matrix, string> s;
    if (argc > 1)
      s.open(atoi(argv[1]), c);
    else
      s.open(5600, c);
  }
};
};

#endif //MILESTONE2__BOOT_H_