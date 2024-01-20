#include <bits/stdc++.h>
using namespace std;

int main()
{
    clock_t start, end;

    int n;
    cout << "Enter size of array: ";
    cin >> n;
    vector<int> arr;
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    int elem;
    cout << "Enter element to search: ";
    cin >> elem;
    int low = 0, high = n - 1, index = -1;

    start = clock();
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == elem)
        {
            index = mid;
            break;
        }
        else if (arr[mid] < elem)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (index == -1)
        cout << "Element not found\n";
    else
        cout << "Element found at index " << index << "\n";

    end = clock();

    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}