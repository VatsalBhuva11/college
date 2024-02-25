/*
NAME: VATSAL BHUVA
ROLL NO.: IIT2022004
SECTION: A
QUESTION: 4
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> fib = {0, 1};
    int prev = fib[0], curr = fib[1];
    for (int i = 0; i < 45; i++)
    {
        int next = prev + curr;
        fib.push_back(next);
        prev = curr;
        curr = next;
    }
    int q;
    cin >> q;
    while (q--)
    {
        int lo = 0, hi = 45;
        int target;
        cout << "Enter element to verify in Fib. : ";
        cin >> target;

        int flag = 0;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (fib[mid] == target)
            {
                cout << "Element belongs to fibonacci series, at position " << mid + 1 << endl;
                flag = 1;
                break;
            }
            else
            {
                if (fib[mid] < target)
                    lo = mid + 1;
                else
                    hi = mid - 1;
            }
        }
        if (!flag)
        {
            cout << "Element does not belong to fibonacci series.\n";
            if (target - fib[hi] < fib[lo] - target)
            {
                cout << "Closest element is: " << fib[hi] << endl;
            }
            else
            {
                cout << "Closest element is: " << fib[lo] << endl;
            }
        }
    }

    return 0;
}