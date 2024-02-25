#include <bits/stdc++.h>
using namespace std;

int merge(vector<int> &arr, int l, int r)
{
    int pivot = arr[r];
    int i = l - 1;
    for (int j = l; j < r; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

void quickSort(vector<int> &arr, int l, int r, int k)
{
    if (l < r)
    {
        int pi = merge(arr, l, r);
        if (pi == k)
        {
            cout << k << "th smallest element: " << arr[pi] << endl;
            return;
        }
        quickSort(arr, l, pi - 1, k);
        quickSort(arr, pi + 1, r, k);
    }
}

int main()
{
    int n;
    cout << "Enter size of array: ";
    cin >> n;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        arr.push_back(temp);
    }
    cout << "Enter k (kth smallest element): ";
    int k;
    cin >> k;
    quickSort(arr, 0, n, k);

    return 0;
}