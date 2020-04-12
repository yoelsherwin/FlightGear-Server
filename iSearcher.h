//
// Created by tal on 7.1.2020.
//

#ifndef MILESTONE2__ISEARCHER_H_
#define MILESTONE2__ISEARCHER_H_
#include "Searchable.h"
template <typename T>
class iSearcher {
 public:
  virtual State<T>* search(Searchable<T>* search_able) = 0;
};

#endif //MILESTONE2__ISEARCHER_H_
