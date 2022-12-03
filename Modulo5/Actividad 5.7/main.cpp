// Program that solves the N Queens problem using Hill-Climbing Algorithm
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
//02/12/22
#include <iostream>
#include <math.h>
#include <vector>
 
using namespace std;
   
// generate how many queens are attacking each othe for a particular board
// Input: vector<vector<int>>, vector<int>, int
// Output: int
// Time complexity: O(n)
int n_queens(vector<vector<int>> &board, vector<int> &state, int n)
{
  int attacking = 0;
  int row, col;

  //check if a queen is attacking other one for every direcion
  for (int i = 0; i < n; i++) {

    row = state.at(i), col = i - 1;
    while (col >= 0 && !board.at(row).at(col)) col--;
    
    if (col >= 0 && board.at(row).at(col)) attacking++;
    row = state.at(i), col = i + 1;
    while (col < n && !board.at(row).at(col)) col++;
    
    if (col < n && board.at(row).at(col)) attacking++;
    
    row = state.at(i) - 1, col = i - 1;
    while (col >= 0 && row >= 0 && !board.at(row).at(col)) {
      col--;
      row--;
    }
    if (col >= 0 && row >= 0 && board.at(row).at(col)) attacking++;
  
    row = state.at(i) + 1, col = i + 1;
    while (col < n && row < n && !board.at(row).at(col)) {
      col++;
      row++;
    }
    if (col < n && row < n && board.at(row).at(col)) attacking++;

    row = state.at(i) + 1, col = i - 1;
    while (col >= 0 && row < n && !board.at(row).at(col)) {
      col--;
      row++;
    }
    if (col >= 0 && row < n && board.at(row).at(col)) attacking++;
 
    row = state.at(i) - 1, col = i + 1;
    while (col < n && row >= 0 && !board.at(row).at(col)) {
      col++;
      row--;
    }

    if (col < n && row >= 0 && board.at(row).at(col)) attacking++;
  }

  return (int)(attacking / 2);
}


// get most "correct" answer between different posible states
// Input: vector<vector<int>>, vector<int>, int
// Output: None
// Time complexity: O(n^2)
void getNeighbour(vector<vector<int>> &board, vector<int> state, int n)
{
  vector<vector<int>> opBoard(n,vector<int>(n,0));
  vector<int> opState(n,0);

  for (int i = 0; i < n; i++) {
    opState.at(i) = state.at(i);
  }
  for (int i = 0; i < n; i++) {
    opBoard.at(opState.at(i)).at(i) = 1;
  }

  int opObjective = n_queens(opBoard, opState, n);
  vector<vector<int>> NeighbourBoard(n,vector<int>(n,0));
  vector<int> NeighbourState(n,0);
  for (int i = 0; i < n; i++) {
    NeighbourState.at(i) = state.at(i);
  }
  for (int i = 0; i < n; i++) {
    NeighbourBoard.at(NeighbourState.at(i)).at(i) = 1;
  }

  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {

          if (j != state.at(i)) {

              NeighbourState.at(i) = j;
              NeighbourBoard.at(NeighbourState.at(i)).at(i)= 1;
              NeighbourBoard.at(state.at(i)).at(i) = 0;

              int temp = n_queens(NeighbourBoard,NeighbourState, n);

              if (temp <= opObjective) {
                  opObjective = temp;
                  for (int i = 0; i < n; i++) {
                    opState.at(i) = NeighbourState.at(i);
                  }
                  for (int i = 0; i < n; i++) {
                   opBoard.at(opState.at(i)).at(i) = 1;
                  }
              }

              NeighbourBoard.at(NeighbourState.at(i)).at(i) = 0;
              NeighbourState.at(i) = state.at(i);
              NeighbourBoard.at(state[i]).at(i) = 1;
          }
      }
  }

  // return best board
  for (int i = 0; i < n; i++) {
    state.at(i) = opState.at(i);
  }
  for (int i = 0; i < n; i++) {
    board.at(state.at(i)).at(i) = 1;
  }
}

// compare if two states are equal
// Input: vector<int>, vector<int>, int
// Output: bool
// Time complexity: O(n)
bool compareStates(vector<int> &state1, vector<int> &state2,int n){
  for (int i = 0; i < n; i++) {
    if (state1.at(i) != state2.at(i)) return false;
  }
  return true;
}

// Hill-Climbing algorithm for local search
// since its an AI algorithm, it does not always generates a completely correct solution
// Input: vector<vector<int>>, vector<int>, int
// Output: None
// Time complexity: O(n^4) 
void hillClimbing(vector<vector<int>> &board, vector<int> &state, int n) {
 
  vector<vector<int>> neighbourBoard(n,vector<int>(n,0));
  vector<int> neighbourState(n,0);

  for (int i = 0; i < n; i++) {
    neighbourState.at(i) = state.at(i);
  }

  for (int i = 0; i < n; i++) {
    neighbourBoard.at(neighbourState.at(i)).at(i) = 1;
  }
 
  do {

    for (int i = 0; i < n; i++) {
     state.at(i) = neighbourState.at(i);
    }
    for (int i = 0; i < n; i++) {
     board.at(state.at(i)).at(i) = 1;
    }

    // Getting the optimal neighbour
    getNeighbour(neighbourBoard, neighbourState,n);
    if (compareStates(state, neighbourState,n)) {
      //we reached the optimal solution
      break;
    } else if (n_queens(board,state, n) == n_queens(neighbourBoard,neighbourState,n)) {
        // check random neighbour
        neighbourState[rand() % n] = rand() % n;
        for (int i = 0; i < n; i++) {
          neighbourBoard.at(neighbourState.at(i)).at(i) = 1;
        }
    }
  } while (true);
}

// generate random board configuration
// Input: vector<vector<int>>, vector<int>, int
// Output: None
// Time complexity: O(n)
void configureRandomly(vector<vector<int>> &board, vector<int> &state, int n){
  srand(time(0));

  for (int i = 0; i < n; i++) {
    state.at(i) = rand() % n;
    board.at(state.at(i)).at(i) = 1;
  }
}

int main() {

  int n;
  
  cin >> n;

  vector<int> state(n,0);
  vector<vector<int>> board(n,vector<int>(n,0));

  // configure board
  configureRandomly(board, state, n);
  hillClimbing(board, state, n);

  //print solution
  for(int i = 0; i < n; i++){
    cout << "{ " ;
    for(int j = 0; j < n; j++){
      if(j == n-1){
        cout << board.at(i).at(j) << "}" << endl;;
      }else {
        cout << board.at(i).at(j) << ", ";
      }
    }
  }
  return 0;
}