#ifndef __SUDOKU_H__
#define __SUDOKU_H__

//sudoku is played on a square board
#define COLUMNS_AND_ROWS 9
#define LINE_LENGTH 38
#define BOARD_PRINT_SIZE 722

typedef struct{
	int cells[COLUMNS_AND_ROWS][COLUMNS_AND_ROWS];
}board_t;

typedef struct{
	board_t start_board;
	board_t current_board;
}sudoku_t;

int sudoku_init_from_file(sudoku_t* self);

char* sudoku_verify(sudoku_t* self);

char* sudoku_place_value(sudoku_t* self);

//buffer must be big enough to hold the whole board (722 chars)
void sudoku_print(sudoku_t* self, char* buffer);

void sudoku_reset(sudoku_t* self);


#endif