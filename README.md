# Sudoku-puzzle-generator-and-solver
## This is a C++ application for generating Sudoku puzzles as well as solving them

Here,the 9-by-9 cell Sudoku grid is filled with numbers from 1 to 9 randomly. However, a number appears in a row or a column only once. Further, the 9-by-9 grid is sub divided in to nine 3-by-3 cell grids. A number appears only once within the 3-by-3 cell grid as well.

Firstlty,a Sudoku puzzle is generated with randomly distributed numbers.The number of missing numbers in a row or a column can be between 2 to 4.User can select how many cells are blank in a row or column at the beginning of the programme. Then the puzzle is generated. Once the user issues the command to solve the puzzle, algorithm will automatically fill the missing cells step by step,
and each step will be displayed, indicating the newly filled cell.If the algorithm performs a wrong allocation,it is indicated and the user can decide to start over the solving process or remove the wrong number and continue solving process from previous step.
