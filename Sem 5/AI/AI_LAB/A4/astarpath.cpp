#include<bits/stdc++.h>
using namespace std;

struct Node {
    int id; 
    double g, h;
    Node* parent;
    
    Node(int id, double g = 0, double h = 0, Node* parent = nullptr)
        : id(id), g(g), h(h), parent(parent) {}
    
    double f() const { return g + h; } 
};

struct CompareNode {
    bool operator()(Node* n1, Node* n2) {
        return n1->f() > n2->f();
    }
};

// Reconstruct the path from the goal node to the start
vector<int> reconstructPath(Node* node) {
    vector<int> path;
    while (node) {
        path.push_back(node->id);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

// A* algorithm to find the shortest path
vector<int> aStar(const unordered_map<int, vector<pair<int, double>>>& graph, const vector<double>& heuristic, int start, int goal) {
    unordered_map<int, bool> visited;
    priority_queue<Node*, vector<Node*>, CompareNode> openSet;
    
    Node* startNode = new Node(start, 0, heuristic[start]);
    openSet.push(startNode);
    
    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();
        
        if (current->id == goal) {
            return reconstructPath(current);
        }
        
        visited[current->id] = true;
        
        for (const auto& neighbor : graph.at(current->id)) {
            int neighborId = neighbor.first;
            double edgeCost = neighbor.second;
            
            if (!visited[neighborId]) {
                double newG = current->g + edgeCost;
                double newH = heuristic[neighborId];
                Node* neighborNode = new Node(neighborId, newG, newH, current);
                openSet.push(neighborNode);
            }
        }
    }
    
    return {};
}

int main() {
    int numNodes, numEdges;
    cout << "Enter number of nodes and edges: ";
    cin >> numNodes >> numEdges;
    
    unordered_map<int, vector<pair<int, double>>> graph;
    
    cout << "Enter edges in format (start end cost): \n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        double cost;
        cin >> u >> v >> cost;
        graph[u].push_back({v, cost});
        graph[v].push_back({u, cost}); 
    }
    
    vector<double> heuristic(numNodes);
    cout << "Enter heuristic values for each node:\n";
    for (int i = 0; i < numNodes; ++i) {
        cin >> heuristic[i];
    }
    
    int start, goal;
    cout << "Enter start and goal nodes: ";
    cin >> start >> goal;
    
    vector<int> path = aStar(graph, heuristic, start, goal);
   
    if (!path.empty()) {
        cout << "Path found:\n";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found" << endl;
    }
    
    return 0;
}

// X->0 , A->1 , B->2 , C->3 , D->4, E->5 , G-> 6

    /*
     Edges: 

     X->A = 2 (0,1)
     A->E = 3 (1,5)
     X->B = 2 (0,2)
     B->C = 2 (2,3)
     X->D = 3 (0,4)
     D->G = 5 (4,6)
     D->E = 1 (4,5)
     D->C = 1 (4,3)
     C->G = 3 (3,6)
     E->G = 5 (5,6)
    
    */
