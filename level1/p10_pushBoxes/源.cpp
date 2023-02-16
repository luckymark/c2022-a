#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define MAP_WIDTH 5
#define MAP_HEIGHT 5

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position player_pos;
    Position box_pos[10];
    Position target_pos[10];
    int box_count;
    int target_count;
} GameState;

void InitGameState(GameState* state) {
    state->box_count = 0;
    state->target_count = 0;
}

void FindObjectPositions(char map[MAP_HEIGHT][MAP_WIDTH + 1], GameState* state) {
    int i, j;
    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            char c = map[i][j];
            switch (c) {
            case 'P':
                state->player_pos.x = j;
                state->player_pos.y = i;
                break;
            case '$':
                state->box_pos[state->box_count].x = j;
                state->box_pos[state->box_count].y = i;
                state->box_count++;
                break;
            case '.':
                state->target_pos[state->target_count].x = j;
                state->target_pos[state->target_count].
                    y = i;
                state->target_count++;
                break;
            }
        }
    }
}

void PrintMap(char map[MAP_HEIGHT][MAP_WIDTH + 1], GameState* state) {
    int i, j;
    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            char c = map[i][j];
            int k;
            for (k = 0; k < state->box_count; k++) {
                if (state->box_pos[k].x == j && state->box_pos[k].y == i) {
                    c = '$';
                    break;
                }
            }
            for (k = 0; k < state->target_count; k++) {
                if (state->target_pos[k].x == j && state->target_pos[k].y == i) {
                    c = '.';
                    break;
                }
            }
            if (state->player_pos.x == j && state->player_pos.y == i) {
                c = 'P';
            }
            printf("%c", c);
        }
        printf("\n");
    }
}

void MoveObject(Position* pos, int dx, int dy, GameState* state) {
    int new_x = pos->x + dx;
    int new_y = pos->y + dy; if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT) {
        return;
    }

    int i;
    for (i = 0; i < state->box_count; i++) {
        if (state->box_pos[i].x == new_x && state->box_pos[i].y == new_y) {
            MoveObject(&state->box_pos[i], dx, dy, state);
            break;
        }
    }
    if (i == state->box_count) {
        pos->x = new_x;
        pos->y = new_y;
    }
}

void MovePlayer(GameState* state, int dx, int dy) {
    MoveObject(&state->player_pos, dx, dy, state);
}

int CheckWin(GameState* state) {
    int i, j;
    for (i = 0; i < state->box_count; i++) {
        int box_on_target = 0;
        for (j = 0; j < state->target_count; j++) {
            if (state->box_pos[i].x == state->target_pos[j].x &&
                state->box_pos[i].y == state->target_pos[j].y) {
                box_on_target = 1;
                break;
            }
        }
        if (!box_on_target) {
            return 0;
        }
    }
    return 1;
}
void ControlMove(GameState* state) {
    int dx = 0, dy = 0;
    switch (getchar()) {
    case 'w': dy = -1; break; // up arrow
    case 's': dy = 1; break; // down arrow
    case 'a': dx = -1; break; // left arrow
    case 'd': dx = 1; break; // right arrow
    case 27: exit(0); // escape key to exit
    }
    MovePlayer(state, dx, dy);
}

int main() {
    char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
        "#####",
        "#.$.#",
        "#.$.#",
        "#P..#",
        "#####"
    };
    GameState state;
    InitGameState(&state);
    FindObjectPositions(map, &state);

    int move_count = 0;
    while (!CheckWin(&state)) {
        system("cls");
        printf("Push the boxes onto the targets. Use arrow keys to move.\n");
        printf("Moves: %d\n", move_count);
        PrintMap(map, &state);

        ControlMove(&state);
        move_count++;
    }
    printf("Congratulations, you won in %d moves!\n", move_count);

    return 0;
}