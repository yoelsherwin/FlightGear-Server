//
// Created by tal on 7.1.2020.
//

#ifndef MILESTONE2__SEARCHABLE_H_
#define MILESTONE2__SEARCHABLE_H_
#include "State.h"
#include "list"
#include "vector"
#include "string"
using namespace std;
template <typename T>
class Searchable {
 public:
  virtual State<T>* getInitialState () = 0;

  virtual State<T>* getGoalState() = 0;

  virtual vector<State<T>*> getSuccessors(State<T>* s) = 0;

  virtual string traceBack() {
    return "";
  }
};

#endif //MILESTONE2__SEARCHABLE_H_
