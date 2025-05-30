#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "queue.h"
using namespace std;

int dijkstraPath(int source, int destination, vector<int> &visited, int adjacency[][20], int vertices[]);

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
	vector<int> visited;
	visited.push_back(1);
	int dist = dijkstraPath(vOne, vTwo, visited, adjacency, vertices);
	cout << dist << endl;
    }
    else if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
  } while (quit != true);
  return 0;
}

int dijkstraPath(int source, int destination, vector<int> &visited, int adjacency[][20], int vertices[]) {
  cout << "starting" << endl;
  queue* curr = new queue(source, 0);
  vector<queue*> priorityQueue;
  int vertCount = 0;
  for (int i = 0; i < 19; i++) {
    if (vertices[i] != 0) {
      vertCount++;
    }
  }
  bool validPath = false;
  cout << visited.size() << endl;
  cout << curr->getVertice() << endl;
  cout << vertCount << endl;
  while (curr->getVertice() != destination && (visited.size() - 1) != vertCount) {
    cout << "gurt" << endl;
    int vert = curr->getVertice();
    cout << vert << endl;
    for (int i = 0; i < 20; i++) {
       if (adjacency[vert - 1][i] != 0) {
	 queue* newQueue = new queue(i+1, curr->getDistance() + adjacency[vert-1][i]);
	 cout << "Adding!" << newQueue->getDistance() << endl;
	 priorityQueue.push_back(newQueue);
	 validPath = true;
       }
    }
    if (validPath == true) {
    cout << "added one" << endl;
    visited.push_back(curr->getVertice());
    }
    for (int i = 0; i < priorityQueue.size(); i++) {
      if (priorityQueue[i] == curr) {
	priorityQueue.erase(priorityQueue.begin() + i);
	break;
      }
    }
      
    sort(priorityQueue.begin(), priorityQueue.end());
    curr = priorityQueue.back();
    cout << "here 6" << endl;
  }
  return priorityQueue.back()->getDistance();
}

