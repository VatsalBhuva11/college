#include <bits/stdc++.h>
using namespace std;

int rodcutting(vector<int> wt, vector<int> val, int n, int w)
{
  int t[n + 1][w + 1];
  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j <= w; j++)
    {
      if (i == 0 or j == 0)
      {
        t[i][j] = 0;
      }
    }
  }
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= w; j++)
    {
      if (wt[i - 1] <= j)
      {
        t[i][j] = max(val[i - 1] + t[i][j - wt[i - 1]], t[i - 1][j]);
      }
      else
      {
        t[i][j] = t[i - 1][j];
      }
    }
  }
  return t[n][w];
}

int main()
{
  int n;
  cout << "Enter n " << endl;
  cin >> n;
  vector<int> val;
  vector<int> wt;
  cout << "Enter weights " << endl;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    wt.push_back(x);
  }
  cout << "Enter values " << endl;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    val.push_back(x);
  }
  int weight;
  int j = rodcutting(wt, val, n, n);
  cout << "Max Value will be " << j << endl;
}