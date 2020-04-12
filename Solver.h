//
// Created by tal on 6.1.2020.
//

#ifndef MILESTONE2__SOLVER_H_
#define MILESTONE2__SOLVER_H_

template<typename Problem,typename Solution>
class Solver {
 public:
  virtual Solution solve(Problem problem) = 0;
};

#endif //MILESTONE2__SOLVER_H_
