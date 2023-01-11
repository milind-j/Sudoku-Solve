#include <bits/stdc++.h>
using namespace std;
#define n 9
bool isSafeRow(int grid[n][n], int row, int num)
{
    // This function will check whether it is safe to place the number in given row
    for (int i = 0; i < n; i++)
    {
        if (grid[row][i] == num)
        {
            return false;
        }
    }
    return true;
}
bool isSafeColumn(int grid[n][n], int col, int num)
{
    // This function will check whether it is safe to place a number in the given column
    for (int i = 0; i < n; i++)
    {
        if (grid[i][col] == num)
        {
            return false;
        }
    }
    return true;
}
bool isSafeGrid(int grid[n][n], int row, int col, int num)
{
    // This function will check whether it is safe to place the number in the given grid 3X3
    int rowfactor = row - (row % 3);
    int colfactor = col - (col % 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + rowfactor][j + colfactor] == num)
            {
                return false;
            }
        }
    }
    return true;
}
bool isSafe(int grid[n][n], int row, int col, int num)
{
    // This function will check whether it is safe for placing the number at the given row and column in sudoku matrix
    // Check for is safe in row && in column && in grid
    if (isSafeRow(grid, row, num) && isSafeColumn(grid, col, num) && isSafeGrid(grid, row, col, num))
    {
        return true;
    }
    return false;
}
bool findEmptyLocation(int grid[n][n], int &row, int &col)
{
    // This function will check whether there is any empty position in the matrix
    // This will also update row and column as it is passed by reference here
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 0)
            {
                row = i;
                col = j;
                // cout << row << col << endl;
                return true;
            }
        }
    }
    return false;
}
bool solveSudoku(int grid[n][n])
{
    int row, col;
    if (findEmptyLocation(grid, row, col) != true)
    {
        return true;
        // This means that if there is no empty location left in the matrix then the problem is solved
    }
    // By end of this findEmptyLocation function we have row and column of first empty location
    for (int i = 1; i <= n; i++)
    {
        // Here we will check whether we can insert value 1 to 9 at this empty position or not
        if (isSafe(grid, row, col, i) == true)
        {
            // If function returns true then we will insert the value in the place and move further
            grid[row][col] = i;
            // Now we will check for further position in matrix
            if (solveSudoku(grid))
            {
                return true;
            }
            // If the function returns false it means we need to backtrack and check for other values
            grid[row][col] = 0;
            // So we are reseting the value
        }
    }
    // If there is no possible number to solve the sudoku at this point then return false
    return false;
}
int main()
{
    int grid[n][n];
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
        {
            grid[i][j] = s[j] - '0';
        }
    }
    bool ans = solveSudoku(grid);
    // cout << ans;
    if (ans)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}