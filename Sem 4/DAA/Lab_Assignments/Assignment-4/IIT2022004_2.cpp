#include <bits/stdc++.h>
using namespace std;

bool isPossible(int arr[], int n, int m, int minOfMax)
{
    int stuReq = 1;
    int curr_sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > minOfMax)
            return false;

        if (curr_sum + arr[i] > minOfMax)
        {
            stuReq++;

            curr_sum = arr[i];
            if (stuReq > m)
                return false;
        }
        else
            curr_sum += arr[i];
    }
    return true;
}

int findPages(int arr[], int n, int m)
{
    long long sum = 0;
    if (n < m)
        return -1;
    int mx = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
        mx = max(mx, arr[i]);
    }
    int start = mx, end = sum;
    int result = INT_MAX;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (isPossible(arr, n, m, mid))
        {
            result = mid;
            end = mid - 1;
        }
        else
            start = mid + 1;
    }
    return result;
}

int main()
{
    int n;
    cout << "Number of books: ";
    cin >> n;
    int m;
    cout << "Number of students: ";
    cin >> m;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << "Minimum number of pages = "
         << findPages(arr, n, m) << endl;
    return 0;
}