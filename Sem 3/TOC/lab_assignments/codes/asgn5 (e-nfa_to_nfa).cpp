#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<vector<int>>> nullNfaTable;
    for(int i=0;i<3;i++){
		cout<<"For state "<<i<<endl;
		vector<vector<int>> v;
		int a=0;
		int y,yn;
		for(int j=0;j<3;j++){
			vector<int> t;
            if (j == 2){
			    cout<<"Enter no. of output states for input epsilon : ";
            } else {
		        cout<<"Enter no. of output states for input "<<a++<<" : ";
            }
			cin>>yn;
			cout<<"Enter output states :"<<endl;
			for(int k=0;k<yn;k++){
				cin>>y;
				t.push_back(y);
			}
			v.push_back(t);
		}
        nullNfaTable.push_back(v);
    }
    // cout<<nullNfaTable[2][1][0]<<endl;
    vector<vector<vector<int>>> nfaTable;
    for(int i=0; i<3; i++){
        vector<vector<int>>temp;
        for(int j=0; j<2; j++){
            //cout<<j<<endl;
            vector<int>jThSymbol;
            set<int>tempSet;
            for(int k=0; k<nullNfaTable[i][2].size(); k++){
                int state=nullNfaTable[i][2][k];
                //cout<<state<<" ";
                for(int l=0; l<nullNfaTable[state][j].size(); l++){
                    //cout<<nullNfaTable[state][j][l]<<endl;
                    for(int m=0; m<nullNfaTable[nullNfaTable[state][j][l]][2].size(); m++){
                        //cout<<nullNfaTable[nullNfaTable[state][j][l]][2][m]<<endl;
                        tempSet.insert(nullNfaTable[nullNfaTable[state][j][l]][2][m]);
                    }
                }
            }
            for(auto it:tempSet){
                jThSymbol.push_back(it);
            }
            // for(auto i: jThSymbol) cout<<i<<" ";
            // cout<<endl;
            temp.push_back(jThSymbol);
        }
        nfaTable.push_back(temp);
    }
    cout<<"\nNFA\n";
    cout<<"Q\t0\t1\n";
    for(int i=0; i<nfaTable.size(); i++){
        cout<<i;
        cout<<"\t";
        for(int j=0; j<2; j++){
            for(int k=0; k<nfaTable[i][j].size(); k++){
                cout<<nfaTable[i][j][k];
            }
            cout<<"\t";
        }
        cout<<endl;
    }
}