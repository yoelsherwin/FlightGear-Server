//
// Created by tal on 7.1.2020.
//

#ifndef MILESTONE2__SEARCHER_H_
#define MILESTONE2__SEARCHER_H_

#include "iSearcher.h"
#include "list"
#include "unordered_map"
#include "set"
#include "Solver.h"
#include "BestFirstSearch.h"
#include "Matrix.h"
using namespace std;

class SearchSolver : public Solver<Matrix,string> {
 protected:
  iSearcher<Point> *searcher_;
 public:
  SearchSolver(iSearcher<Point> *searcher) : searcher_(searcher) {}
  string solve(Matrix problem) {
    State<Point>* goal = this->searcher_->search(&problem);
    return problem.traceBack();
  }
};

#endif //MILESTONE2__SEARCHER_H_
