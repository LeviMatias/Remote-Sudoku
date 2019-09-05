#ifndef __SUDOKU_H__
#define __SUDOKU_H__
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//sudoku is played on a square board
#define COLUMNS_AND_ROWS 9
#define LINE_LENGTH 38
#define BOARD_PRINT_SIZE 722

#define WIN_MSG "You win"
#define VERIFY_OK "OK"
#define VERIFY_ERR "ERROR"
#define PUT_FAIL "Cell is not modifiable"

typedef struct{
	char* text;
	size_t size;
}sudoku_message_t;


typedef struct{
	char start_board[COLUMNS_AND_ROWS][COLUMNS_AND_ROWS];
	char current_board[COLUMNS_AND_ROWS][COLUMNS_AND_ROWS];
	char graphic_board[BOARD_PRINT_SIZE]; 
	sudoku_message_t msg;
}sudoku_t;

//attemps to read a file and create the sudoku board from it
//uses by default the filepath "board.txt" and assumes the files is well constructed
//POS returns 0 if successful, -1 if not
int sudoku_init_from_file(sudoku_t* self);

//verifies that every value is placed correctly
//POS returns a pointer to the sudoku msg with the return text
//message returns "OK" if all values are correctly placed, "Error" if not
sudoku_message_t* sudoku_verify(sudoku_t* self);

//Attemps to position value in x:y, it also checks for win condition
//POS returns a pointer to the sudoku msg with the return text
sudoku_message_t* sudoku_place_value(sudoku_t* self, char* value, int x, int y);

//POS returns a pointer to the sudoku msg with the return text
sudoku_message_t* sudoku_print(sudoku_t* self);

//resets the sudoku board
//POS returns a pointer to the sudoku msg with the return text
sudoku_message_t* sudoku_reset(sudoku_t* self);


#endif