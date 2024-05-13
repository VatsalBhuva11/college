#include <bits/stdc++.h>
using namespace std;

#define V 6


int bfs(vector<vector<int>>&resG, int s, int t, vector<int>&parent)
{
	
	bool v[V];
	queue<int> q;
	q.push(s);
	v[s] = true;
	parent[s] = -1;
    int mini = INT_MAX;
                                                                                                                                                    memset(v, 0, sizeof(v));
	while (!q.empty()) {
		int par = q.front();
		q.pop();

		for (int child = 0; child < V; child++) {
			if (!resG[par][child] <= 0 && v[child] == false) {
                mini = min(mini, resG[par][child]);
				if (child == t) {
					parent[child] = par;
					return mini;
				}
				q.push(child);
				parent[child] = par;
				v[child] = true;
			}
		}
	}
	return 0;
}


int main()
{
    int s = 0, t = 5;
	vector<vector<int>>graph = { 
            {0,10,10,0,0,0}, 
            {0,0,2,4,8,0},
			{0,0,0,0,9,0}, 
            {0,0,0,0,6,10},
			{0,0,0,0,0,10}, 
            {0,0,0,0,0,0} };

    vector<vector<int>>resG(V, vector<int>(V,0));
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			resG[i][j] = graph[i][j];

    vector<int>parent(V,0);
	int max_flow = 0; 
    int min_flow=0;
	
	while (min_flow = bfs(resG, s, t, parent)) {
        int u;
		for (int v = t; v != s; v = parent[v]) {
			u = parent[v];
			resG[u][v] -= min_flow;
			resG[v][u] += min_flow;
		}
        max_flow += min_flow;

	}

	cout << "MAX FLOW: "<< max_flow<<endl;

	return 0;
}



