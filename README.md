# Knight's Tour Problem Solver

## What is the Knight's Tour?

The knight's tour is a chess problem that first appeared in around the ninth century. It consists of a knight starting at any square of the board and moving to the remaining 63 squares without ever jumping to the same square more than once (Source: https://www.chess.com/terms/knights-tour-chess).

## Steps to use:
1. Compile the C++ file
2. Run the executable with command line parameters for: board size (integer for number of chess squares in a row), start square, end square

Example compilation command on Mac/Linux:
```
g++ -std=c++17 knights-tour-solver.cpp -o knights-tour-solver
```


Example execution command on Mac/Linux:
```
./knights-tour-solver 8 a3 c4
```
