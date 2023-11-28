#include <bits/stdc++.h>
using namespace std;
const int N = 51;

int table[N][N];
bool finalStates[N];
int numState, numSymbols, numFinalState;

void print(vector<int>&v){
    for(int i=0; i<v.size(); i++){
        cout<<v[i];
    }
}

int main(){
    cout <<"Enter the number of states:"<<endl; cin >> numState;
    cout << "Enter the number of symbols:" << endl; cin >> numSymbols;
    cout << "Enter the number of final states:" << endl; cin >> numFinalState;
    cout << "Enter the final states:" << endl;
    for (int i = 0; i < numFinalState; ++i){
        int x; cin >> x;
        finalStates[x] = 1;
    }
    cout << "Input the transition table:" << endl;
    for (int i = 0; i < numState; i++){
        for (int j = 0; j < numSymbols; j++){
            cin >> table[i][j];
        }
    }
    unordered_map<int,int>m1,m2;
    int temp=0;
    for(int i=0; i<numState; i++){
        if (finalStates[i]==1){
            m1[i]=temp; m2[i]=temp;
        }
    }
    temp++;
    for(int i=0; i<numState; i++){
        if (finalStates[i]==0){
            m1[i]=temp; m2[i]=temp;
        }
    }
    temp++;
    int ct=0;
    while(1){
        int prev=ct;
        vector<int> visited(51,-1);
        for(int i=0; i<numState; i++){
            if (visited[m1[i]]==-1){
                visited[m1[i]]=1;
                for(int j=i+1; j<numState; j++){
                    if (m1[i]==m1[j]){
                        if (m1[table[i][0]]==m1[table[j][0]] and m1[table[i][1]]==m1[table[j][1]]) continue;
                        else {
                            m2[j]=temp;
                            ct++;
                        }
                    }
                }
            }
        }
        for(int k=0; k<numState; k++){
            m1[k]=m2[k];
        }
        if (prev==ct) break;
        temp++;
    }
    unordered_map<int,vector<int>>mnew;
    for(int i=0; i<temp; i++){
        for(int j=0; j<numState; j++){
            if(m1[j]==i){
                mnew[i].push_back(j);
            }
        }
    }
    cout << "\nThe Minimised Table for given DFA is:\n";
    cout << "Q\t"<<"0\t"<<"1"<<endl;
    for(int i=0;i<temp; i++){
        bool f=0;
        for(int j=0; j<numState; j++){
            if (m1[j]==i){
                print(mnew[i]); cout<<"\t";print(mnew[m1[table[j][0]]]);cout<<"\t";print(mnew[m1[table[j][1]]]);
                cout<<endl;
                f=1; break;
            }
        }
        if (f) continue;
    }
}