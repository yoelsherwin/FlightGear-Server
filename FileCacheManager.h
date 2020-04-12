//
// Created by yoel on 06/01/2020.
//

#ifndef MILESTONE2__FILECACHEMANAGER_H_
#define MILESTONE2__FILECACHEMANAGER_H_
#include <string>
#include "CacheManager.h"
#include <list>
#include "unordered_map"
#include "hash_fun.h"
using namespace std;
//template<typename Problem, typename Solution>
class FileCacheManager : public CacheManager<string, string> {

 private:
  unordered_map<string, string> map;
  hash<string> hashFunc;

 public:
  FileCacheManager() {

  }

  void insert(string str, string val) {
    WriteToFile(str, val);
  }


  string get(string str) {
    string val;
    char *val1 = nullptr;
    string fileName = to_string(hashFunc(str));    //check if this key is in the cache
    //if (map.count(str) > 0) {
    if(isCacheHaveSol(str)){
      val = ReadFromFile(fileName);
      val += '\n';
      return val;
    } else return nullptr;
  }

//func that writing to file
  void WriteToFile(string str1, string ans) {
    fstream file;
    string fileName = to_string(hashFunc(str1));
    ofstream file1(fileName);
    if (!file) {
      throw "problem with file";
    }
    file1 << ans;
    file1.close();
    map[str1] = fileName;
  }

//func that reading from file
  string ReadFromFile(const string& fileName) {
    ifstream file;
    file.open(fileName);
    string line;
    char buffer[5000];
    getline(file, line);
    return line;
  }
 public:

  bool isCacheHaveSol(string problemThatWeWantToCheck) override {
    string fileName = to_string(hashFunc(problemThatWeWantToCheck));
    ifstream file(fileName);
    if(file.is_open()) {
      file.close();
      return true;
    }
    return false;
  }
};
//};

#endif //MILESTONE2__FILECACHEMANAGER_H_