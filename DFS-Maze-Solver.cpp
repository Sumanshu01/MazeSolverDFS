#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Define directions for movement: Right, Down, Left, Up
const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// Function to check if a cell is within bounds and is valid for movement
bool isValidMove(int x, int y, const vector<vector<char>> &maze, vector<vector<bool>> &visited) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() &&
           maze[x][y] != '#' && !visited[x][y];
}

// Depth-First Search to solve the maze
bool solveMazeDFS(int x, int y, vector<vector<char>> &maze, vector<vector<bool>> &visited, vector<pair<int, int>> &path) {
    if (maze[x][y] == 'E') { // If we've reached the end
        path.push_back({x, y});
        return true;
    }

    visited[x][y] = true;
    path.push_back({x, y});

    // Explore all possible directions
    for (const auto &dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;

        if (isValidMove(newX, newY, maze, visited)) {
            if (solveMazeDFS(newX, newY, maze, visited, path)) {
                return true;
            }
        }
    }

    // Backtrack if no solution is found
    path.pop_back();
    return false;
}

int main() {
    int rows, cols;
    cout << "Enter the number of rows and columns in the maze: ";
    cin >> rows >> cols;

    vector<vector<char>> maze(rows, vector<char>(cols));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    pair<int, int> start, end;

    cout << "Enter the maze (use 'S' for start, 'E' for end, '.' for paths, and '#' for walls):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> maze[i][j];
            if (maze[i][j] == 'S') {
                start = {i, j};
            } else if (maze[i][j] == 'E') {
                end = {i, j};
            }
        }
    }

    vector<pair<int, int>> path;
    if (solveMazeDFS(start.first, start.second, maze, visited, path)) {
        cout << "Path found:\n";
        for (const auto &p : path) {
            cout << "(" << p.first << ", " << p.second << ") -> ";
        }
        cout << "End\n";

        // Mark the path on the maze
        for (const auto &p : path) {
            if (maze[p.first][p.second] != 'S' && maze[p.first][p.second] != 'E') {
                maze[p.first][p.second] = '*';
            }
        }

        cout << "Solved Maze:\n";
        for (const auto &row : maze) {
            for (char cell : row) {
                cout << cell << ' ';
            }
            cout << '\n';
        }
    } else {
        cout << "No path found from 'S' to 'E'.\n";
    }

    return 0;
}

