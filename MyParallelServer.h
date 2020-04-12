//
// Created by yoel on 14/01/2020.
//

#ifndef SERVER__MYPARALLELSERVER_H_
#define SERVER__MYPARALLELSERVER_H_
#include <thread>
#include "server_side.h"
#include <string.h>
#include "vector"
struct dataForClient {
  ClientHandler *client;
  int socket;
};
/*template<typename Problem, typename Solution>
void playThread(ClientHandler *client, int socket) {
  client->handleClient(socket);
}*/
template<typename Problem, typename Solution>
void playThread(dataForClient *data) {
  data->client->handleClient(data->socket);
}
template<typename Problem, typename Solution>
void startParallel(int port, ClientHandler *c) {
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

  bind(s, (sockaddr *) &serv, sizeof(serv));
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
      server_side::threads.push_back(new thread);
      ClientHandler *client_handler = c;
      struct dataForClient *data = new struct dataForClient();
      data->client = client_handler;
      data->socket = new_sock;
      server_side::threads[server_side::threads.size() - 1] = new thread(playThread<Problem, Solution>, data);
    } catch (...) {
      cout << "connection with client stopped" << endl;
    }
  }
  delete isTimeOut;
}

template<typename Problem, typename Solution>
class MyParallelServer : server_side::Server<Problem, Solution> {
  bool shouldStop = false;
 public:
  void open(int port, ClientHandler *c) override {
    server_side::GlobalShouldStop = false;
    thread thr(startParallel<Problem, Solution>, port, c);
    thr.join();
  }
  void stop() override {
    server_side::GlobalShouldStop = true;
  }
};

#endif //SERVER__MYPARALLELSERVER_H_
