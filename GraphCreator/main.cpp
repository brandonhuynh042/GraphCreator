#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include "queue.h"
using namespace std;

// This program implements a weighted, directional graph with the ability to find the shortest path using Dijsktra's Algorithm.
// Last edited Brandon Huynh, 5/30/2025

void dijkstraPath(int source, int destination, vector<int> &visited, int adjacency[][20], int vertices[]);

int main() {
  bool quit = false;
  char input[30];
  int adjacency[20][20];
  int vertices[20];
  // initialize empty vertices and adj table
  for (int a = 0; a < 20; a++) {
    vertices[a] = 0;
    for (int b = 0; b < 20; b++) {
      adjacency[a][b] = 0;
    }
  }
  do {
    cout << "You can: \'ADD\' \'REMOVE\' \'PRINT\' \'PATHFIND\' \'QUIT\'" << endl;
    cin >> input;
    if (strcmp(input, "ADD") == 0) {
      // which one?
      cout << "You can add: \'EDGE\' \'VERTICE\'" << endl;
      char choiceInput[10];
      cin >> choiceInput;
      if (strcmp(choiceInput, "VERTICE") == 0) {
	cout << "Please label the vertice with a number 1-20: " << endl;
	int newLabel;
	cin >> newLabel;
	// add vertice to user input...
	vertices[newLabel-1] = newLabel;
      }
      if (strcmp(choiceInput, "EDGE") == 0) {
	// take connection & weight
	cout << "First vertice?" << endl;
	int vOne;
	cin >> vOne;
	cout << "Second vertice?" << endl;
	int vTwo;
	cin >> vTwo;
        cout << "Weight?" << endl;
	int weight;
	cin >> weight;
	// set adjacency table accordingly
	adjacency[vOne-1][vTwo-1] = weight;
      }
    }
    else if (strcmp(input, "REMOVE") == 0) {
      cout << "You can remove: \'EDGE\' \'VERTICE\'" << endl;
      char choiceInput[10];
      cin >> choiceInput;
      if (strcmp(choiceInput, "EDGE") == 0) {
	// which connection?
	cout << "First vertice?" << endl;
        int vOne;
        cin >> vOne;
        cout << "Second vertice?" << endl;
        int vTwo;
        cin >> vTwo;
	// delete in adj. table
        adjacency[vOne-1][vTwo-1] = 0;
      }
      if (strcmp(choiceInput, "VERTICE") == 0) {
	cout << "What label would you like to remove?" << endl;
        int delVert;
        cin >> delVert;
	// delete the vertice itsself
        vertices[delVert - 1] = 0;
  	// delete all potential links it may have had
        for (int a = 0; a < 20; a++) {
          if (a = delVert - 1) {
            for (int b = 0; b < 20; b++) {
              adjacency[a][b] = 0;
              adjacency[b][a] = 0;
            }
	    break;
          }
        }
      }
    }
    else if (strcmp(input, "PRINT") == 0) {
      cout << " " << " ";
      for (int i = 0; i < 20; i++) {
	// only showing the ones that exist
	if (vertices[i] != 0) {
	  cout << " " << vertices[i];
	}
      }
      cout << '\n';
      // print out the adjacency table for rows/columns which there are actually vertices
      for (int j = 0; j < 20; j++) {
	if (vertices[j] != 0) {
	  if (j < 10) {
	    cout << " ";
	  }
	  cout << vertices[j] << " ";
	  for (int k = 0; k < 20; k++) {
	    if (vertices[k] != 0) {
	      if (adjacency[j][k] != 0) {
		cout << "1 ";
	      }
	      else {
		cout << "0 ";
	      }
	      if (k > 9) {
		cout << " ";
	      }
	    }
	  }
        cout << '\n';

	}
     }
    }
    else if (strcmp(input, "PATHFIND") == 0) {
       // which connection?
        cout << "First vertice?" << endl;
        int vOne;
        cin >> vOne;
        cout << "Second vertice?" << endl;
        int vTwo;
        cin >> vTwo;
	// this honestly doesn't need to be passed by ref. but i don't want to change it
	vector<int> visited;
	// find the path
        dijkstraPath(vOne, vTwo, visited, adjacency, vertices); 
    }
    else if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
  } while (quit != true);
  return 0;
}

void dijkstraPath(int source, int destination, vector<int> &visited, int adjacency[][20], int vertices[]) {
  //cout << "starting" << endl;
  // start at the starting node, no distance yet.
  queue* curr = new queue(source, 0);
  vector<queue*> priorityQueue;
  priorityQueue.push_back(curr);
  int vertCount = 0;
  map<int, int> parents;
  map<int, int> distances;
  distances[source] = 0;
  // see how many vertices there are, set these non source nodes to "infinity"
  for (int i = 0; i < 20; i++) {
    if (vertices[i] != 0) {
      vertCount++;
      distances[i+1] = 100000; // not infinity but very big.
    }
  }
  distances[source] = 0; // not the source though
  // until finished, or no path is possible
  while (!priorityQueue.empty() && curr) {
    // sort, take smallest distance and pop from priority queue
    sort(priorityQueue.begin(), priorityQueue.end(), [](queue* a, queue* b) {
      return a->getDistance() > b->getDistance();
    });
    curr = priorityQueue.back();
    priorityQueue.pop_back();
    // reached the end vertice? print distance + path
    if (curr->getVertice() == destination) {
      cout << "Distance: " << curr->getDistance() << endl;
      vector<int> path;
      int current = destination;
      // follow the parents to get path backwards
      while (current != source) {
        path.push_back(current);
        current = parents[current];
      }
      path.push_back(source);
      // make it fowards!
      reverse(path.begin(), path.end());
      cout << "Path: ";
      for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
      }
      cout << '\n';
      return;
    }
    // skip if it's already been looked through
    if (find(visited.begin(), visited.end(), curr->getVertice()) != visited.end()) {
      continue;
    }
    visited.push_back(curr->getVertice());
    int vert = curr->getVertice();
    // looking at all connections
    for (int i = 0; i < 20; i++) {
      // is there an edge there?
      if (adjacency[vert - 1][i] != 0) {
        int neighbor = i + 1;
        if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
          int newDist = curr->getDistance() + adjacency[vert - 1][i];
	  // in case there's a shorter path
          if (newDist < distances[neighbor]) {
            distances[neighbor] = newDist;
            queue* newQueue = new queue(neighbor, newDist);
            priorityQueue.push_back(newQueue);
            parents[neighbor] = vert;
          }
        }
      }
    }
  }
  // no path.
  cout << "No path found!" << endl;
  return;
}
