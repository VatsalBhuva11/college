/*
NAME: VATSAL BHUVA
ROLL NO.: IIT2022004
SECTION: A
QUESTION: 3
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    srand(time(0));
    vector<pair<int, int>> points;
    /*-*/
    unordered_map<int, vector<int>> xCollinear, yCollinear;
    int n = 5000;

    for (int i = 0; i < n; i++)
    {
        int x, y;
        x = rand() % n;
        y = rand() % n;
        yCollinear[x].push_back(y);
        xCollinear[y].push_back(x);
    }

    // i) collinear to x axis means y same.
    cout << "Points collinear to x-axis:" << endl;
    for (auto pr : xCollinear)
    {
        cout << "At y=" << pr.first << ":\n";
        if (pr.second.size() > 0)
        {
            for (auto xCoord : pr.second)
            {
                cout << "(" << pr.first << "," << xCoord << "), ";
            }
            cout << endl;
        }
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Points collinear to y-axis:" << endl;
    for (auto pr : yCollinear)
    {
        cout << "At x=" << pr.first << ":\n";
        if (pr.second.size() > 0)
        {

            for (auto yCoord : pr.second)
            {
                cout << "(" << pr.first << "," << yCoord << "), ";
            }
            cout << endl;
        }
    }

    return 0;
}