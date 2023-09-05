#include <bits/stdc++.h>
using namespace std;



int trans[7][2]={
	{1,2},
	{5,4},
	{6,4},
	{0,4},
	{4,4},
	{5,5},
	{6,6}
};
vector<bool> unreachable(7,true);
vector<vector<vector<int>>> ans;
set<set<int>> curs;
int cur_ct=0;

vector<int> fin_states={5,6};
vector<int> nonfin={0,1,2,3,4};
set<int> initial={0};
bool check(set<int> s,int s1,int s2){
	if(!((s.find(trans[s1][0])!=s.end() && s.find(trans[s2][0])!=s.end())|| (s.find(trans[s1][0])==s.end() && s.find(trans[s2][0])==s.end()))){
		return false;
	}
	if(!((s.find(trans[s1][1])!=s.end() && s.find(trans[s2][1])!=s.end()) || (s.find(trans[s1][1])==s.end() && s.find(trans[s2][1])==s.end()))){
		return false;
	}
	return true;
}
int main(){
	for(int i=0;i<2;i++){
		for(int j=0;j<7;j++){
			unreachable[trans[j][i]]=false;
		}
	}
		set<int> q1,q2;
		for(auto x:fin_states){
			q1.insert(x);

		}
		for(auto x:nonfin){
			q2.insert(x);
		}
		curs.insert(q1);
		curs.insert(q2);
		int prev_ct=0;
		cur_ct=2;
		while(cur_ct!=prev_ct){
			set<set<int>> pis;
			for(auto x:curs){

				for(auto y:x){
					set<int> temp;
					for(auto z:x){
						if(check(x,y,z)){
							temp.insert(y);
							temp.insert(z);
						}
					}
					pis.insert(temp);
				}
			}
			prev_ct=cur_ct;
			cur_ct=pis.size();
			curs=pis;
		}
		cout<<"\nMinimized DFA contains the following states:\n";
		
		for(auto x: curs){
			
			for(auto y:x){
				if(!unreachable[y]) cout<<y<<" ";
				else cout<<y<<" (unreachable)";
				
			}
			
			cout<<endl;
		}
		cout<<"      "<<0<<"   "<<1<<endl;
		for(auto x: curs){
			int a0,a1;
			for(auto y:x){
				cout<<y<<" ";
				a0=trans[y][0];
				a1=trans[y][1];
			}
			for(int i=0;i<3-x.size();i++){
				cout<<"  ";
			}
			cout<<a0<<"   "<<a1;
			cout<<endl;
		}


}
