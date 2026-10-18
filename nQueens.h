#pragma once

#include <stack>
using namespace std;

class nQueens
{
private:
	short size; // Size of the chessboard (n x n).
	char** board; // 2D array representing the chessboard.
	int numberOfExistingQueens; // Count of queens currently placed on the board.

    stack<int> queens; // Stores queen columns for backtracking.

public:
	nQueens(int n); // Constructor to initialize the chessboard of size n x n.
	~nQueens(); // Destructor to deallocate the chessboard memory.

	int getSize() const; // Returns the size of the chessboard (n).
	void display() const; // Displays the current state of the chessboard.

    int placeQueen(int row, int column); 
    bool removeQueen(int row, int column);
    int isConflict(int row, int col) const;
    bool solved() const;

	bool solve(int firstColumn); // Attempts to solve the n-Queens problem starting from the specified first column.

    // Prevent copying because the class owns dynamic memory.
    nQueens(const nQueens&) = delete;
    nQueens& operator=(const nQueens&) = delete;
};