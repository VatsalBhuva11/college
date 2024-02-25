#include <bits/stdc++.h>
using namespace std;

int bruteNumberOfWays(int n, int i)
{
    if (i > n)
        return 0;
    if (i == n)
    {
        return 1;
    }
    int withOneStep = bruteNumberOfWays(n, i + 1);
    int withTwoSteps = bruteNumberOfWays(n, i + 2);
    return withOneStep + withTwoSteps;
}

int optimisedNumberOfWays(int n, int i, vector<int> &dp)
{
    if (i > n)
        return 0;
    if (i == n)
    {
        return 1;
    }
    if (dp[i] != -1)
        return dp[i];

    int withOneStep = optimisedNumberOfWays(n, i + 1, dp);
    int withTwoSteps = optimisedNumberOfWays(n, i + 2, dp);
    return dp[i] = withOneStep + withTwoSteps;
}

int main()
{
    int n;
    cin >> n;
    vector<int> dp(n + 1, -1);
    cout << "Number of ways using brute: " << bruteNumberOfWays(n, 0) << endl;
    cout << "Number of ways using optimised: " << optimisedNumberOfWays(n, 0, dp) << endl;

    return 0;
}