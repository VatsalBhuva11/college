#include <bits/stdc++.h>
using namespace std;

int min(int x, int y, int z) { return min(min(x, y), z); }
string deleteChar(string s, int i)
{
    s.erase(s.begin() + i);
    return s;
}

string addChar(string s, int i, char c)
{
    int j = 0;
    int n = s.size();
    string output = "";
    while (j < n)
    {
        if (j == i)
        {
            output += c;
            j++;
            n++;
        }
        else
        {
            output += s[j];
            j++;
        }
    }
    return output;
}

int editDist(string &str1, string &str2, int m, int n, vector<vector<int>> &dp)
{
    if (dp[m][n] != -1)
    {
        return dp[m][n];
    }

    if (m == 0)
    {
        return dp[m][n] = n; // Insert all remaining characters from str2
    }
    if (n == 0)
    {
        return dp[m][n] = m; // Delete all characters from str1
    }

    if (str1[m - 1] == str2[n - 1])
    {
        // No operation needed if characters match
        return dp[m][n] = editDist(str1, str2, m - 1, n - 1, dp);
    }

    string s1 = addChar(str1, m, str2[n - 1]);
    string s2 = deleteChar(str1, m - 1);

    // Calculate minimum cost for each operation, incorporating addChar and deleteChar:
    int insertCost = 1 + editDist(s1, str2, m + 1, n, dp);        // Insert from str2
    int deleteCost = 1 + editDist(s2, str2, m - 1, n, dp);        // Delete from str1
    int replaceCost = 1 + editDist(str1, str2, m - 1, n - 1, dp); // Replace in str1

    // Return the minimum cost:
    return dp[m][n] = std::min({insertCost, deleteCost, replaceCost});
}

int main()
{
    string str1 = "abcdef";
    string str2 = "aghbidef";
    // string str1 = "abc";
    // string str2 = "abdc";
    int m = str1.size();
    int n = str2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

    cout << editDist(str1, str2, str1.length(),
                     str2.length(), dp)
         << endl;

    return 0;
}
