#include<bits/stdc++.h>
using namespace std;


vector<int> greedypath(vector<vector<pair<int,int>>> &adj,int V,int s,int target){

   priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> vis(V,0);
    vector<int> parent(V,-1);
    parent[s]=s;

    vector<int> dist(V,1e9);

    dist[s]=0;
    
    pq.push({0,s});

    while(!pq.empty()){

        int node = pq.top().second;
        int wt = pq.top().first;

        pq.pop();

         for (auto it : adj[node]) {
            int adjNode = it.first;
            int distwt = it.second;

            if (distwt + wt < dist[adjNode]) {
                dist[adjNode] = distwt + wt;
                pq.push({dist[adjNode], adjNode});
                parent[adjNode] = node;
            }
        }
    }

        vector<int> ans;
        int node = target;

        if(dist[target] == 1e9) return {};

        while(parent[node]!=node){
            ans.push_back(node);
            node = parent[node];
        }
        ans.push_back(node);
        reverse(ans.begin(),ans.end());

        return ans;

}

int main(){

    int V;
    cout<<"Enter number of vertices:\n";
    cin>>V;

    int edges;
    cout<<"Enter number of edges:\n";
    cin>>edges;

    vector<vector<pair<int,int>>> adj(V);

    for(int i=0;i<edges;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        adj[u].push_back({v,wt});
        adj[v].push_back({u,wt});

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

    //cout<<greedypath(adj,V,0,6);

    vector<int> ans = greedypath(adj,V,0,6);

    for(int i=0;i<ans.size();i++) cout<<ans[i]<<"->";

    return 0;
}