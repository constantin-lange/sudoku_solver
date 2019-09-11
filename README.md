# Sudoku Solver
This little C++ application can solve (3 x 3) sudoku's via backtracking.

## Build and Execute
1. *cd /build*
2. *cmake ..* (>= 3.10.2)
3. *make*
4. *./sudoku_solver*

## Configure Sudoku's
Open *test_sudoku.txt* and enter the custom sudoku as formatted in the file('X' represents unknown numbers). <br>
For exchanging the sudoku file go to line 75 in */src/main.cpp* and configure it there.