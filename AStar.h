//
// Created by tal on 7.1.2020.
//

#ifndef MILESTONE2__ASTAR_H_
#define MILESTONE2__ASTAR_H_

#include "iSearcher.h"
#include "set"
#include <cmath>
#include <queue>

template<typename T>
class AStar : public iSearcher<T> {
  void insertToOpenSet(State<T> *state, priority_queue<State<T> *, vector<State<T> *>, compareStateAStar<T>> *open,
                       set<State<T> *> *openSet) {
    open->push(state);
    openSet->insert(state);
  }
  void removeFromOpen(priority_queue<State<T> *, vector<State<T> *>, compareStateAStar<T>> *open,
                      set<State<T> *> *openSet) {
    State<T> *temp = open->top();
    openSet->erase(temp);
    open->pop();
  }
  State<T> *search(Searchable<T> *search_able) {
    priority_queue<State<T> *, vector<State<T> *>, compareStateAStar<T>> open;
    set<State<T> *> openSet;
    State<T> *goal;
    State<T> *startingState;
    int numberOfNodesEvaluated = 0;

    goal = search_able->getGoalState();
    State<T> *current;
    startingState = search_able->getInitialState();
    set<State<T> *> closedSet;
    insertToOpenSet(startingState, &open, &openSet);
    vector<State<T> *> neighbours;
    startingState->costOfTrack = startingState->state->getValue();
    startingState->fCost = hCost(startingState, goal) + startingState->state->getValue();
    while (!open.empty()) {
      numberOfNodesEvaluated++;
      current = open.top();
      closedSet.insert(current);
      removeFromOpen(&open, &openSet);
      if (current->equals(*goal)) {
        break;
      }

      neighbours = search_able->getSuccessors(current);
      for (int i = 0; i < neighbours.size(); i++) {
        int tentative_g_score = current->costOfTrack;
        int tentative_h_score = hCost(current, goal);
        if ((!openSet.count(neighbours[i])
            || tentative_g_score + neighbours[i]->state->getValue() < neighbours[i]->costOfTrack) &&
            !closedSet.count(neighbours[i])) {
          neighbours[i]->prev = current;
          neighbours[i]->costOfTrack = current->costOfTrack + neighbours[i]->state->getValue();
          neighbours[i]->fCost = neighbours[i]->costOfTrack + hCost(neighbours[i], goal);
          if (!openSet.count(neighbours[i]))
            insertToOpenSet(neighbours[i], &open, &openSet);
        }
      }
    }
    //cout<<numberOfNodesEvaluated<<endl;
  }
  int hCost(State<T> *state1, State<T> *goal) {
    int x;
    int y;
    x = abs(state1->state->getX() - goal->state->getX());
    y = abs(state1->state->getY() - goal->state->getY());
    return (x + y);
  }
  int gCost(State<T> *state1, State<T> *startingState) {
    int x;
    int y;
    x = abs(state1->state->getX() - startingState->state->getX());
    y = abs(state1->state->getY() - startingState->state->getY());
    return (int) (x + y);
  }
};

#endif //MILESTONE2__ASTAR_H_
