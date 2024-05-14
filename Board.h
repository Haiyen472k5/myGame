#ifndef __BOARD__
#define __BOARD__
#define BOARD_SIZE 20
#define CELL_SIZE 30
#define X_BOARD 0
#define Y_BOARD 0
#define win 5
#define EMPTY_CELL ' '
#define X_CELL 'x'
#define O_CELL 'o'
#define X_WON 0
#define O_WON 1
#define TIE 2
#include <iostream>

struct Board{
    char BOARD_PIECE[BOARD_SIZE][BOARD_SIZE];
    int occupied;
    int board_state;
    char next_move;
    Board();

    void board_reset();
    void move(int rows, int cols);
    bool gameOver();
    bool isDraw();
    bool checkRows();
    bool checkCols();
    bool checkDiags();
    bool isFieldEmpty(int rows, int cols);
    bool isFieldX(int rows, int cols);
    bool isFieldO(int rows, int cols);
};

#endif // __BOARD__
