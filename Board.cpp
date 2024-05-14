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
    for (int i = 0; i <= BOARD_SIZE - win; i++){
        int tmp = 0;
        for (int j = i; j <= BOARD_SIZE - win; j++){
            if (!isFieldEmpty(tmp, j)){
                int count = 1;
                int tmp_2 = j;
                int tmp_3 = tmp;
                char checkVal = BOARD_PIECE[tmp][j];
                ++tmp_3;
                ++tmp_2;
                while (tmp_3 < j+win){
                    if (BOARD_PIECE[tmp_3][tmp_2] != checkVal) break;
                    else {
                        tmp_3++;
                        tmp_2++;
                        count++;
                    }
                }
                if (count == win){
                    if (checkVal == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
            else tmp++;
        }
    }
        ///right cols
    for (int i = BOARD_SIZE-1; i >= win - 1; i--){
        int tmp = 0;
        for (int j = i; j >= win - 1; j--){
            if (!isFieldEmpty(tmp,j)){
                int count = 1;
                int tmp_2 = j;
                int limit = tmp+win;
                int tmp_3 = tmp;
                char checkVal = BOARD_PIECE[tmp][j];
                ++tmp_3;
                --tmp_2;
                while (tmp_3 < limit){
                    if (BOARD_PIECE[tmp_3][tmp_2] != checkVal) break;
                    else {
                        count++;
                        tmp_2--;
                        tmp_3++;
                    }
                }
                if (count == win){
                    if (checkVal == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
            else tmp++;
        }
    }
    for (int i = 1; i <= BOARD_SIZE - win; i++){
        int tmp = 0;///col
        for (int j = i; j <= BOARD_SIZE - win; j++){
            if (!isFieldEmpty(j, tmp)){
                int count = 1;
                int tmp_2 = j;
                int tmp_3 = tmp;
                int limit = tmp+win;
                char checkVal = BOARD_PIECE[j][tmp];
                ++tmp_3;
                ++tmp_2;
                while (tmp_3 < limit){
                    if (BOARD_PIECE[tmp_2][tmp_3] != checkVal) break;
                    else {
                        tmp_3++;
                        tmp_2++;
                        count++;
                    }
                }
                if (count == win){
                    if (checkVal == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
            else tmp++;
        }
    }
    for (int i = 1; i <= BOARD_SIZE - win; i++){
        int tmp = BOARD_SIZE-1;
        for (int j = i ; j <= BOARD_SIZE-win; j++){
            if (!isFieldEmpty(j, tmp)){
                int count = 1;
                int tmp_2 = j;
                int tmp_3 = tmp;
                int limit = tmp-win;
                char checkVal = BOARD_PIECE[j][tmp];
                tmp_2++;
                tmp_3--;
                while (tmp_3 > limit){
                    if (BOARD_PIECE[tmp_2][tmp_3] != checkVal) break;
                    else{
                        count++;
                        tmp_3--;
                        tmp_2++;
                    }
                }
                if (count == win){
                    if (checkVal == X_CELL) board_state = X_WON;
                    else board_state = O_WON;
                    return true;
                }
            }
            else tmp--;
        }
    }
    return false;
}
