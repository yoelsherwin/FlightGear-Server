//
// Created by tal on 6.1.2020.
//

#ifndef MILESTONE2__CLIENTHANDLER_H_
#define MILESTONE2__CLIENTHANDLER_H_
#include "iostream"
#include "fstream"
#include "istream"
#include <sys/socket.h>
#include "Solver.h"
using namespace std;
class ClientHandler {

 public:
  virtual void handleClient(int socket) = 0;
  virtual ~ClientHandler() {}
};

#endif //MILESTONE2__CLIENTHANDLER_H_
