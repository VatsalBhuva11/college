#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include<math.h>

using namespace std;

// Utility function to check if the current state is the goal state
bool isGoalState(vector<vector<int>> &state, int n) {
    vector<vector<int>> goal(n, vector<int>(n, 0));
    int k=1;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            goal[i][j] = k;
            k++;
        }
    }
    goal[n-1][n-1] = 0;
    return state == goal;
}

// Utility function to convert the board state to a string for hashing
string boardToString(vector<vector<int>> &board) {
    stringstream ss;
    for (auto &row : board) {
        for (int val : row) {
            ss << val << ",";
        }
    }
    return ss.str();
}

// Utility function to print the board state
void printBoard(vector<vector<int>> &board) {
    for (auto &row : board) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Breadth-First Search (BFS) function to solve the 8-puzzle
void solve8Puzzle(vector<vector<int>> &initial, int n) {
    // Direction vectors for moving the blank space (0)
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    // Queue to store the board states and their corresponding steps
    queue<pair<vector<vector<int>>, int>> q;
    unordered_set<string> visited;
    
    q.push({initial, 0});
    visited.insert(boardToString(initial));
    
    while (!q.empty()) {
        auto [current, steps] = q.front();
        q.pop();
        
        if (isGoalState(current, n)) {
            cout << "Solved in " << steps << " steps." << endl;
            printBoard(current);
            return;
        }
        
        // Find the position of the blank space (0)
        int zeroX, zeroY;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (current[i][j] == 0) {
                    zeroX = i;
                    zeroY = j;
                    break;
                }
            }
        }
        
        // Try moving the blank space in all four possible directions
        for (auto &[dx, dy] : directions) {
            int newX = zeroX + dx;
            int newY = zeroY + dy;
            
            if (newX >= 0 && newX < n && newY >= 0 && newY < n) {
                swap(current[zeroX][zeroY], current[newX][newY]);
                
                string stateString = boardToString(current);
                if (visited.find(stateString) == visited.end()) {
                    q.push({current, steps + 1});
                    visited.insert(stateString);
                }
                
                // Swap back to restore the original state
                swap(current[zeroX][zeroY], current[newX][newY]);
            }
        }
    }
    
    cout << "No solution found." << endl;
}

int main() {
    
    int size;
    cout<<"Which puzzle do you want to play?"<<endl;
    cin>>size;
    cout<<endl;
    int n = sqrt(size+1);
    vector<vector<int>> initial(n, vector<int>(n, 0));
    
    cout<<"Enter the random sequence of puzzle:"<<endl;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>initial[i][j];
        }
    }
    cout<<endl;
    
    // Example input for the 8-puzzle problem
    // vector<vector<int>> initial = {
    //     {7, 2, 4},
    //     {5, 6, 0},
    //     {8, 3, 1}
    // };
    
    cout << "Initial board:" << endl;
    printBoard(initial);
    
    solve8Puzzle(initial, n);
    
    return 0;
}
