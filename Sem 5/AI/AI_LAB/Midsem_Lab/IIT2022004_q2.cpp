#include <bits/stdc++.h>
using namespace std;

const int N = 3;
const vector<vector<int>> goal = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 0}};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void print_state(vector<vector<int>> &state)
{
    for (auto &row : state)
    {
        for (auto &num : row)
        {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool is_goal(vector<vector<int>> &state)
{
    return state == goal;
}

vector<pair<int, int>> find_blanks(vector<vector<int>> &state)
{
    vector<pair<int, int>> blanks;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (state[i][j] == 0)
            {
                blanks.push_back({i, j});
            }
        }
    }
    return blanks;
}

void print_path(map<vector<vector<int>>, vector<vector<int>>> &parent, vector<vector<int>> &goal_state)
{
    vector<vector<vector<int>>> path;
    vector<vector<int>> current = goal_state;
    while (parent.find(current) != parent.end())
    {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(current);

    for (int i = path.size() - 1; i >= 0; --i)
    {
        cout << "State " << path.size() - i - 1 << ":" << endl;
        print_state(path[i]);
    }
}
void solve_7_puzzle(vector<vector<int>> initial)
{
    queue<vector<vector<int>>> q;
    set<vector<vector<int>>> visited;
    map<vector<vector<int>>, vector<vector<int>>> parent;

    q.push(initial);
    visited.insert(initial);

    while (!q.empty())
    {
        vector<vector<int>> state = q.front();
        q.pop();

        if (is_goal(state))
        {
            cout << "Goal state reached!" << endl;
            print_path(parent, state);
            return;
        }

        vector<pair<int, int>> blanks = find_blanks(state);

        for (auto &blank : blanks)
        {
            int x = blank.first;
            int y = blank.second;

            for (int i = 0; i < 4; ++i)
            {
                int new_x = x + dx[i];
                int new_y = y + dy[i];

                if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < N)
                {
                    vector<vector<int>> new_state = state;
                    swap(new_state[x][y], new_state[new_x][new_y]);

                    if (visited.find(new_state) == visited.end())
                    {
                        q.push(new_state);
                        visited.insert(new_state);
                        parent[new_state] = state;
                    }
                }
            }
        }
    }
    cout << "No solution found!" << endl;
}

int main()
{
    /*
    solved using BFS.
    prints the intermediate states of the correct path.
    */
    vector<vector<int>> initial = {
        {1, 0, 3},
        {4, 5, 7},
        {0, 6, 2}};

    cout << "Initial state:" << endl;
    print_state(initial);
    cout << "Solving..." << endl;

    solve_7_puzzle(initial);

    return 0;
}
