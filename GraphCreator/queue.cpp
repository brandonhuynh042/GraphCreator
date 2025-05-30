#include <iostream>
#include <cstring>
#include "queue.h"
using namespace std;

queue::queue(int newVertice, int newDistance) {
  vertice = newVertice;
  distance = newDistance;
}
queue::~queue() {
  vertice = 0;
  distance = 0;
}
void queue::setVertice(int newVertice) {
  vertice = newVertice;
}
void queue::setDistance(int newDistance) {
  distance = newDistance;
}
int queue::getVertice() {
  return vertice;
}
int queue::getDistance() {
  return distance;
}
