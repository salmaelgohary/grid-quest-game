#include <iostream>
#include <cstring>

using namespace std;

// Grid size (constants in uppercase)
const int ROWS = 5;
const int COLS = 5;

// Function declarations
void display_grid(char grid[ROWS][COLS]);
bool move_player(char grid[ROWS][COLS], int& player_row, int& player_col, char direction);
bool check_goal(char grid[ROWS][COLS], int& goal_row, int& goal_col);

// Main function
int main() {
    // Create a 5x5 grid and initialize it with empty spaces
    char grid[ROWS][COLS] = {
        { 'P', '.', '.', '.', '.' },
        { '0', '.', '.', 'O', '.' },
        { '.', '.', '.', 'O', '.' },
        { '.', 'O', '.', '.', '.' },
        { '.', '.', '.', 'O', '.' } 
    };
    int goal_row, goal_col;
    // Player's initial position
    int player_row = 0;
    int player_col = 0;
    grid[player_row][player_col] = 'P';  // Player starts at top-left corner

    // Game loop
    char direction;
    bool reached_goal = false;

    cout << "Welcome to the Grid Game!" << endl;

    display_grid(grid);

    bool chosen_goal = false;

    while (chosen_goal == false){
        cout << "Choose the coordinates of the goal: from (0-4)" << endl;

        cout << "Row: ";
        cin >> goal_row;

        cout << "Column: ";
        cin >> goal_col;

        check_goal(grid, goal_row, goal_col);

        if (check_goal(grid, goal_row, goal_col)){
            chosen_goal = true; //will automatically exit the while loop
        }

        else{
            cout << "Invalid choice! Try again" << endl;
        }
    }
        
    cout << endl << "Move using W (up), A (left), S (down), D (right), Q (North-West), E (North-East), C (South-East), Z (South-West). Reach the goal (G)." << endl;

    while (!reached_goal) {
        // Display the current grid
        display_grid(grid);

        // Get the player's move
        cout << "Enter direction (W/A/S/D/Q/E/Z/C): ";
        cin >> direction;

        // Move the player
        if (move_player(grid, player_row, player_col, direction)) {
            // Check if the player has reached the goal
            if (grid[goal_row][goal_col] == 'P') {
                display_grid(grid);
                reached_goal = true;
                cout << "Congratulations! You've reached the goal!" << endl;
                return 0;
            }
        } else {
            cout << "Invalid move. Try again!" << endl;
        }
    }

    return 0;
}

//Function to choose location of goal
bool check_goal(char grid[ROWS][COLS], int& goal_row, int& goal_col){
    //check if inputted row & column are within array range
    if (goal_row < 0 || goal_row > ROWS || goal_row < 0 || goal_row > COLS){
        return false;
    }

    //check if inputted row & column have an O
    if (grid[goal_row][goal_col] == 'O'){
        return false;
    }

    //check if they inputted starting position
    if (grid[goal_row][goal_col] == 'P'){
        return false;
    }

    grid[goal_row][goal_col] = 'G';

    return true;
    }


// Function to display the grid
void display_grid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to move the player
bool move_player(char grid[ROWS][COLS], int& player_row, int& player_col, char direction) {
    // Calculate the new position based on the direction
    int new_row = player_row;
    int new_col = player_col;

    switch (toupper(direction)) { //directly changes input to capital letter
        case 'W': new_row--; break;  // Up
        case 'A': new_col--; break;  // Left
        case 'S': new_row++; break;  // Down
        case 'D': new_col++; break;  // Right
        case 'E': new_col++, new_row--; break;  //northeast
        case 'Q': new_col--, new_row--; break;  //northwest
        case 'C': new_col++, new_row++; break;  //southeast
        case 'Z': new_col--, new_row++; break;  //southwest
        default: return false;  // Invalid direction
    }

    // Check if the new position is out of bounds
    if (new_row < 0 || new_row >= ROWS || new_col < 0 || new_col >= COLS) {
        return false;
    }

    // Check if the new position is an obstacle
    if (grid[new_row][new_col] == 'O') {
        return false;
    }

    // Move the player to the new position
    grid[player_row][player_col] = '.';  // Clear the old position
    player_row = new_row;
    player_col = new_col;
    grid[player_row][player_col] = 'P';  // Place the player at the new position

    return true;
}
