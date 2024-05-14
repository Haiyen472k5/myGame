#include "Board.h"
Board::Board(){
    board_reset();
}

void Board::board_reset(){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            BOARD_PIECE[i][j] = EMPTY_CELL;
        }
    }
    occupied = 0;
    board_state = TIE;
    next_move = X_CELL;
}

void Board::move(int rows, int cols){
    if (rows >= 0 && rows < BOARD_SIZE && cols >= 0 && cols < BOARD_SIZE){
        BOARD_PIECE[rows][cols] = next_move;
        next_move = (next_move == X_CELL ? O_CELL : X_CELL);
        ++occupied;
    }
}

bool Board:: gameOver(){
    return (checkCols() || checkRows() || checkDiags() || isDraw());
}

bool Board::isDraw(){
    board_state = TIE;
    return (occupied == BOARD_SIZE*BOARD_SIZE);
}

bool Board::isFieldEmpty(int rows, int cols){
    if (rows >= 0 && rows < BOARD_SIZE && cols >= 0 && cols < BOARD_SIZE)
        return (BOARD_PIECE[rows][cols] == EMPTY_CELL);
    return false;
}

bool Board::isFieldO(int rows, int cols){
    if (rows >= 0 && rows < BOARD_SIZE && cols >= 0 && cols < BOARD_SIZE)
        return (BOARD_PIECE[rows][cols] == O_CELL);
    return false;
}

bool Board::isFieldX(int rows, int cols){
    if (rows >= 0 && rows < BOARD_SIZE && cols >= 0 && cols < BOARD_SIZE)
        return (BOARD_PIECE[rows][cols] == X_CELL);
    return false;
}

bool Board::checkRows(){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j <= BOARD_SIZE-win; j++){
            if(!isFieldEmpty(i,j)){
                int count = 1;
                for (int k = j+1; k < j+win; k++){
                    if (BOARD_PIECE[i][j] != BOARD_PIECE[i][k]) break;
                    else count++;
                }
                if (count == win){
                    if (BOARD_PIECE[i][j] == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::checkCols(){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j <= BOARD_SIZE-win; j++){
            if (!isFieldEmpty(j,i)){
                int count = 1;
                for (int k = j+1; k < j+win; k++){
                    if (BOARD_PIECE[j][i] != BOARD_PIECE[k][i]) break;
                    else count++;
                }
                if (count == win){
                    if (BOARD_PIECE[j][i] == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::checkDiags(){
    for (int cols = 0; cols <= BOARD_SIZE-win; cols++){
        int tmp = cols;
        for (int rows = 0; rows <= BOARD_SIZE-win; rows++){
            if (!isFieldEmpty(rows, tmp)){
                char checkVal = BOARD_PIECE[rows][tmp];
                int new_row = rows+1;
                int new_cols = tmp+1;
                int count = 1;
                while (count < win && new_row < BOARD_SIZE && new_cols < BOARD_SIZE){
                    if (BOARD_PIECE[new_row][new_cols] != checkVal) break;
                    else{
                        count++;
                        new_row++;
                        new_cols++;
                    }
                }

                if (count == win){
                    if (checkVal == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
            tmp++;
        }
    }

    for (int col = BOARD_SIZE-1; col >= win-1; col--){
        int tmp = col;
        for (int row = 0; row <= BOARD_SIZE-win; row++){
            if (!isFieldEmpty(row, tmp)){
                char checkVal = BOARD_PIECE[row][tmp];
                int new_row = row+1;
                int new_col = tmp-1;
                int count = 1;
                while (count < win && new_row < BOARD_SIZE && new_col >= 0){
                    if (BOARD_PIECE[new_row][new_col] != checkVal) break;
                    else{
                        count++;
                        new_row++;
                        new_col--;
                    }
                }
                if (count == win){
                    if (checkVal == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
            tmp--;
        }
    }

    for (int row = 1; row <= BOARD_SIZE - win; row++){
        int tmp = row;
        for (int col = 0; col <= BOARD_SIZE-win; col++){
            if (!isFieldEmpty(tmp, col)){
                char checkVal = BOARD_PIECE[tmp][col];
                int count = 1;
                int new_row = tmp+1;
                int new_col = col+1;
                while (count < win && new_row < BOARD_SIZE && new_col < BOARD_SIZE){
                    if (BOARD_PIECE[new_row][new_col] != checkVal) break;
                    else{
                        count++;
                        new_row++;
                        new_col++;
                    }
                }
                if (win == count){
                    if (checkVal == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
            tmp++;
        }
    }

    for (int row = 1; row <= BOARD_SIZE-win; row++){
        int tmp = row;
        for (int col = BOARD_SIZE-1; col >= win-1; col--){
            if (!isFieldEmpty(tmp, col)){
                char checkVal = BOARD_PIECE[tmp][col];
                int count = 1;
                int new_row = row+1;
                int new_col = col-1;
                while (count < win && new_row < BOARD_SIZE && new_col >= 0){
                    if (BOARD_PIECE[new_row][new_col] != checkVal) break;
                    else {
                        count++;
                        new_row++;
                        new_col--;
                    }
                }
                if (win == count){
                    if (checkVal == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
            tmp++;
        }
    }
    return false;
}


