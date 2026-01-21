# 15-Puzzle Game
Classic 15-puzzle game (also known as "Fifteen") implemented using **C++** and **Qt Framework**.

## About
The **15-puzzle** is a sliding puzzle that consists of a 4x4 grid of numbered square tiles in random order with one tile missing. The objective of the puzzle is to place the tiles in numerical order (from 1 to 15) use the empty space.

This project demonstrates:
- GUI development with **Qt**.
- Game logic implementation in **C++**.
- Event handling and grid-based movement algorithms.

## Features
- **Classic Gameplay**: 4x4 grid with numbers 1 through 15 or a picture divided into pieces.
- **Registration mechanism**: Enter ID - "VIP" and password - "666" to access the new images.
- **Win Detection**: Automatically detects when the puzzle is solved and displays a victory picture.
- **Responsive UI**: Clean and simple interface designed with Qt.

## Installation

### Prerequisites
- **Qt Creator** (latest version recommended)
- **Qt 5.x or 6.x**
- **C++ Compiler** (MSVC, MinGW, or GCC)

### Building
- **Clone the repository**:
    ```bash
    git clone https://github.com/Kliooo/15-Puzzle-Game.git
    ```
- Open the project directory `15-Puzzle-Game`.
- Run `build.bat` to compile the project.

## Running

- Locate the `build_ninja` folder in each subproject.
- Run the respective executable files (`15_Puzzle_Game_Images.exe`).

## How to Play
- Click the **"Login"**  and come up with your ID and password (enter Enter ID - "VIP" and password - "666" to access the exclusive content)
- Select the desired level.
- The goal is to arrange the tiles in the following order:
    ```
    1   2   3   4
    5   6   7   8
    9  10  11  12
    13 14  15  [ ]
    ```
