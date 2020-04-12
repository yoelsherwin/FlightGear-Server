//
// Created by tal on 6.1.2020.
//

#ifndef MILESTONE2__MYTESTCLIENTHANDLER_H_
#define MILESTONE2__MYTESTCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "FileCacheManager.h"
#include "server_side.h"
template <typename Problem, typename Solution>
class MyTestClientHandler : public ClientHandler {
  Solver<Problem, Solution>* solver;
  CacheManager<Problem, Solution>* cm;
 public:
  MyTestClientHandler(CacheManager<Problem, Solution> *cm1, Solver<Problem,Solution>* solver1 ) {
    this->cm = cm1;
    this->solver = solver1;
  }
  void handleClient(int socket) {
    char buffer[2900];
    while (!server_side::GlobalShouldStop) {
      read(socket, buffer, 1024);
      string prob(buffer);
      for (int i = 0; i < sizeof(buffer); i++) {
        buffer[i] = '\0';
      }
      if (!strcmp(prob.c_str(), "end\r\n")) {
        //GlobalShouldStop = true;
        close(socket);
        break;
      }
      if (prob.size() > 0) {
        string ans;
        if (this->cm->isCacheHaveSol(prob)) {
          ans = this->cm->get(prob);
        } else {
          ans = this->solver->solve(prob);
          this->cm->insert(prob, ans);
        }
        //write(new_sock, answer.c_str(), answer.size());
        send(socket, ans.c_str(), ans.size(), 0);
      }
    }
  }

  ~MyTestClientHandler() {
    delete(cm);
    delete(solver);
  }

};

#endif //MILESTONE2__MYTESTCLIENTHANDLER_H_
