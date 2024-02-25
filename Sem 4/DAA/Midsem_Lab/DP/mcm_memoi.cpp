#include <bits/stdc++.h>
using namespace std;
int t[1001][1001];
int solve(int a[], int i, int j)
{
  if (i >= j)
  {
    return 0;
  }
  if(t[i][j]!=-1){
    return t[i][j];
  }
  int min = INT_MAX;
  for (int k = i; k < j; k++)
  {
    int temp = solve(a, i, k) + solve(a, k + 1, j) + (a[i - 1] * a[k] * a[j]);
    if (temp < min)
    {
      min = temp;
    }
  }
  return t[i][j]=min;
}

int main()
{
  int n;
  cin >> n;
  int a[n];
  for(int i=0;i<=n;i++){
    for(int j=0;j<=n;j++){
      t[i][j]=-1;
    }
  }
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
  }
  int go = solve(a, 1, n - 1);
  cout << go << endl;
}
