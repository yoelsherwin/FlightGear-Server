//
// Created by tal on 7.1.2020.
//

#ifndef MILESTONE2__STATE_H_
#define MILESTONE2__STATE_H_
#include "limits"
template<typename T>
class State {
 public:
  T* state;
  State<T> *prev;
  bool isDiscovered;
  double costOfTrack;
  double fCost;
  State() {}
//  State<T>(T state, double value) : state(state), value(value) {
//    this->isDiscovered = false;
//    this->prev = nullptr;
//  }
  State<T>(T* state1) {
    this->state = state1;
    this->isDiscovered = false;
    this->prev = nullptr;
    costOfTrack = std::numeric_limits<double>::infinity();
    fCost = std::numeric_limits<double>::infinity();
  }

  void SetPrev(State<T> *prev) {
    State::prev = prev;
  }

  bool equals(State<T> state1) {
    return (state1.state == this->state);
  }
};
template<typename T>
class compareStateAStar{
 public:
  bool operator()(State<T>* state1, State<T>* state2){
    return state1->fCost > state2->fCost;
  }
};
template<typename T>

class compareStateBestFirsSearch{
 public:
  bool operator()(State<T>* state1, State<T>* state2){
    return state1->costOfTrack > state2->costOfTrack;
  }
};

#endif //MILESTONE2__STATE_H_
