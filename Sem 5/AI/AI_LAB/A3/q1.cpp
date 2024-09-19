#include <bits/stdc++.h>
using namespace std;

// Define the goal state for the 8-puzzle
const vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

// Structure to represent the state of the puzzle
struct PuzzleState
{
    vector<vector<int>> board; // 3x3 board configuration
    int x, y;                  // Position of the empty tile (0)
    string path;               // Path to reach the current state (actions taken)

    // Compare two states for equality
    bool operator==(const PuzzleState &other) const
    {
        return board == other.board;
    }

    // Convert the 2D board into a string (used for hashing)
    string to_string() const
    {
        string result;
        for (const auto &row : board)
        {
            for (int val : row)
            {
                result += std::to_string(val);
            }
        }
        return result;
    }
};

// Direction vectors for the four possible moves (left, right, up, down)
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
const string moves = "LRUD"; // Left, Right, Up, Down

// Function to check if a position is within the puzzle boundaries
bool is_valid(int x, int y)
{
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

// Function to print the puzzle board
void print_board(const vector<vector<int>> &board)
{
    for (const auto &row : board)
    {
        for (int val : row)
        {
            if (val == 0)
                cout << "  ";
            else
                cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// BFS function to solve the 8-puzzle
string solve_8_puzzle(vector<vector<int>> &start_board)
{
    queue<PuzzleState> q;
    unordered_set<string> visited;

    // Find the position of the empty tile (0) in the start state
    int start_x, start_y;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (start_board[i][j] == 0)
            {
                start_x = i;
                start_y = j;
            }
        }
    }

    // Push the initial state to the queue
    q.push({start_board, start_x, start_y, ""});
    visited.insert(PuzzleState{start_board, start_x, start_y, ""}.to_string());

    // Perform BFS to find the solution
    while (!q.empty())
    {
        PuzzleState current = q.front();
        q.pop();

        // If the current state is the goal state, return the path
        if (current.board == goal)
        {
            return current.path;
        }

        // Try all possible moves
        for (int i = 0; i < 4; ++i)
        {
            int new_x = current.x + dx[i];
            int new_y = current.y + dy[i];

            // Check if the new position is valid
            if (is_valid(new_x, new_y))
            {
                vector<vector<int>> new_board = current.board;
                swap(new_board[current.x][current.y], new_board[new_x][new_y]); // Move the empty tile

                PuzzleState new_state = {new_board, new_x, new_y, current.path + moves[i]};

                // If this state has not been visited, add it to the queue
                if (visited.find(new_state.to_string()) == visited.end())
                {
                    q.push(new_state);
                    visited.insert(new_state.to_string());
                }
            }
        }
    }

    return "No solution";
}

int main()
{
    vector<vector<int>> start_board = {
        {2, 1, 3},
        {0, 6, 5},
        {4, 7, 8}};

    cout << "Start Board: \n";
    print_board(start_board);

    string solution = solve_8_puzzle(start_board);
    if (solution != "No solution")
    {
        cout << "Solution found! Moves: " << solution << endl;
    }
    else
    {
        cout << "No solution exists." << endl;
    }

    return 0;
}
