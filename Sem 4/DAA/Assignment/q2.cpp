/*
NAME: VATSAL BHUVA
ROLL NO.: IIT2022004
SECTION: A
QUESTION: 2
*/

#include <bits/stdc++.h>
using namespace std;

int bubble_sort(vector<int> arr, int n)
{
    int swaps = 0;
    for (int i = 0; i < n; i++)
    {
        bool isSwapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swaps++;
                isSwapped = true;
            }
        }
        if (!isSwapped)
            return swaps;
    }
    return swaps;
}

int selection_sort(vector<int> arr, int n)
{
    int swaps = 0;

    for (int i = 0; i < n; i++)
    {
        int mini = arr[i];
        int miniIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < mini)
            {
                mini = arr[j];
                miniIndex = j;
            }
        }
        if (miniIndex != i)
        {
            swap(arr[i], arr[miniIndex]);
            swaps++;
        }
    }

    return swaps;
}

int insertion_sort(vector<int> arr, int n)
{
    int swaps = 0;
    for (int i = 1; i < n; i++)
    {
        int flag = 0;
        int j = i - 1;
        for (; j >= 0; j--)
        {
            if (arr[j] > arr[j + 1])
            {
                arr[j + 1] = arr[j];
            }
            else
            {
                break;
            }
        }
        if (j != i - 1)
        {
            swap(arr[j + 1], arr[i]);
            swaps++;
        }
    }
    return swaps;
}

int main()
{
    srand(time(0));
    vector<int> arr;
    int n = 1000;
    for (int i = 0; i < n; i++)
    {
        int num = rand() % n;
        arr.push_back(num);
    }
    cout << "Swaps in bubble sort: " << bubble_sort(arr, n) << endl;
    cout << "Swaps in selection sort: " << selection_sort(arr, n) << endl;
    cout << "Swaps in insertion sort: " << insertion_sort(arr, n) << endl;

    return 0;
}