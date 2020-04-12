//
// Created by yoel on 09/01/2020.
//

#ifndef SERVER__MYCLIENTHANDLER_H_
#define SERVER__MYCLIENTHANDLER_H_
#include <vector>
#include "ClientHandler.h"
#include "FileCacheManager.h"
#include "server_side.h"
#include "State.h"
#include "Matrix.h"

//template <typename Problem,typename Solution>
class MyClientHandler : public ClientHandler{
  Solver<Matrix, string>* solver;
  CacheManager<string, string>* cm;
 public:
  MyClientHandler(CacheManager<string, string> *cm1, Solver<Matrix, string>* solver1 ) {
    this->cm = cm1;
    this->solver = solver1;
  }
  void handleClient(int socket) {
    vector<string> lines;
    string matrixString = "";
    string stringToCheck;
    char buffer[10000];
    while (!server_side::GlobalShouldStop) {
      read(socket, buffer, 10000);
      string line(buffer);
      matrixString += line;
      stringToCheck += line;

      for (int i = 0; i < sizeof(buffer); i++) {
        buffer[i] = '\0';
      }

      string temp = matrixString.substr(matrixString.size()-4,3);
      string temp2 = matrixString.substr(matrixString.size()-5,3);
      string temp3 = matrixString.substr(matrixString.size()-3,3);
      if (!strcmp(temp.c_str(), "end") || !strcmp(temp2.c_str(), "end") || !strcmp(temp3.c_str(), "end")) {
        if (!strcmp(temp3.c_str(), "end"))
          matrixString+="\n";
        break;
      }
    }

    matrixString = matrixString.substr(0,matrixString.size()-4);
    auto find = matrixString.find_first_of('\n');
    while (find != string::npos) {
      string line = matrixString.substr(0, find);
      matrixString = matrixString.substr(find + 1, matrixString.size() - (find + 1));
      lines.push_back(line);
      find = matrixString.find('\n');
    }


    //create matrix
    Matrix *matrix = new Matrix(lines);
    string ans;
    int counter = 0;
    //check if we have a solution to the problem in cache
    if (this->cm->isCacheHaveSol(stringToCheck)) {
      ans = this->cm->get(stringToCheck);
    } else {
      ans = this->solver->solve(*matrix);
      this->cm->insert(stringToCheck, ans);
    }

    // make sure every byte was sent to client
    auto size = ans.size();
    auto t = send(socket, ans.c_str(), ans.size(), 0);
    while(t != size) {
      size -= t;
      t = send(socket, ans.c_str(), ans.size(), 0);
    }
    close(socket);
    ans = "";
  }

  virtual ~MyClientHandler() {
    delete (cm);
    delete (solver);
  }
};

#endif //SERVER__MYCLIENTHANDLER_H_
