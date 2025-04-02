#include <iostream>
#include <vector>
#include <limits>  // For input validation
#include <string>  // For string manipulation
using namespace std;

void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) cout << "- - - - - - - - - - -\n";
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) cout << "| ";
            cout << (board[i][j] ? to_string(board[i][j]) : ".") << " ";
        }
        cout << "\n";
    }
}

bool isValid(const vector<vector<int>>& board, int row, int col, int num) {
    for (int j = 0; j < 9; j++) if (board[row][j] == num) return false;
    for (int i = 0; i < 9; i++) if (board[i][col] == num) return false;
    int boxRow = 3 * (row / 3), boxCol = 3 * (col / 3);
    for (int i = 0; i < 3; i++) 
        for (int j = 0; j < 3; j++) 
            if (board[boxRow + i][boxCol + j] == num) return false;
    return true;
}

bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board)) return true;
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<vector<int>> board(9, vector<int>(9));
    
    cout << "Enter Sudoku (9x9 grid, 0=empty, space-separated):\n";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            while (!(cin >> board[i][j])) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid. Enter 0-9: ";
            }
        }
    }

    cout << "\nUnsolved Sudoku:\n";
    printBoard(board);

    if (solveSudoku(board)) {
        cout << "\nSolved Sudoku:\n";
        printBoard(board);
    } else {
        cout << "\nNo solution!\n";
    }

    // Keep window open
    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();
    return 0;
}