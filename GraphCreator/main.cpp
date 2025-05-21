#include <iostream>
#include <cstring>

using namespace std;

int main() {
  bool quit = false;
  char input[30];
  int adjacency[20][20];
  int vertices[20];
  for (int a = 0; a < 20; a++) {
    vertices[a] = 0;
    for (int b = 0; b < 20; b++) {
      adjacency[a][b] = 0;
    }
  }
  do {
    cout << "You can: \'ADD\' \'REMOVE\' \'PRINT\' \'QUIT\'" << endl;
    cin >> input;
    if (strcmp(input, "ADD") == 0) {
      cout << "You can add: \'EDGE\' \'VERTICE\'" << endl;
      char choiceInput[10];
      cin >> choiceInput;
      if (strcmp(choiceInput, "VERTICE") == 0) {
	cout << "Please label the vertice with a number 1-20: " << endl;
	int newLabel;
	cin >> newLabel;
	vertices[newLabel-1] = newLabel;
      }
      if (strcmp(choiceInput, "EDGE") == 0) {
	cout << "First vertice?" << endl;
	int vOne;
	cin >> vOne;
	cout << "Second vertice?" << endl;
	int vTwo;
	cin >> vTwo;
        cout << "Weight?" << endl;
	int weight;
	cin >> weight;
	adjacency[vOne-1][vTwo-1] = weight;
        adjacency[vTwo-1][vOne-1] = weight;
      }
    }
    else if (strcmp(input, "REMOVE") == 0) {
      cout << "You can remove: \'EDGE\' \'VERTICE\'" << endl;
      char choiceInput[10];
      cin >> choiceInput;
      if (strcmp(choiceInput, "EDGE") == 0) {
	cout << "First vertice?" << endl;
        int vOne;
        cin >> vOne;
        cout << "Second vertice?" << endl;
        int vTwo;
        cin >> vTwo;
        adjacency[vOne-1][vTwo-1] = 0;
        adjacency[vTwo-1][vOne-1] = 0;
      }
      if (strcmp(choiceInput, "VERTICE") == 0) {
	cout << "What label would you like to remove?" << endl;
        int delVert;
        cin >> delVert;
        vertices[delVert - 1] = 0;
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
	if (vertices[i] != 0) {
	  cout << " " << vertices[i];
	}
      }
      cout << '\n';
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
    else if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
  } while (quit != true);
  return 0;
}
