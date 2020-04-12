//
// Created by yoel on 06/01/2020.
//

#ifndef MILESTONE2__CACHEMANAGER_H_
#define MILESTONE2__CACHEMANAGER_H_
#include <iostream>
#include <fstream>
#include <cstring>
#include "unordered_map"
using namespace std;
template<typename Problem,typename Solution>

class CacheManager {
 public:
  unordered_map<string,string> map;
  virtual bool isCacheHaveSol(Problem problemThatWeWantToCheck) = 0;
  virtual void insert(Problem str, Solution val) = 0;
  virtual Solution get(Problem problem) = 0;
};

#endif //MILESTONE2__CACHEMANAGER_H_
