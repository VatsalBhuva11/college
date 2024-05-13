#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int>weights = {10,20,30};
    vector<int>values = {60,100,120};
    set<pair<float,int>, greater<pair<float,int>>> ratio;
    for (int i = 0; i<3; i++) {
        ratio.insert({values[i]/weights[i], i});
    }
    int x = 50;
    int total = 0;
    while (x > 0 && ratio.size() >= 0) {
        pair<float,int>curr = *(ratio.begin());
        float r = curr.first;
        int item = curr.second;
        if (weights[item] == 0) {
            ratio.erase(ratio.begin());
        } else {
            total += r;
            weights[item] -= 1; 
            x -= 1;
        }
    }
    cout<<"MAX VALUE: "<<total<<endl;
}