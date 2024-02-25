#include <bits/stdc++.h>
using namespace std;

int maxDigitsInArr(vector<int> arr, int n)
{
    int mx = INT_MIN;
    for (auto elem : arr)
    {
        int ct = 0;
        while (elem)
        {
            elem /= 10;
            ct++;
        }
        mx = max(mx, ct);
    }
    return mx;
}

void radixSort(vector<int> &arr, int n)
{
    map<int, vector<int>> mp;
    int maximumDigits = maxDigitsInArr(arr, n);
    int i = 1;
    while (i <= maximumDigits)
    {
        for (auto elem : arr)
        {
            int element = elem;
            int digit;
            int j = i;
            while (j)
            {
                digit = element % 10;
                element /= 10;
                j--;
            }
            mp[digit].push_back(elem);
        }
        int temp = 0;
        for (auto pr : mp)
        {
            if (pr.second.size() > 0)
            {
                for (auto elem : pr.second)
                {
                    arr[temp++] = elem;
                }
            }
        }
        i++;
        mp.clear();
    }
}

int main()
{
    vector<int> arr = {17, 35, 102, 80, 65, 27, 109, 55};
    int n = arr.size();
    radixSort(arr, n);
    for (auto elem : arr)
    {
        cout << elem << " ";
    }
    cout << endl;
    return 0;
}