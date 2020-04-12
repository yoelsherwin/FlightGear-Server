//
// Created by tal on 11.1.2020.
//

#ifndef SERVER__POINT_H_
#define SERVER__POINT_H_

class Point {
  int x;
  int y;
 public:
  double value;
  bool blocked;
  Point(int x, int y, double value);
  int getX();
  int getY();
  int getValue();
  bool operator==(Point p2);
  void setX(int x);
  void SetY(int y);
  void setPoint(Point p2);
  bool operator <(Point p2);
  bool operator >(Point p2);
};

#endif //SERVER__POINT_H_
