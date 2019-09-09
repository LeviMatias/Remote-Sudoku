#ifndef __SUDOKU_H__
#define __SUDOKU_H__
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include "common_message.h"

//sudoku is played on a square board
#define LEN 9 //common board line length
#define LEN2 38 //draw_board line length
#define BOARD_PRINT_SIZE 722

#define WIN_MSG "You win\n"
#define VERIFY_OK "OK\n"
#define VERIFY_ERR "ERROR\n"
#define PUT_FAIL "La celda indicada no es modificable\n"

typedef struct{
	uint8_t ini_board[LEN * LEN];
	uint8_t main_board[LEN * LEN];
	char draw_board[BOARD_PRINT_SIZE]; 
	common_message_t *msg;
}sudoku_t;

//the cmd parameter holds the information needed to execute the command
//its used to standarize the arguments and easily map the functions and

//attemps to read a file and create the sudoku board from it
//by default the filepath "board.txt"
//*msg is a pointer to the message the sudoku is going to use
// to write down its output messages
//POS returns 0 if successful, -1 if not
int sudoku_init(sudoku_t* self, common_message_t *msg);

//verifies that every value is placed correctly
//POS returns a pointer to the sudoku msg with the return text
//message returns "OK" if all values are correctly placed, "Error" if not
common_message_t* sudoku_verify(sudoku_t* self, char* cmd);

//Attemps to position value in x:y
//POS returns a pointer to the sudoku msg with the return text
common_message_t* sudoku_place_value(sudoku_t* self, char* cmd);

//POS returns a pointer to the sudoku msg with the return text
common_message_t* sudoku_print_board(sudoku_t* self, char* cmd);

//resets the sudoku board
//POS returns a pointer to the sudoku msg with the return text
common_message_t* sudoku_reset(sudoku_t* self, char* cmd);


#endif
