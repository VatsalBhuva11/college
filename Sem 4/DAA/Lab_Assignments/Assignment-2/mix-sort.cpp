#include <bits/stdc++.h>
using namespace std;

void shuffle_array(vector<int> &arr)
{

    // To obtain a time-based seed
    unsigned seed = 0;

    // Shuffling our array
    shuffle(arr.begin(), arr.end(),
            default_random_engine(seed));
}

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

void insertionSort(vector<int> &arr, int l, int r)
{
    for (int i = l + 1; i <= r; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= l && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void quickSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int pi = merge(arr, l, r);
        if (pi - l < 10)
            insertionSort(arr, l, pi - 1);
        else
            quickSort(arr, l, pi - 1);

        if (r - pi < 10)
            insertionSort(arr, pi + 1, r);
        else
            quickSort(arr, pi + 1, r);
    }
}

int main()
{
    vector<int> arr;
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    // calculating and logging time for randomized, sorted and reverse sorted array
    clock_t start, end;
    start = clock();
    shuffle_array(arr);
    cout << "Shuffled array: ";
    for (auto elem : arr)
    {
        cout << elem << " ";
    }
    cout << endl;
    quickSort(arr, 0, n - 1);
    end = clock();
    cout << "Time taken for random array: " << fixed << (double)(end - start) / (double)CLOCKS_PER_SEC << setprecision(7) << endl;

    cout << "Sorted array: ";
    for (auto elem : arr)
    {
        cout << elem << " ";
    }
    cout << endl;
    start = clock();
    quickSort(arr, 0, n - 1);
    end = clock();
    cout << "Time taken for sorted array: " << fixed << (double)(end - start) / (double)CLOCKS_PER_SEC << setprecision(7) << endl;

    reverse(arr.begin(), arr.end());
    cout << "Reversed array: ";
    for (auto elem : arr)
    {
        cout << elem << " ";
    }
    cout << endl;
    start = clock();
    quickSort(arr, 0, n - 1);
    end = clock();
    cout << "Time taken for reverse sorted array: " << fixed << (double)(end - start) / (double)CLOCKS_PER_SEC << setprecision(7) << endl;
    return 0;
}