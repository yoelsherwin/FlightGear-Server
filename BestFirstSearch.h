//
// Created by tal on 7.1.2020.
//

#ifndef MILESTONE2__BESTFIRSTSEARCH_H_
#define MILESTONE2__BESTFIRSTSEARCH_H_
#include "iSearcher.h"
#include "queue"
#include "stack"
#include "set"
#include "iostream"

template<typename T>
class BestFirstSearch : public iSearcher<T> {
  void pushToOpenQue(State<T> *state, set<State<T> *> *openSet,
                     priority_queue<State<T> *, vector<State<T> *>, compareStateBestFirsSearch<T>> *openQue) {
    openSet->insert(state);
    openQue->push(state);
  }

  void addToClosedSet(State<T> *newVal, set<State<T> *> *closedSet) {
    closedSet->insert(newVal);
  }

  bool isInClosedSet(State<T> *state, set<State<T> *> closedSet) {
    return (closedSet.find(state) != closedSet.end());
  }
  bool isInOpenSet(State<T> *state, set<State<T> *> openSet) {
    return (openSet.count(state));
  }
  State<T> *popOpenList(set<State<T> *> *openSet,
      priority_queue<State<T> *, vector<State<T> *>, compareStateBestFirsSearch<T>> *openQue) {
    State<T> *tempState = openQue->top();
    openQue->pop();
    openSet->erase(tempState);
    return tempState;
  }
  void updateOpenQue(State<T> *state, set<State<T> *> *openSet,
      priority_queue<State<T> *, vector<State<T> *>, compareStateBestFirsSearch<T>> *openQue) {
    stack<State<T> *> tempStack;
    while (!openQue->empty()) {
      tempStack.push(popOpenList(&openSet, &openQue));
    }
    while (!tempStack.empty()) {
      openQue->push(tempStack.top());
      openSet->insert(tempStack.top());
      tempStack.pop();
    }
  }
  void addToOpenList(State<T> *state, set<State<T> *> *openSet,
      priority_queue<State<T> *, vector<State<T> *>, compareStateBestFirsSearch<T>> *openQue) {
    openQue->push(state);
    openSet->insert(state);
  }
 public:
  State<T> *search(Searchable<T> *search_able) override {
    priority_queue<State<T> *, vector<State<T> *>, compareStateBestFirsSearch<T>> openQue;
    set<State<T> *> closedSet;
    set<State<T> *> openSet;
    vector<State<T> *> listOfSuccessors;

    //pushToOpenQue(search_able->getInitialState());
    addToOpenList(search_able->getInitialState(), &openSet, &openQue);
    State<T> *currentState;
    search_able->getInitialState()->isDiscovered = true;
    search_able->getInitialState()->costOfTrack = 0;
    int numberOfNodesEvaluated = 0;

    while (openQue.size() > 0) {
      numberOfNodesEvaluated++;
      currentState = popOpenList(&openSet, &openQue);
      currentState->isDiscovered = true;
      this->addToClosedSet(currentState, &closedSet);
      if (currentState->equals(*(search_able->getGoalState()))) {
        break;
      }
      listOfSuccessors = search_able->getSuccessors(currentState);
      for (int i = 0; i < listOfSuccessors.size(); i++) {
        if (listOfSuccessors[i]->isDiscovered == false && !this->isInOpenSet(listOfSuccessors[i], openSet)) {
          (listOfSuccessors[i])->prev = currentState;
          (listOfSuccessors[i])->costOfTrack = currentState->costOfTrack +
              listOfSuccessors[i]->state->value;
          pushToOpenQue(listOfSuccessors[i], &openSet, &openQue);
        } else {
          int tentative_g_score = currentState->costOfTrack + listOfSuccessors[i]->state->getValue();
          if (tentative_g_score < (listOfSuccessors[i])->costOfTrack) {
            (listOfSuccessors[i])->costOfTrack = currentState->costOfTrack +
                listOfSuccessors[i]->state->value;
            (listOfSuccessors[i])->prev = currentState;
            if (!openSet.count(listOfSuccessors[i]))
              pushToOpenQue(listOfSuccessors[i], &openSet, &openQue);
          }
        }
      }
    }
    //cout<<numberOfNodesEvaluated<<endl;
  }
};

#endif //MILESTONE2__BESTFIRSTSEARCH_H_
