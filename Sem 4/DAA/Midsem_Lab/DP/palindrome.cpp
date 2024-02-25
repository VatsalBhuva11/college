#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(int i, int j, string &s)
{
    if (i == j)
    {
        return true;
    }
    while (i < j)
    {
        if (s[i] != s[j])
        {
            return false;
        }
        i++;
        j--;
    }
    return true;
}
int partition(int i, int j, string &s, vector<vector<int>> &dp)
{
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    if (i >= j || isPalindrome(i, j, s))
    {
        return 0;
    }
    int mini = INT_MAX;
    for (int k = i; k < j; k++)
    {
        int temp = partition(i, k, s, dp) + partition(k + 1, j, s, dp) + 1;
        mini = min(temp, mini);
    }
    return dp[i][j] = mini;
}
int minCut(string s)
{
    int n = s.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    return partition(0, s.length() - 1, s, dp);
}

int main()
{
    string s;
    cin >> s;
    int go = minCut(s);
    cout << go << endl;
}