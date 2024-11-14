#include <iostream>
using namespace std;

// Function to display the truth table header
void displayHeader()
{
    cout << "p(x)\tq(x)\tr(x)\ts(x)\tp(x) AND q(x)\tp(x) AND r(x) AND s(x)\t(p(x) AND r(x)) -> s(x)\ts(x) <-> r(x)" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
}

// Function to display the truth table for the given predicates
void displayTruthTable()
{
    // Loop through all possible truth values (0 = false, 1 = true)
    for (int p = 0; p <= 1; p++)
    {
        for (int q = 0; q <= 1; q++)
        {
            for (int r = 0; r <= 1; r++)
            {
                for (int s = 0; s <= 1; s++)
                {
                    // Calculate compound statements
                    int p_and_q = p && q;
                    int p_and_r_and_s = p && r && s;
                    int implication = !(p && r) || s; // (p AND r) -> s is equivalent to NOT(p AND r) OR s
                    int biconditional = (s == r);     // s <-> r is true when s and r are the same

                    // Display the truth values for each combination
                    cout << p << "\t" << q << "\t" << r << "\t" << s << "\t";
                    cout << p_and_q << "\t\t";
                    cout << p_and_r_and_s << "\t\t\t";
                    cout << implication << "\t\t\t";
                    cout << biconditional << endl;
                }
            }
        }
    }
}

int main()
{
    // Display the header for the truth table
    displayHeader();

    // Generate and display the truth table for the given predicates
    displayTruthTable();

    return 0;
}
