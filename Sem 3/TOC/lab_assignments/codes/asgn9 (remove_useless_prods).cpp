#include<bits/stdc++.h>
using namespace std;

int main()
{
    map<char,int>visited;
    map<char,int> terminals;
    vector<pair<char,string>> productions;
    vector<pair<char,string>> ans;
    int n;
    cout<<"Enter of of Productions : ";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        char left;
        string right;
        cout<<"Enter left side : ";
        cin>>left;
        cout<<"Enter right side : ";
        cin>>right;
        if(right[right.length()-1] >= 'a' && right[right.length()-1] <= 'z')
        {
            if(right[0] >= 'a' && right[0] <= 'z')
            terminals[left]++;
            terminals[right[0]]++;
        }
        for(int i=0;i<right.length();i++)
        {
            if(right[i] >= 'A' && right[i] <= 'Z')
            visited[right[i]]++;
        }
        productions.push_back({left,right});
    }
    for(auto it : productions)
    {
        if(terminals[it.first] > 0 && visited[it.first] > 0 && terminals[it.second[it.second.length()-1]] > 0)
        ans.push_back({it.first,it.second});
        else if(it.first == 'S' && terminals[it.second[it.second.length()-1]] > 0)
        {
            ans.push_back({it.first,it.second});
        }
        else if(visited[it.first] >0 )
       { int flag = 0;
        for(auto ch : it.second)
        {
            if((terminals[ch] > 0 && visited[ch] >0) || (ch >= 'a' && ch <= 'z'))
            continue;
            else
            flag++;
        }
        if(flag == 0)
        ans.push_back({it.first,it.second});}
    }

    for(auto it : ans)
    {
        cout<<it.first<<"  -->  "<<it.second<<endl;
    }
    return 0;
}