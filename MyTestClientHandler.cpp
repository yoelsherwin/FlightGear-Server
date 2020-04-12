//
// Created by tal on 6.1.2020.
//


#include "MyTestClientHandler.h"
#include "string.h"
#include "server_side.h"
/*
template<typename Problem, typename Solution>
MyTestClientHandler<Problem, Solution>::~MyTestClientHandler() {
  delete(cm);
  delete(solver);
}

template<typename Problem, typename Solution>
MyTestClientHandler<Problem, Solution>::MyTestClientHandler(CacheManager<Problem, Solution> *cm1, Solver<Problem,Solution>* solver1 ) {
  this->cm = cm1;
  this->solver = solver1;
}

template<typename Problem, typename Solution>
void MyTestClientHandler<Problem, Solution>::handleClient(string prob, string ans) {
  if(this->cm->isCacheHaveSol(prob)){
    ans = this->cm->get(prob);
  } else{
    ans = this->solver->solve(prob);
    this->cm->insert(prob,ans);
  }
/*  while(!server_side::GlobalShouldStop) {
    char buf[1024];
    // receiving message from client
    int numBytesRead = recv(socket, buf, sizeof(buf), 0);
    if(numBytesRead > 0) {

    }
  }*/
