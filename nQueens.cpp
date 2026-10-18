#include "nQueens.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
using namespace std;

// precondition: n is a positive integer representing the size of the chessboard
// postcondition: Initializes the nQueens object with a chessboard of size n x n and sets the number of existing queens to 0
nQueens::nQueens(int n)
{
	//create 2D array
	numberOfExistingQueens = 0;
	size = n;
	board = new char* [n];
	for (int i = 0; i < n; i++)
	{
		board[i] = new char[n];
	}

	//fill it with empty signs (based on prof Q's executable it is '-')
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			board[i][j] = '-';
		}
	}
}

// precondition: None
// postcondition: Returns the size of the chessboard (n)
int nQueens::getSize() const
{
	return size;
}

// precondition: None
// postcondition: Displays the current state of the chessboard with Unicode characters for better visualization
void nQueens::display() const
{
	cout << "\n\t" << char(201) << string((size * 2 - 1), char(205)) << char(187);
	for (int i = 0; i < size; i++)
	{
		cout << "\n\t" << char(186);
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j];

			if (j < size - 1)
			{
				cout << char(179);
			}
		}
		cout << char(186);
	}
	cout << "\n\t" << char(200) << string((size * 2 - 1), char(205)) << char(188) << "\n";
}

// precondition: row and col are valid indices for the chessboard
// postcondition: Checks if placing a queen at the specified position (row, col) would result in a conflict with existing queens on the board
int nQueens::isConflict(int row, int col) const
{
	//check directly that position
	if (board[row][col] == 'Q')
	{
		return 1;
	}
	//check row
	for (int i = 0; i < size; i++)
	{
		if (board[row][i] == 'Q')
		{
			return 2;
		}
	}
	//check column
	for (int i = 0; i < size; i++)
	{
		if (board[i][col] == 'Q')
		{
			return 3;
		}
	}
	//check diagonal (4 directions to check)
	//these 2 variables are for increment and decrement (stepping thru the array to check)
	int r = 0;
	int c = 0;
	//upper-left
	r = row - 1;
	c = col - 1;
	while (r >= 0 && c >= 0)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}
		r--;
		c--;
	}

	//upper-right
	r = row - 1;
	c = col + 1;

	while (r >= 0 && c < size)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}

		r--;
		c++;
	}

	//lower-left
	r = row + 1;
	c = col - 1;

	while (r < size && c >= 0)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}

		r++;
		c--;
	}

	//lower-right
	r = row + 1;
	c = col + 1;

	while (r < size && c < size)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}

		r++;
		c++;
	}

	return 0;
}

// precondition: row and col are valid indices for the chessboard
// postcondition: Places a queen at the specified position (row, col) if there is no conflict with existing queens on the board; returns 0 if successful, or a conflict type code if there is a conflict
int nQueens::placeQueen(int row, int col)
{
	int conflictType = isConflict(row - 1, col - 1);
	if (conflictType != 0)
	{
		return conflictType;
	}
	else
	{
		numberOfExistingQueens++;
		board[row - 1][col - 1] = 'Q';
		return 0;
	}
}

// precondition: row and col are valid indices for the chessboard
// postcondition: Removes a queen from the specified position (row, col) if there is a queen present; returns true if successful, or false if there was no queen at that position
bool nQueens::removeQueen(int row, int col)
{
	if (board[row - 1][col - 1] == 'Q')
	{
		numberOfExistingQueens--;
		board[row - 1][col - 1] = '-';
		return true;
	}
	else
	{
		return false;
	}
}

// precondition: None
// postcondition: Returns true if the number of existing queens on the board is equal to the size of the chessboard (indicating that the n-Queens problem is solved), or false otherwise
bool nQueens::solved() const
{
	if (numberOfExistingQueens == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// precondition: firstColumn is a valid column index (1-based) for the chessboard
// postcondition: Attempts to solve the n-Queens problem by placing queens on the chessboard starting from the specified first column; 
// returns true if a solution is found, or false if no solution exists
bool nQueens::solve(int firstColumn)
{
	if (size < 1 || firstColumn < 1 || firstColumn > size)
	{
		return false;
	}

	// Clear the board.
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			board[row][col] = '-';
		}
	}

	numberOfExistingQueens = 0;

	while (!queens.empty())
	{
		queens.pop();
	}

	// No solutions exist for 2 or 3 queens.
	if (size == 2 || size == 3)
	{
		return false;
	}

	// Special case for one queen.
	if (size == 1)
	{
		board[0][0] = 'Q';
		numberOfExistingQueens = 1;
		queens.push(0);
		return true;
	}

	const int MAX_ATTEMPTS = 500; // Maximum number of attempts to find a solution.
	const int MAX_STEPS = 20000; // Maximum number of steps to improve a solution.

	vector<int> positions(size); // positions[row] = column of the queen in that row

	vector<int> usedColumns(size, 0);
	vector<int> usedDiagonal1(2 * size - 1, 0);
	vector<int> usedDiagonal2(2 * size - 1, 0);

	int start = firstColumn - 1; // Convert to 0-based index.

	// Try different starting arrangements.
	for (int attempt = 0; attempt < MAX_ATTEMPTS; attempt++)
	{
		// Keep the first queen fixed.
		positions[0] = start;

		// Initialize the remaining queens.
		for (int row = 1; row < size; row++)
		{
			positions[row] =
				(start + row * 2 + attempt) % size;
		}

		// Improve the arrangement.
		for (int step = 0; step < MAX_STEPS; step++)
		{
			// Reset conflict counters.
			fill(usedColumns.begin(), usedColumns.end(), 0);
			fill(usedDiagonal1.begin(), usedDiagonal1.end(), 0);
			fill(usedDiagonal2.begin(), usedDiagonal2.end(), 0);

			// Count occupied columns and diagonals.
			for (int row = 0; row < size; row++)
			{
				int col = positions[row];

				usedColumns[col]++;
				usedDiagonal1[row - col + size - 1]++;
				usedDiagonal2[row + col]++;
			}

			int conflictRow = -1;
			int mostConflicts = 0;

			// Find the queen with the most conflicts.
			// Row 0 is fixed, so begin at row 1.
			for (int row = 1; row < size; row++)
			{
				int col = positions[row];
				int diagonal1 = usedDiagonal1[row - col + size - 1] - 1;
				int diagonal2 = usedDiagonal2[row + col] - 1;
				int conflicts = usedColumns[col] - 1 + diagonal1 + diagonal2; // Count conflicts for this queen.
				// If this queen has more conflicts than the previous most, remember it.
				if (conflicts > mostConflicts)
				{
					mostConflicts = conflicts;
					conflictRow = row;
				}
			}
			int diagonal1 = usedDiagonal1[size - 1 - start] - 1;
			int diagonal2 = usedDiagonal2[start] - 1;
			// Check the first queen.
			int firstConflicts = usedColumns[start] - 1 + diagonal1 + diagonal2;
			// Check whether all queens are safe.
			if (mostConflicts == 0 && firstConflicts == 0)
			{
				// Place the completed solution.
				for (int row = 0; row < size; row++)
				{
					int col = positions[row];
					board[row][col] = 'Q';
					numberOfExistingQueens++;
					queens.push(col);
				}

				return solved();
			}

			// Choose a row to adjust.
			if (conflictRow == -1)
			{
				conflictRow = 1 + (step % (size - 1));
			}

			int oldCol = positions[conflictRow];

			// Temporarily remove this queen from the counters.
			usedColumns[oldCol]--;
			usedDiagonal1[conflictRow - oldCol + size - 1]--;
			usedDiagonal2[conflictRow + oldCol]--;

			int bestCol = oldCol;
			int fewestConflicts = size * 3 + 1;

			// Try every column and choose the safest.
			for (int offset = 0; offset < size; offset++)
			{
				int col = (offset + step + attempt) % size;
				// Calculate diagonal indices.
				int diagonalIndex1 = conflictRow - col + size - 1;
				int diagonalIndex2 = conflictRow + col;
				// Count conflicts.
				int conflicts = usedColumns[col] + usedDiagonal1[diagonalIndex1] + usedDiagonal2[diagonalIndex2];
				// Select the column with the fewest conflicts.
				if (conflicts < fewestConflicts)
				{
					fewestConflicts = conflicts;
					bestCol = col;
				}
			}

			// Move the selected queen.
			positions[conflictRow] = bestCol;
		}
	}

	// The search limit was reached.
	return false;
}


// precondition: None
// postcondition: Deallocates the memory used for the chessboard by deleting the dynamically allocated 2D array
nQueens::~nQueens() 
{
	for (int i = 0; i < size; i++)
	{
		delete[] board[i]; //delete the small array inside big array
	}
	delete[] board; //delete the big board at last
}



