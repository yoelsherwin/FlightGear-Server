//
// Created by tal on 7.1.2020.
//

#ifndef MILESTONE2__DFS_H_
#define MILESTONE2__DFS_H_
#include "iSearcher.h"
#include "stack"
template <typename T>
class DFS : public iSearcher<T>{
  State<T>* search(Searchable<T>* search_able) {
    int numberOfNodesEvaluated = 0;
    stack<State<T>*> stack;

    State<T>* n = search_able->getInitialState();
    State<T>* goal = search_able->getGoalState();

    vector<State<T>*> neighbours;
    //insert ot stack, dont insert to list because it will be removed immediatley
    stack.push(n);
    n->isDiscovered = true;
    while (!stack.empty()) {
      numberOfNodesEvaluated++;
      n = stack.top();
      stack.pop();
      if (n->equals(*goal)) {
        break;
      }

      neighbours = search_able->getSuccessors(n);
      for (int i = 0; i < neighbours.size(); ++i) {
        if(neighbours[i]->isDiscovered == false){
          neighbours[i]->isDiscovered = true;
          neighbours[i]->prev = n;
          stack.push(neighbours[i]);
        }
      }
    }
    //cout<<numberOfNodesEvaluated<<endl;
  }
};


#endif //MILESTONE2__DFS_H_
