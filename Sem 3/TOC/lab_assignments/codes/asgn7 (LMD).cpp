#include <bits/stdc++.h>
#include <cstring>
#include <stack>

using namespace std;

char productions[][4] = {"A1B", "0A", "ε", "0B", "1B", "ε"};

void leftmostDerivation(const char* input) {
    stack<char> derivationStack;
    int inputIndex = 0;
    derivationStack.push('S'); 

    cout << "Leftmost Derivation Steps:" << endl;

    while (!derivationStack.empty()) {
        char currentSymbol = derivationStack.top();
        derivationStack.pop();

        if (currentSymbol >= 'A' && currentSymbol <= 'B') {
            char* production = nullptr;
            if (currentSymbol == 'A') {
                if (input[inputIndex] == '0') {
                    production = productions[1];
                } else {
                    production = productions[2];
                }
            } else if (currentSymbol == 'B') {
                if (input[inputIndex] == '0') {
                    production = productions[3];
                } else if (input[inputIndex] == '1') {
                    production = productions[4];
                } else {
                    production = productions[5];
                }
            }

            int len = strlen(production);
            for (int i = len - 1; i >= 0; i--) {
                if (production[i] != 'ε') {
                    derivationStack.push(production[i]);
                }
            }

            cout << "Step " << inputIndex + 1 << ": ";
            cout << "Replace " << currentSymbol << " with " << production << endl;

            if (input[inputIndex] != '\0') {
                inputIndex++;
            }
        } else {
            cout << "Step " << inputIndex + 1 << ": ";
            cout << "Keep " << currentSymbol << endl;
        }
    }

    cout << "Final Derivation: ";
    cout << "S -> " << input << endl;
}

int main() {
    const char* input = "00101"; 
    leftmostDerivation(input);

    return 0;
}