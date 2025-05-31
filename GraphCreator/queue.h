#include <iostream>
#include <cstring>
#ifndef QUEUE_H
#define QUEUE_H
using namespace std;
class queue {
public:
  queue(int newVertice, int newDistance);
  ~queue();
  void setVertice(int newVertice);
  void setDistance(int newDistance);
  int getVertice();
  int getDistance();
 protected:
  int vertice;
  int distance;
};

#endif
