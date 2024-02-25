#include <bits/stdc++.h>
using namespace std;
void findLIS(vector<vector<int>> &result, vector<int> &temp, vector<int> &arr,
             int index)
{
    if (index == arr.size())
    {
        if (temp.size() > 0)
        {
            result.push_back(temp);
        }
        return;
    }
    if (temp.empty() || arr[index] > temp.back())
    {
        temp.push_back(arr[index]);
        findLIS(result, temp, arr, index + 1);
        temp.pop_back();
    }
    findLIS(result, temp, arr, index + 1);
}
vector<vector<int>> get_LIS(vector<int> &arr)
{
    vector<vector<int>> result;
    vector<int> temp;
    findLIS(result, temp, arr, 0);
    int max_length = 0;
    for (auto &lis : result)
    {
        max_length = max(max_length, (int)(lis.size()));
    }
    vector<vector<int>> longest_lis;
    for (auto &lis : result)
    {
        if (lis.size() == max_length)
        {
            longest_lis.push_back(lis);
        }
    }
    return longest_lis;
}

void printLIS(vector<vector<int>> &arr)
{
    for (auto vec : arr)
    {

        for (auto x : vec)
            cout << x << " ";
        cout << endl;
    }
}
int main()
{
    cout << "Enter number of elements: ";
    int n;
    cin >> n;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int elem;
        cin >> elem;
        arr.push_back(elem);
    }
    vector<vector<int>> LIS = get_LIS(arr);
    printLIS(LIS);
    return 0;
}