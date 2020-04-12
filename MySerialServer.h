//
// Created by tal on 6.1.2020.
//

#ifndef MILESTONE2__MYSERIALSERVER_H_
#define MILESTONE2__MYSERIALSERVER_H_
#include <thread>
#include "server_side.h"
#include <cstring>
template<typename Problem, typename Solution>
void startSerial(int port, ClientHandler *c) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serv;
  serv.sin_addr.s_addr = INADDR_ANY;
  serv.sin_port = htons(port);
  serv.sin_family = AF_INET;
  bool *isTimeOut = new bool;
  *isTimeOut = false;
  timeval timeout;
  timeout.tv_sec = 120;
  timeout.tv_usec = 0;

  bind(s, (sockaddr * ) & serv, sizeof(serv));
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

  while (!server_side::GlobalShouldStop) {
    try {
      int new_sock;
      listen(s, 20000);
      struct sockaddr_in client;
      socklen_t clilen = sizeof(client);
      new_sock = accept(s, (struct sockaddr *) &client, &clilen);
      if (*isTimeOut || new_sock < 0) {
        if (errno == EWOULDBLOCK) {
          cout << "timeout of Serial!" << endl;
          break;
        } else {
          perror("other error");
          break;
        }
      }
      c->handleClient(new_sock);

/*        if (new_sock >= 0) {
          thread *t = new thread(serial, clientHandler, new_sock, isTimeOut);
          t->join();
          delete t;
          *isTimeOut = true;
        }*/
    } catch (...) {
      cout << "connection with client stopped" << endl;
    }
  }
  delete isTimeOut;
}
template<typename Problem, typename Solution>
class MySerialServer : server_side::Server<Problem, Solution> {
  thread thr1;
  bool shouldStop = false;
 public:
  void open(int port, ClientHandler *c) override {
    server_side::GlobalShouldStop = false;
    thread thr(startSerial<Problem, Solution>, port, c);
    thr.join();
  }
  void stop() override {
    server_side::GlobalShouldStop = true;
    if (this->thr1.joinable()) {
      this->thr1.join();
    }
  }
};

#endif //MILESTONE2__MYSERIALSERVER_H_
