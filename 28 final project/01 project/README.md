# Sudoku Solver
#### Video Demo:  https://youtu.be/ZXcVh9EaPik
#### Description:

## Project Overview

The Sudoku Solver project is a Python-based application that provides a graphical interface to solve Sudoku puzzles. It utilizes the Pygame library to create a graphical user interface (GUI) where users can interactively input Sudoku puzzles and watch as the solver algorithm finds a solution in real-time. This project aims to provide a visually appealing and user-friendly tool for solving Sudoku puzzles.

## Project Components

### main
This file contains the main logic for running the Pygame application. It initializes the game window, handles user interactions, and integrates the Sudoku solving algorithm.

### grid
The Grid class manages the Sudoku grid, including the creation of the puzzle board, updating the model, validating moves, solving the puzzle, and handling user inputs.

### square
The Square class represents each cell in the Sudoku grid. It manages the drawing of individual squares and handles the display of numbers, both as filled values and temporary sketches.

### solver_gui
Contains the backtracking algorithm implementation for solving Sudoku puzzles. The solve() and solve_gui() functions employ a backtracking approach to find the solution to the Sudoku puzzle.

## Design Choices

### Pygame for GUI:

Pygame was chosen for its simplicity in creating graphical interfaces and handling user interactions, providing an intuitive platform for users to interact with the Sudoku puzzle.

### Backtracking Algorithm:

The solver uses a backtracking algorithm due to its effectiveness in solving Sudoku puzzles. It systematically attempts different number combinations and backtracks when a conflict arises, ensuring a valid solution.

### Real-time Visualization:

The decision to update the GUI in real-time during the solving process was made to provide users with a visual representation of how the algorithm progresses towards solving the puzzle.

### UI Feedback:

Different colors and highlighting (such as green for correct moves by the Sudoku Doggy and red for selection) were employed to provide users with immediate feedback on the solving process.

## Conclusion

The Sudoku Solver project offers an interactive and visually engaging way to solve Sudoku puzzles. By leveraging Pygame for the graphical interface and implementing an efficient backtracking algorithm, users can input puzzles, watch the solver in action, and enjoy a satisfying solution to their Sudoku challenges.
