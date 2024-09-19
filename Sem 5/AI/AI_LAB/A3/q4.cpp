#include<bits/stdc++.h>

using namespace std;

class TicTacToe {
private:
    vector<int> board;
    vector<int> magicSquare;
    vector<bool> marked;
    char player, opponent;

public:
    TicTacToe() : board(9, 0), marked(9, false), player('X'), opponent('O') {
        magicSquare = {8, 1, 6, 3, 5, 7, 4, 9, 2}; // Magic square values
    }

    void printBoard() {
        cout << "Board:\n";
        for (int i = 0; i < 9; ++i) {
            if (board[i] == 0)
                cout << "- ";
            else if (board[i] == 1)
                cout << "X ";
            else
                cout << "O ";

            if ((i + 1) % 3 == 0)
                cout << endl;
        }
    }

    bool isWinning(vector<int>& selected) {
        int sum = 0;
        for (int pos : selected) {
            sum += magicSquare[pos];
        }
        return sum == 15;
    }

    bool checkWin(char turn) {
        vector<int> selected;

        for (int i = 0; i < 9; ++i) {
            if ((turn == 'X' && board[i] == 1) || (turn == 'O' && board[i] == 2)) {
                selected.push_back(i);
            }
        }

        if (selected.size() >= 3) {
            // Check all combinations of 3
            for (int i = 0; i < selected.size() - 2; ++i) {
                for (int j = i + 1; j < selected.size() - 1; ++j) {
                    for (int k = j + 1; k < selected.size(); ++k) {
                        vector<int> subset = {selected[i], selected[j], selected[k]};
                        if (isWinning(subset)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool isFull() {
        for (bool m : marked) {
            if (!m) return false;
        }
        return true;
    }

    void makeMove(int pos, char turn) {
        board[pos] = (turn == 'X') ? 1 : 2;
        marked[pos] = true;
    }

    void play() {
        int move;
        char turn = player;

        while (true) {
            printBoard();
            cout << "Player " << turn << ", enter your move (1-9): ";
            cin >> move;

            if (move < 1 || move > 9 || marked[move - 1]) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            makeMove(move - 1, turn);

            if (checkWin(turn)) {
                printBoard();
                cout << "Player " << turn << " wins!\n";
                break;
            }

            if (isFull()) {
                printBoard();
                cout << "The game is a draw!\n";
                break;
            }

            turn = (turn == player) ? opponent : player;
        }
    }
};

int main() {
    TicTacToe game;
    game.play();

    return 0;
}
