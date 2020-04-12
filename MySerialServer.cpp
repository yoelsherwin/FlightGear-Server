//
// Created by tal on 6.1.2020.
//

#include "MySerialServer.h"
#include "time.h"
#include <utime.h>
/*
void MySerialServer::open(int port, ClientHandler<Problem,Solution *c) {
  GlobalShouldStop = false;
  thread thr(start, port, c);
  thr.join();
}
*/

//static bool GlobalShouldStop = false;
/*template <typename Problem,typename Solution>
void start(int port, ClientHandler<Problem, Solution> *c) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serv;
  serv.sin_addr.s_addr = INADDR_ANY;
  serv.sin_port = htons(port);
  serv.sin_family = AF_INET;
  bool *isTimeOut = new bool;
  *isTimeOut = false;
  char buffer[2900];
  timeval timeout;
  timeout.tv_sec = 50;
  timeout.tv_usec = 0;

  bind(s, (sockaddr *) &serv, sizeof(serv));
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

  while (!GlobalShouldStop) {
    try {
      int new_sock;
      listen(s, 20000);
      struct sockaddr_in client;
      socklen_t clilen = sizeof(client);
      new_sock = accept(s, (struct sockaddr *) &client, &clilen);
      cout << "Server connected" << endl;
      if (*isTimeOut) {
        if (new_sock < 0) {
          if (errno == EWOULDBLOCK) {
            cout << "timeout of Serial!" << endl;
            break;
          } else {
            perror("other error");
            break;
          }
        }
      }

*//*        if (new_sock >= 0) {
          thread *t = new thread(serial, clientHandler, new_sock, isTimeOut);
          t->join();
          delete t;
          *isTimeOut = true;
        }*//*
      while (!GlobalShouldStop) {
        read(new_sock, buffer, 1024);
        string prob(buffer);
        if (prob.compare("end") == 0) {
          GlobalShouldStop = true;
          break;
        }
        if (prob.size() > 0) {
          auto *answer = new string;
          c->handleClient(prob, answer);
          //write(new_sock, answer.c_str(), answer.size());
          send(new_sock,(*answer).c_str(),(*answer).size(),0);
          delete answer;
        }
      }
    } catch (...) {
      cout << "connection with client stopped" << endl;
    }
  }
  delete isTimeOut;
}*/
/*
void MySerialServer<Solution,Problem::stop() {
  GlobalShouldStop = true;
  if (this->thr1.joinable()) {
    this->thr1.join();
  }
}*/
