#include <bits/stdc++.h>

using namespace std;

struct Node
{
    string state;
    int empty_pos;
    int level;
    vector<string> moves;

    Node(string s, int e, int l, vector<string> m) : state(s), empty_pos(e), level(l), moves(m) {}
};

// Goal state
const string GOAL_STATE = "123b";

// Function to check if the current state is the goal state
bool isGoalState(const string &state)
{
    return state == GOAL_STATE;
}

// Function to print the state space tree
void printStateSpace(const Node &node)
{
    cout << "Level " << node.level << " | State: " << node.state << " | Moves: ";
    for (const string &move : node.moves)
    {
        cout << move << " ";
    }
    cout << endl;
}

// Generate possible moves
vector<Node> generateMoves(const Node &node)
{
    vector<Node> successors;
    int empty_pos = node.empty_pos;
    int x = empty_pos / 2;
    int y = empty_pos % 2;

    // Define possible moves
    vector<pair<int, string>> directions = {
        {-2, "UP"}, {2, "DOWN"}, {-1, "LEFT"}, {1, "RIGHT"}};

    for (const auto &dir : directions)
    {
        int new_x = x + dir.first / 2;
        int new_y = y + dir.first % 2;

        if (new_x >= 0 && new_x < 2 && new_y >= 0 && new_y < 2)
        {
            int new_pos = new_x * 2 + new_y;
            string new_state = node.state;
            swap(new_state[empty_pos], new_state[new_pos]);
            vector<string> new_moves = node.moves;
            new_moves.push_back(dir.second);
            successors.emplace_back(new_state, new_pos, node.level + 1, new_moves);
        }
    }

    return successors;
}

// Breadth-First Search (BFS)
void bfs(const string &start_state)
{
    int empty_pos = start_state.find('b');
    queue<Node> q;
    unordered_set<string> visited;

    q.emplace(start_state, empty_pos, 0, vector<string>());
    visited.insert(start_state);

    while (!q.empty())
    {
        Node current = q.front();
        q.pop();

        printStateSpace(current); // Print the current state

        if (isGoalState(current.state))
        {
            cout << "BFS Solution in " << current.level << " moves: ";
            for (const string &move : current.moves)
            {
                cout << move << " ";
            }
            cout << endl;
            return;
        }

        vector<Node> successors = generateMoves(current);

        for (const Node &next : successors)
        {
            if (visited.find(next.state) == visited.end())
            {
                q.push(next);
                visited.insert(next.state);
            }
        }
    }

    cout << "No solution found with BFS.\n";
}

// Depth-First Search (DFS)
void dfs(string &start_state)
{
    int empty_pos = start_state.find('b');
    stack<Node> s;
    unordered_set<string> visited;

    s.emplace(start_state, empty_pos, 0, vector<string>());
    visited.insert(start_state);

    while (!s.empty())
    {
        Node current = s.top();
        s.pop();

        printStateSpace(current); // Print the current state

        if (isGoalState(current.state))
        {
            cout << "DFS Solution in " << current.level << " moves: ";
            for (const string &move : current.moves)
            {
                cout << move << " ";
            }
            cout << endl;
            return;
        }

        vector<Node> successors = generateMoves(current);

        for (const Node &next : successors)
        {
            if (visited.find(next.state) == visited.end())
            {
                s.push(next);
                visited.insert(next.state);
            }
        }
    }

    cout << "No solution found with DFS.\n";
}

// Depth-Bounded Search (DFS with Depth Limit)
void depthBoundedSearch(string &start_state, int limit)
{
    int empty_pos = start_state.find('b');
    stack<Node> s;

    s.emplace(start_state, empty_pos, 0, vector<string>());

    unordered_set<string> visited;
    visited.insert(start_state);
    while (!s.empty())
    {
        Node current = s.top();
        s.pop();

        printStateSpace(current); // Print the current state

        if (isGoalState(current.state))
        {
            cout << "Depth-Bounded Search (limit " << limit << ") Solution in " << current.level << " moves: ";
            for (const string &move : current.moves)
            {
                cout << move << " ";
            }
            cout << endl;
            return;
        }

        if (current.level < limit)
        {
            vector<Node> successors = generateMoves(current);

            for (const Node &next : successors)
            {
                if (visited.find(next.state) == visited.end())
                {
                    visited.insert(next.state);
                    s.push(next);
                }
            }
        }
    }

    cout << "No solution found with Depth-Bounded Search (limit " << limit << ").\n";
}

int main()
{
    string start_state = "312b"; // Input state

    cout << "BFS State Space Tree:\n";
    bfs(start_state);
    cout << "\nDFS State Space Tree:\n";
    dfs(start_state);
    cout << "\nDepth-Bounded Search State Space Tree (limit 3):\n";
    depthBoundedSearch(start_state, 3); // l = 3
    cout << "\nDepth-Bounded Search State Space Tree (limit 4):\n";
    depthBoundedSearch(start_state, 4); // l = 4

    return 0;
}
