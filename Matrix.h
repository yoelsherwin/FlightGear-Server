//
// Created by yoel on 09/01/2020.
//

#ifndef SERVER__MATRIX_H_
#define SERVER__MATRIX_H_

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Searchable.h"
#include "Point.h"
using namespace std;
//template <typename T>
class Matrix : public Searchable<Point> {
  State<Point> *initialState;
  State<Point> *goalState;
  vector<vector<State<Point> *>> mat;
  int rows;
  int columns;
 public:
  Matrix(vector<string> lines) {
    // save last 2 lines in order to create
    string goalLine = lines.back();
    lines.pop_back();
    string initLine = lines.back();
    lines.pop_back();

    rows = lines.size();
    vector<double> check = createValuesVector(lines[0]);
    columns = check.size();

    //create vector of vector
    for (int i = 0; i < rows; ++i) {
      vector<State<Point> *> line;
      vector<double> values = createValuesVector(lines[i]);
      for (int j = 0; j < columns; ++j) {
        Point *p = new Point(i, j, values[j]);
        line.push_back(new State<Point>(p));
      }
      mat.push_back(line);
    }

    string temp1;
    // create initial and goal states
    initLine.erase(std::remove_if(initLine.begin(), initLine.end(), ::isspace), initLine.end());
    string temp = initLine;
    auto find = initLine.find_first_of(',');
    temp1 = initLine.substr(0, find);
    int x = stoi(temp1);
    initLine = temp;
    find = initLine.find_first_of(',');
    initLine.erase(0, find + 1);
    find = initLine.find_first_of(',');
    temp1 = initLine.substr(find + 1, initLine.size() - find);
    int y = stoi(temp1);
    this->initialState = mat[x][y];

    goalLine.erase(std::remove_if(goalLine.begin(), goalLine.end(), ::isspace), goalLine.end());
    temp = goalLine;
    find = goalLine.find_first_of(',');
    x = stoi(temp.substr(0, find));
    goalLine = temp;
    find = goalLine.find_first_of(',');
    goalLine.erase(0, find + 1);
    find = goalLine.find_first_of(',');
    y = stoi(goalLine.substr(find + 1, goalLine.size() - find));
    pair<int, int> goal1;
    this->goalState = mat[x][y];
  }

  State<Point> *getInitialState() override {
    return initialState;
  }
  State<Point> *getGoalState() override {
    return goalState;
  }

  vector<State<Point> *> getSuccessors(State<Point> *s) override {
    vector<State<Point> *> successors;
    int x = s->state->getX();
    int y = s->state->getY();

    // also check if blocked
    if (x + 1 < this->rows && !mat[x+1][y]->state->blocked) {
      successors.push_back(mat[x + 1][y]);
    }
    if (x - 1 >= 0 && !mat[x-1][y]->state->blocked) {
      successors.push_back(this->mat[x - 1][y]);
    }
    if (y + 1 < this->columns && !mat[x][y+1]->state->blocked) {
      successors.push_back(mat[x][y + 1]);
    }
    if (y - 1 >= 0 && !mat[x][y-1]->state->blocked) {
      successors.push_back(mat[x][y - 1]);
    }
    return successors;
  }

  vector<double> createValuesVector(string line) {
    vector<double> values;
    double val;
    string temp;
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    auto find = line.find_first_of(',');
    while (find != string::npos) {
      temp = line;
      line.substr(0, find - 1);
      val = stod(line);
      values.push_back(val);
      auto find2 = temp.find_first_of(',');
      line = temp.erase(0, find2 + 1);
      find = line.find_first_of(',');
    }
    //push last value
    val = stod(line);
    values.push_back(val);
    return values;
  }

  string traceBack() override {
    string ans = "";
    double sum = 0;

    State<Point> *curr = this->goalState;
    vector<State<Point>*> path;
    if(this->goalState->prev == nullptr && !this->goalState->equals(*(this->initialState))){
      return "there is no path!";
    }
    while(curr != initialState) {
      path.push_back(curr);
      curr = curr->prev;
    }
    path.push_back(curr);

    State<Point>* next;
    State<Point>* temp;
    curr = path.back();
    sum += curr->state->value;
    path.pop_back();
    next = path.back();
    path.pop_back();
    while (!next->equals(*goalState)) {
      sum += next->state->value;
      if (curr->state->getY() < next->state->getY()) {
        ans += "Right(" + to_string((int)sum) + "), ";
      } else if (curr->state->getY() > next->state->getY()) {
        ans += "Left(" + to_string((int)sum) + "), ";
      } else if (curr->state->getX() < next->state->getX()) {
        ans += "Down(" + to_string((int)sum) + "), ";
      } else if (curr->state->getX() > next->state->getX()){
        ans += "Up(" + to_string((int)sum) + "), ";
      }
      curr = next;
      next = path.back();
      path.pop_back();
    }
    // insert last move
    sum += next->state->value;
    if (curr->state->getY() < next->state->getY()) {
      ans += "Right(" + to_string((int)sum) + ")\n";
    } else if (curr->state->getY() > next->state->getY()) {
      ans += "Left(" + to_string((int)sum) + ")\n";
    } else if (curr->state->getX() < next->state->getX()) {
      ans += "Down(" + to_string((int)sum) + ")\n";
    } else if (curr->state->getX() > next->state->getX()){
      ans += "Up(" + to_string((int)sum) + ")\n";
    }
    return ans;
  }

};

#endif //SERVER__MATRIX_H_
