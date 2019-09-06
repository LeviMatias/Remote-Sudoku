#include "server_sudoku.h"

const char square_separator[LINE_LENGTH] = "U===========U===========U===========U\n";
const char common_separator[LINE_LENGTH] = "U---+---+---U---+---+---U---+---+---U\n";
const char number_line[LINE_LENGTH] = "U 0 | 0 | 0 U 0 | 0 | 0 U 0 | 0 | 0 U\n";

void _sudoku_make_printboard(sudoku_t* self){
	//for internal use
	for (int i = 0; i < 19; i++){
		if ( i % 2  == 1){ //odd
			memcpy(&(self->graphic_board[LINE_LENGTH*i]), &number_line[0], LINE_LENGTH);
		} else { // even
			if (i % 6 == 0){//its inside the square
				memcpy(&(self->graphic_board[LINE_LENGTH*i]), &square_separator[0], LINE_LENGTH);
			}else{
				memcpy(&(self->graphic_board[LINE_LENGTH*i]), &common_separator[0], LINE_LENGTH);
			}
		}
	}
}

void _sudoku_add_value_to_printboard(sudoku_t* self, char* value, int x, int y){
	//for internal use
	int pos = (1 + 2*(y - 1))*LINE_LENGTH + 2 + (x - 1)*4;
	memcpy(&(self->graphic_board[pos]), value, 1);
}

int _sudoku_line_check(char* start_pos, int multiplier){
	//for internal use, returns -1 if not ok, 0 if has 0
	//and 1 if full and ok
	int check[COLUMNS_AND_ROWS] = {0};
	int has_zero = COLUMNS_AND_ROWS;
	for (int  i=0; i < COLUMNS_AND_ROWS; i++){
		int pos = i * multiplier;
		int value = (start_pos[pos] - '0');
		if (value == 0){
			has_zero--;
		} else if (check[value - 1] != 0) {// value goes from 1-9!
			return -1;
		} else {
			check[value - 1] = 1;
		}
	}
	return (int)(has_zero/COLUMNS_AND_ROWS);
}

int _sudoku_square_check(char* square_start_pos){
	//for internal use, returns -1 if not ok, 0 if has 0
	// and 1 if full and ok
	int check[COLUMNS_AND_ROWS] = {0};
	int has_zero = COLUMNS_AND_ROWS;
	for (int  i=0; i < COLUMNS_AND_ROWS; i++){
		int pos = i%3 + ( (int)(i/3) ) * COLUMNS_AND_ROWS;
		int value = square_start_pos[pos] - '0';//convert from char to int
		if (value == 0){
			has_zero--;
		} else if (check[value - 1] != 0) {
			return -1;
		} else {
			check[value - 1] = 1;
		}
	}
	return (int)(has_zero/COLUMNS_AND_ROWS);
}

int sudoku_init(sudoku_t* self){
	FILE* fd = fopen("board.txt", "r");
	if (fd == NULL){
		//error!
		return -1;
	}
	_sudoku_make_printboard(self);

	char c = fgetc(fd);
	int x = 0;
	while (!feof(fd)){
		if (isdigit(c) != 0){
			int y = (int)(x/COLUMNS_AND_ROWS);
			int position = (x % COLUMNS_AND_ROWS) + COLUMNS_AND_ROWS * y;
			memcpy(&(self->start_board[position]), &c, 1);
			memcpy(&(self->current_board[position]), &c, 1);
			_sudoku_add_value_to_printboard(self, &c, (x % COLUMNS_AND_ROWS) + 1, y + 1);
			x++;
		}
		c = fgetc(fd);
	}
	fclose(fd);
	return 0;
}

sudoku_message_t* sudoku_print(sudoku_t* self, char* cmd){
	self->msg.text = self->graphic_board;
	self->msg.size = BOARD_PRINT_SIZE;
	return &(self->msg);
}

sudoku_message_t* sudoku_verify(sudoku_t* self, char* cmd){
	int verification = 0;
	for (int i=0; i < COLUMNS_AND_ROWS; i++){
		int pos = (i%3)*3 + ((int)(i/3))*9*3;
		int s1 = _sudoku_square_check(&(self->current_board[pos]));
		int s2 = _sudoku_line_check(&(self->current_board[i * COLUMNS_AND_ROWS]),1); //row
		int s3 = _sudoku_line_check(&(self->current_board[i]),COLUMNS_AND_ROWS); //column
		if (s1 < 0 || s2 < 0 || s3 < 0){
			verification = -1;
			printf("s1 %d , s2 %d s3 %d i %d \n", s1, s2 ,s3, i);
			break;
		} else {
			verification += s1 + s2 + s3;
		}
	}
	if (verification == (COLUMNS_AND_ROWS * 3)){
		//number of checks * times checked
		self->msg.text = WIN_MSG;
		self->msg.size = sizeof(WIN_MSG);
	} else if (verification == -1){
		self->msg.text = VERIFY_ERR;
		self->msg.size = sizeof(VERIFY_ERR);
	} else {
		self->msg.text = VERIFY_OK;
		self->msg.size = sizeof(VERIFY_OK);
	}
	return &(self->msg);
}

sudoku_message_t* sudoku_place_value(sudoku_t* self, char* cmd){
	char value = (cmd[3] + '0');//convert to number-char
	int x = cmd[1];
	int y = cmd[2];
	int position = (x - 1) + COLUMNS_AND_ROWS*(y - 1);
	printf("%d - %c - %d \n",cmd[1], self->start_board[position], cmd[2] );
	if (self->start_board[position] != '0'){ 
	//trying to place on unmodifiable cell
		self->msg.text = PUT_FAIL;
		self->msg.size = sizeof(PUT_FAIL);
		return &(self->msg);
	} else {
		memcpy(&(self->current_board[position]), &value, 1);
		_sudoku_add_value_to_printboard(self, &(self->current_board[position]), x, y);
		return sudoku_print(self, cmd);
	}
}

sudoku_message_t* sudoku_reset(sudoku_t* self, char* cmd){
	memcpy(&(self->current_board[0]), &(self->start_board[0]), COLUMNS_AND_ROWS*COLUMNS_AND_ROWS);
	for (int i=0; i < COLUMNS_AND_ROWS; i++){
		for (int j =0; j < COLUMNS_AND_ROWS; j++){
			_sudoku_add_value_to_printboard(self, &(self->start_board[i + COLUMNS_AND_ROWS*j]), i + 1, j + 1);
		}
	}
	return sudoku_print(self, cmd);
}

/*

38x19
U===========U===========U===========U\n
U X | X | X U X | X | X U X | X | X U\n
U---+---+---U---+---+---U---+---+---U\n
U X | X | X U X | X | X U X | X | X U\n
U---+---+---U---+---+---U---+---+---U\n
U X | X | X U X | X | X U X | X | X U\n
U===========U===========U===========U\n
U X | X | X U X | X | X U X | X | X U\n
U---+---+---U---+---+---U---+---+---U\n
U X | X | X U X | X | X U X | X | X U\n
U---+---+---U---+---+---U---+---+---U\n
U X | X | X U X | X | X U X | X | X U\n
U===========U===========U===========U\n
U X | X | X U X | X | X U X | X | X U\n
U---+---+---U---+---+---U---+---+---U\n
U X | X | X U X | X | X U X | X | X U\n
U---+---+---U---+---+---U---+---+---U\n
U X | X | X U X | X | X U X | X | X U\n
U===========U===========U===========U\n

*/