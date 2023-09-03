#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAZE_WIDTH 10
#define MAZE_HEIGHT 10

int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

typedef struct Player {
    int x;
    int y;
} Player;

Player player;

void init_game() {
    // Initialize player's position.
    player.x = 1;
    player.y = 1;
}

void update_game_state() {
    // Get user input.
    char input = getchar();

    // Update player's position based on user input.
    if (input == 'w') {
        int new_y = player.y - 1;
        if (maze[new_y][player.x] != 1) {
            player.y = new_y;
        }
    }
    else if (input == 'a') {
        int new_x = player.x - 1;
        if (maze[player.y][new_x] != 1) {
            player.x = new_x;
        }
    }
    else if (input == 's') {
        int new_y = player.y + 1;
        if (maze[new_y][player.x] != 1) {
            player.y = new_y;
        }
    }
    else if (input == 'd') {
        int new_x = player.x + 1;
        if (maze[player.y][new_x] != 1) {
            player.x = new_x;
        }
    }

    // Check if player reaches the exit.
    if (maze[player.y][player.x] == 2) {
        printf("You win!\n");
        exit(0);
    }
}

void draw_game() {
    // Clear the screen.
    system("cls");

    // Draw maze.
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            if (maze[y][x] == 1) {
                // Wall.
                printf("%c", '#');
            }
            else if (maze[y][x] == 2) {
                // Exit.
                printf("%c", 'E');
            }
            else if (player.x == x && player.y == y) {
                // Player.
                printf("%c", 'P');
            }
            else {
                // Path.
                printf("%c", ' ');
            }
        }
        printf("\n");
    }
}

int main() {
    // Initialize the game.
    init_game();// Enter the main game loop.
    while (1) {
        // Update the game state.
        update_game_state();

        // Draw the game scene.
        draw_game();

        // Sleep for a short amount of time.
        Sleep(100);
    }

    return 0;
}

