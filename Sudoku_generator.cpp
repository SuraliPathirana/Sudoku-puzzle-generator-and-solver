//date:06-09-2021
//author:Surali Pathirana

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int size = 9; //size of the grid
int startover = 0;	
int backtrackRequest = 0;

/*
function: checkRow
inputs: array-generated sudoku puzzle   i-row number
output->true-if num is present in the row
*/
bool checkRow(int array[][size], int i, int num)
{
    for (int j = 0; j < size; j++)
    {
        if (array[i][j] == num)
            return false;
    }
    return true;
}

/*
function:checkColumn
inputs: array-generated sudoku puzzle   j-column number
output->true-if num is present in the column
*/
bool checkColumn(int array[][size], int j, int num)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i][j] == num)
            return false;
    }
    return true;
}

/*
function:checkBox
inputs: array-generated sudoku puzzle   startRow/ startColumn-start position of the box
output->true-if num is present in the box
*/
bool checkBox(int array[][size], int startRow, int startColumn, int num)
{
    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startColumn; j < startColumn + 3; j++)
        {
            if (array[i][j] == num)
                return false;
        }
    }
    return true;
}

/*
function:printArray
inputs: array-generated sudoku puzzle
output-non
*/
void printArray(int array[][size])
{
    for (int i = 0; i < size; i++)
    {
        cout << " ";
        for (int j = 0; j < size; j++)
        {

            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
function:printArray2    print the intermediate steps with ' to indicate currrent position
inputs:array-generated sudoku puzzle   r-row c-column
output-non
*/
void printArray2(int array[][size], int r, int c)
{
    cout << " processing....." << endl;
    for (int i = 0; i < size; i++)
    {
        cout << " ";
        for (int j = 0; j < size; j++)
        {
            if (i == r && j == c)
            {
                cout << array[i][j] << "'";
            }
            else
                cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
function:isZero
inputs: array-generated sudoku puzzle   &row/ &column-reference to the row and column variables
output:non(modifies the row and column variable values to blank positions)
*/
bool isZero(int array[][size], int &row, int &column)
{
    for (row = 0; row < size; row++)
        for (column = 0; column < size; column++)
            if (array[row][column] == 0) //empty cell
                return true;
    return false;
}

/*
function:isValidPlace
inputs:array-generated sudoku puzzle    row/column-row and column variables num-value to be searched
output: true->can be filled with the value
*/
bool isValidPlace(int array[][size], int row, int column, int num)
{

    bool freeRow = checkRow(array, row, num);
    bool freeColumn = checkColumn(array, column, num);
    bool freeBox = checkBox(array, row - row % 3, column - column % 3, num);
    if (freeRow != true || freeColumn != true || freeBox != true)
    {
        return false;
    }
    else
        return true;
}
/*
function:sudokuSolver
inputs:array-generated sudoku puzzle    
output-recursively solves the puzzle    
*/
bool sudokuSolver(int array[][size])
{
    int row, column;
    if (!isZero(array, row, column))
        return true; //completely filled
    for (int num = 1; num <= size; num++)
    {
        if (isValidPlace(array, row, column, num))
        {
            array[row][column] = num; //fill in if valid
            if (startover != 1)
            {
                printArray2(array, row, column);
                cout << endl;
            }
            if (sudokuSolver(array)) //recursively go for other spaces
                return true;
            array[row][column] = 0; //turn back to 0 when conditions are not satisfied
            if (backtrackRequest == 0)
            {
                cout << " wrong allocation! 0-allow backtrack  1-startover with new puzzle :";
                cin >> startover;
                backtrackRequest = 1; //user is asked only 1 time.if allowed backtracking will automatically happen if when needed
            }
            if (startover == 0)
            {
                cout << " backtracking......" << endl
                     << endl;
            }
        }
    }
    return false;
}

/*
function:createRandomPuzzle
inputs:array    
output-non
*/
void createRandomPuzzle(int array[][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            array[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++) //first creating a correct sudoku puzzle from the pattern
    {
        int p = i / 3;
        int q = i % 3;
        int k = p + 3 * q;
        for (int j = 0; j < size; j++)
        {
            array[i][(k + j) % size] = j + 1;
        }
    }
    // randomizing  rows (interchanging possible rows)
    for (int i = 0; i <= 6; i = i + 3)
    {
        int rand1 = rand() % 3 + i;
        int rand2 = rand() % 3 + i;
        if (rand1 != rand2)
        {
            int temp;
            for (int j = 0; j < size; j++)
            {
                temp = array[rand1][j];
                array[rand1][j] = array[rand2][j];	//interchanging the 2 rows
                array[rand2][j] = temp;
            }
        }
    }
    // randomizing columns (interchanging possible columns)
    for (int i = 0; i <= 6; i = i + 3)
    {
        int rand1 = rand() % 3 + i;
        int rand2 = rand() % 3 + i;
        if (rand1 != rand2)
        {
            int temp;
            for (int i = 0; i < size; i++)
            {
                temp = array[i][rand1];
                array[i][rand1] = array[i][rand2];	//interchanging the 2 columns
                array[i][rand2] = temp;
            }
        }
    }
}

int main()
{
    //sudoku puzzle generator
    cout << "\n---------Sudoku puzzle generator---------" << endl;
    srand(time(NULL));
    int array[size][size];
    while (true)
    {
        createRandomPuzzle(array);
        int missingCells; //no of missing cells per row
        cout << "\n Number of missing values in a row? (2/3/4):";
        cin >> missingCells;
        if(missingCells<2 ||missingCells>4){
        	cout<<" Invalid Input";
        	return 0;
		}
        for (int i = 0; i < size; i++)
        {
            for (int count = 0; count < missingCells;)
            {
                int randomCell = rand() % size;
                if (array[i][randomCell] != 0)
                {
                    array[i][randomCell] = 0;
                    count++;
                }
            }
        }

        cout << endl
             << "-----generated sudoku puzzle-----" << endl;
        printArray(array);
        cout << "** '0' is used for empty spaces" << endl
             << endl;

        cout << "--------Sudoku puzzle solver--------" << endl
             << endl;

        cout << "**wrong allocation->backtracking.User is asked only 1 time to allow backtracking.\n";
		cout <<"  wrong allocations are backtracked automatically and indicated to the user\n" << endl;
        cout << "**current position is indicated using ' in each step" << endl;
        char userCommand;
        cout << "\npress 's' to start solving : ";
        cin >> userCommand;
        cout << endl;
        while (userCommand != 's')
        {
            cout << "enter 'e' to exit or 's' to start :";
            cin >> userCommand;
            if (userCommand == 'e')
            {
                return 0;
            }
        }

        if (sudokuSolver(array) == true && startover != 1)
        {
            cout << "------solved sudoku puzzle------" << endl;
            printArray(array);
            break;
        }

        else if (startover == 1)
        {

            cout << "\n starting over......" << endl //starting again from a new grid
                 << endl;
            startover = 0;
            backtrackRequest = 0;
        }
    }
    return 0;
}
