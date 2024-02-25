#include <bits/stdc++.h>
using namespace std;

int bruteNumberOfWays(int m, int n, int i, int j)
{
    if (i >= m || j >= n)
        return 0;
    if (i == m - 1 && j == n - 1)
        return 1;
    int down = bruteNumberOfWays(m, n, i + 1, j);
    int right = bruteNumberOfWays(m, n, i, j + 1);
    return down + right;
}

int optimisedNumberOfWays(int m, int n, int i, int j, vector<vector<int>> &dp)
{
    if (i >= m || j >= n)
        return 0;
    if (i == m - 1 && j == n - 1)
        return 1;
    if (dp[i][j] != -1)
        return dp[i][j];
    int down = optimisedNumberOfWays(m, n, i + 1, j, dp);
    int right = optimisedNumberOfWays(m, n, i, j + 1, dp);
    return dp[i][j] = down + right;
}

int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    cout << "Number of ways using brute: " << bruteNumberOfWays(m, n, 0, 0) << endl;
    cout << "Number of ways using optimised: " << optimisedNumberOfWays(m, n, 0, 0, dp) << endl;

    return 0;
}