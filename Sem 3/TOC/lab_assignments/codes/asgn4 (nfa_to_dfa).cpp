#include <bits/stdc++.h>
using namespace std;

unordered_map<string,int> possibleStates={
    {"0",1},
    {"1",0},
    {"2",0},
    {"01",0},
    {"02",0},
    {"12",0},
    {"012",0},
};

string Vector2String(vector<int>v){
    string s;
    for(int i=0; i<v.size(); i++){
        s+=to_string(v[i]);
    }   
    return s;
}

int main(){
    vector<vector<vector<int>>> nfaTable;
    for(int i=0;i<3;i++){
		cout<<"For state "<<i<<endl;
		vector< vector< int > > v;
		int a=0;
		int y,yn;
		for(int j=0;j<2;j++){
			vector<int> t;
			cout<<"Enter no. of output states for input "<<a++<<" : ";
			cin>>yn;
			cout<<"Enter output states :\n(For null state or death state input -1)\n"<<endl;
			for(int k=0;k<yn;k++){
				cin>>y;
				t.push_back(y);
			}
			v.push_back(t);
		}
        nfaTable.push_back(v);
    }
    vector<vector<vector<int>>> dfaTable;
    stack<vector<int>>s;
    s.push({0});
    vector<vector<int>>newStates;
    while(!s.empty()){
        vector<int> currState=s.top();
        newStates.push_back(s.top());
        // for(auto i:currState) cout<<i<<" ";
        // cout<<endl;
        s.pop();
        vector<vector<int>> temp;
        for(int j=0; j<2; j++){
            // if(j==1) cout<<j<<endl;
            vector<int>jThSymbol;
            set<int>tempSet;
            for(int i=0; i<currState.size(); i++){
                for(int k=0; k<nfaTable[currState[i]][j].size(); k++){
                    tempSet.insert(nfaTable[currState[i]][j][k]);
                    // if (j==1 and i==1) cout<<nfaTable[currState[i]][j][k]<<endl;
                }
            }
            //if (j==1) cout<<tempSet.size()<<endl;
            for(auto it:tempSet) {
                jThSymbol.push_back(it);
            }
            //if (j==1) {for(auto i:jThSymbol) cout<<i<<" "; cout<<endl;}
            if (!possibleStates[Vector2String(jThSymbol)]){
                possibleStates[Vector2String(jThSymbol)]=1;
                s.push(jThSymbol);
                //cout<<s.top().size()<<endl;
            }
            temp.push_back(jThSymbol);
            // cout<<temp.size()<<endl;
        }
        dfaTable.push_back(temp);
        
    }
    //cout<<dfaTable.size()<<endl;
    cout<<"\nDFA\n";
    cout<<"Q\t0\t1\n";
    for(int i=0; i<dfaTable.size(); i++){
        for(int l=0; l<newStates[i].size(); l++){
            cout<<newStates[i][l];
        }
        cout<<"\t";
        for(int j=0; j<2; j++){
            for(int k=0; k<dfaTable[i][j].size(); k++){
                cout<<dfaTable[i][j][k];
            }
            cout<<"\t";
        }
        cout<<endl;
    }
}