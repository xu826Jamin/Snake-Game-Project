# Snake Game Project

## Overview
This project implements a classic **Snake Game** in C++. It solves the problem of creating an interactive, real-time console application using object-oriented design principles. This project matters because it demonstrates fundamental concepts of game development, including the game loop architecture, state management, and dynamic memory handling without relying on heavy game engines.

## Features
- **Classic Gameplay**: Navigate a snake to eat food, grow in length, and increase your score.
- **Dynamic Growth**: The snake's body grows dynamically as food is consumed, managed by a custom data structure.
- **Score Tracking**: Real-time score updates displayed on the screen.
- **Cross-Platform Support**: Utilizes `MacUILib` to abstract terminal input/output, allowing the game to run on both Windows and POSIX systems (Mac/Linux).
- **Collision Detection**: Handles logic for collecting food and preventing invalid moves (like reversing direction instantly).

## Tech Stack
- **Language**: C++ (Standard 98/11 compatible)
- **Build Tool**: GNU Make (`makefile`)
- **Libraries**: 
  - `MacUILib`: A custom library for handling console I/O (wraps `conio.h`/`windows.h` on Windows and standard POSIX calls on Mac/Linux).
  - Standard C++ Libraries (`iostream`, `cstdlib`, `time.h`).

## Design Decisions
**Tradeoff: Custom `objPosArrayList` vs. `std::vector`**
- **Decision**: I chose to implement a custom `objPosArrayList` class to manage the snake's body segments instead of using the standard library's `std::vector`.
- **Why**: This decision was made to explicitly handle memory management and deep copying logic. While `std::vector` is more robust, building a custom list provided finer control over how `objPos` objects are stored and allowed for a deeper understanding of dynamic array resizing and memory deallocation in C++.

## How to Run
1. **Build the Project**:
   Open your terminal and run the make command to compile the source code.
   ```bash
   make
   ```

2. **Run the Game**:
   Execute the generated binary.
   - On Windows:
     ```powershell
     ./Project.exe
     ```
   - On Mac/Linux:
     ```bash
     ./Project
     ```

3. **Controls**:
   - Use **WASD** keys to control the snake's direction.
   - Press the designated exit key (usually defined in the game logic, e.g., `ESC` or `SPACE`) to quit.

## What I Learned
- **Game Loop Architecture**: Understanding the cycle of *Input -> Logic -> Draw* and how to manage timing to create smooth gameplay.
- **Dynamic Memory Management**: Gained concrete skills in allocating and deallocating memory on the heap, specifically for the snake's body segments, to prevent memory leaks.
- **Modular Design**: Learned how to separate concerns by splitting the game into distinct classes (`GameMechs`, `Player`, `ScreenDrawer`), making the codebase easier to maintain and extend.
- **Finite State Machines**: Implemented basic state logic for player movement and game states (playing, game over).
