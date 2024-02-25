#include <bits/stdc++.h>
using namespace std;

bool isValidTriangle(int a, int b, int c)
{
    return a + b > c && b + c > a && c + a > b;
}

vector<vector<int>> triplets(int n)
{
    string s = to_string(n);
    vector<vector<int>> ans;
    for (int i = 1; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (i > 0 && j - i > 0 && 5 - j > 0)
            {
                int num1 = stoi(s.substr(0, i));
                int num2 = stoi(s.substr(i, j - i));
                int num3 = stoi(s.substr(j));
                if (isValidTriangle(num1, num2, num3))
                {
                    vector<int> triplet = {num1, num2, num3};
                    sort(triplet.begin(), triplet.end(), greater<int>());
                    ans.push_back(triplet);
                }
            }
        }
    }
    return ans;
}

void pythagorean(vector<vector<int>> &triplets)
{
    for (auto triplet : triplets)
    {
        int val = triplet[1] * triplet[1] + triplet[2] * triplet[2];
        if (triplet[0] * triplet[0] == val)
        {
            cout << "(" << triplet[0] << "," << triplet[1] << "," << triplet[2] << ") is a pythagorean triplet." << endl;
            return;
        }
        else
        {
            if (abs(val - triplet[0] * triplet[0]) <= 1)
            {

                cout << "(" << triplet[0] << "," << triplet[1] << "," << triplet[2] << ") is nearly pythagorean" << endl;
            }
        }
    }
}

int main()
{
    cout << "Enter the 5 digit number: ";
    int n;
    cin >> n;
    vector<vector<int>> validTriplets = triplets(n);
    if (validTriplets.size() == 0)
    {
        cout << "There are no valid triangle triplets.";
    }
    else
    {

        cout << "Valid triangle triplets are:\n";
        for (auto vec : validTriplets)
        {
            for (auto elem : vec)
            {
                cout << elem << " ";
            }
            cout << endl;
        }

        pythagorean(validTriplets);
    }
    return 0;
}