// Created by Vadim on 15.05.2024.

#ifndef LAB_WORK_19_GAME_LIFE_H
#define LAB_WORK_19_GAME_LIFE_H

#include <stdio.h>
#include <stdlib.h>

int c = 4;
int r = 3;

int count_Live_neighbors(int board[c][r], int row, int col) {
    int count = 0;
    int i, j;

    for (i = row - 1; i <= row + 1; i++) {
        for (j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < c && j >= 0 && j < r && !(i == row && j == col)) {
                count += board[i][j];
            }
        }
    }

    return count;
}

void game_life(int board[c][r]) {
    int nextBoard[c][r];
    int i, j;

    for (i = 0; i < c; i++) {
        for (j = 0; j < r; j++) {
            int liveNeighbors = count_Live_neighbors(board, i, j);

            if (board[i][j] == 1) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    nextBoard[i][j] = 0;
                } else {
                    nextBoard[i][j] = 1;
                }
            } else {
                if (liveNeighbors == 3) {
                    nextBoard[i][j] = 1;
                } else {
                    nextBoard[i][j] = 0;
                }
            }
        }
    }

    for (i = 0; i < c; i++) {
        for (j = 0; j < r; j++) {
            board[i][j] = nextBoard[i][j];
        }
    }
}

void test_game_life() {
    int board[4][3] = {{0, 1, 0},
                       {0, 0, 1},
                       {1, 1, 1},
                       {0, 0, 0}};

    game_life(board);

    int check[4][3] = {{0, 0, 0},
                       {1, 0, 1},
                       {0, 1, 1},
                       {0, 1, 0}};

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            if (board[i][j] != check[i][j]) {
                printf("Matrices are different\n");
                break;
            }
        }
    }
}

#endif //LAB_WORK_19_GAME_LIFE_H
