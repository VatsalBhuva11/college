#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function for classification using Gender first (Scenario A)
string classify_by_gender(string gender, double height)
{
    if (gender == "M")
    { // Male
        if (height > 2.0)
        {
            return "T"; // Tall
        }
        else
        {
            return "M"; // Medium
        }
    }
    else if (gender == "F")
    { // Female
        if (height > 1.88)
        {
            return "M"; // Medium
        }
        else
        {
            return "S"; // Short
        }
    }
    return "Unknown";
}

// Function for classification using Height first (Scenario B)
string classify_by_height(double height)
{
    if (height <= 1.7)
    {
        return "S"; // Short
    }
    else if (height > 1.7 && height <= 2.0)
    {
        return "M"; // Medium
    }
    else
    {
        return "T"; // Tall
    }
}

int main()
{
    // Test data: vector of pairs (gender, height)
    vector<pair<string, double>> test_data = {
        {"M", 1.8},
        {"F", 1.9},
        {"M", 2.1},
        {"F", 1.6},
        {"M", 1.95},
        {"F", 1.75}};

    // Classifications using Gender First (Scenario A)
    cout << "Classifications using Gender First (Scenario A):" << endl;
    for (auto &person : test_data)
    {
        string gender = person.first;
        double height = person.second;
        string classification = classify_by_gender(gender, height);
        cout << "Gender: " << gender << ", Height: " << height << " -> Class: " << classification << endl;
    }

    // Classifications using Height First (Scenario B)
    cout << "\nClassifications using Height First (Scenario B):" << endl;
    for (auto &person : test_data)
    {
        double height = person.second;
        string classification = classify_by_height(height);
        cout << "Height: " << height << " -> Class: " << classification << endl;
    }

    return 0;
}
