#include "server_sudoku.h"

const char square_separator[] = "U===========U===========U===========U\n";
const char common_separator[] = "U---+---+---U---+---+---U---+---+---U\n";
const char number_line[] = "U 0 | 0 | 0 U 0 | 0 | 0 U 0 | 0 | 0 U\n";

void _sudoku_make_dboard(sudoku_t* self){
	//for internal use
	for (int i = 0; i < 19; i++){
		if (i % 2  == 1){ //odd
			memcpy(&(self->draw_board[LEN2*i]), &number_line[0], LEN2);
		} else { // even
			if (i % 6 == 0){//its inside the square
				memcpy(&(self->draw_board[LEN2*i]),\
						 &square_separator[0], LEN2);
			}else{
				memcpy(&(self->draw_board[LEN2*i]),\
						 &common_separator[0], LEN2);
			}
		}
	}
}

void _sudoku_add_value_to_dboard(sudoku_t* self, char* value, int x, int y){
	//for internal use
	int pos = (1 + 2*(y - 1))*LEN2 + 2 + (x - 1)*4;
	memcpy(&(self->draw_board[pos]), value, 1);
}

int _sudoku_line_check(char* start_pos, int multiplier){
	//for internal use, returns -1 if not ok, 0 if has 0
	//and 1 if full and ok
	int check[LEN] = {0};
	int has_zero = LEN;
	for (int  i=0; i < LEN; i++){
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
	return (int)(has_zero/LEN);
}

int _sudoku_square_check(char* square_start_pos){
	//for internal use, returns -1 if not ok, 0 if has 0
	// and 1 if full and ok
	int check[LEN] = {0};
	int has_zero = LEN;
	for (int  i=0; i < LEN; i++){
		int pos = i%3 + ( (int)(i/3) ) * LEN;
		int value = square_start_pos[pos] - '0';//convert from char to int
		if (value == 0){
			has_zero--;
		} else if (check[value - 1] != 0) {
			return -1;
		} else {
			check[value - 1] = 1;
		}
	}
	return (int)(has_zero/LEN);
}

int sudoku_init(sudoku_t* self){
	FILE* fd = fopen("board.txt", "r");
	if (fd == NULL){
		//error!
		return -1;
	}
	_sudoku_make_dboard(self);

	char c = fgetc(fd);
	int x = 0;
	while (!feof(fd)){
		if (isdigit(c) != 0){
			int y = (int)(x/LEN);
			int position = (x % LEN) + LEN * y;
			memcpy(&(self->ini_board[position]), &c, 1);
			memcpy(&(self->main_board[position]), &c, 1);
			_sudoku_add_value_to_dboard(self, &c, (x % LEN) + 1, y + 1);
			x++;
		}
		c = fgetc(fd);
	}
	fclose(fd);
	return 0;
}

sudoku_message_t* sudoku_print(sudoku_t* self, char* cmd){
	self->msg.text = self->draw_board;
	self->msg.size = BOARD_PRINT_SIZE;
	return &(self->msg);
}

sudoku_message_t* sudoku_verify(sudoku_t* self, char* cmd){
	int verification = 0;
	for (int i=0; i < LEN; i++){
		int pos = (i%3)*3 + ((int)(i/3))*9*3;
		int s1 = _sudoku_square_check(&(self->main_board[pos]));
		int s2 = _sudoku_line_check(&(self->main_board[i * LEN]),1); //row
		int s3 = _sudoku_line_check(&(self->main_board[i]),LEN); //column
		if (s1 < 0 || s2 < 0 || s3 < 0){
			verification = -1;
			break;
		} else {
			verification += s1 + s2 + s3;
		}
	}
	if (verification == (LEN * 3)){
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
	int position = (x - 1) + LEN*(y - 1);
	if (self->ini_board[position] != '0'){ 
	//trying to place on unmodifiable cell
		self->msg.text = PUT_FAIL;
		self->msg.size = sizeof(PUT_FAIL);
		return &(self->msg);
	} else {
		memcpy(&(self->main_board[position]), &value, 1);
		_sudoku_add_value_to_dboard(self, &(self->main_board[position]), x, y);
		return sudoku_print(self, cmd);
	}
}

sudoku_message_t* sudoku_reset(sudoku_t* self, char* cmd){
	memcpy(&(self->main_board[0]), &(self->ini_board[0]), LEN*LEN);
	for (int i=0; i < LEN; i++){
		for (int j =0; j < LEN; j++){
			_sudoku_add_value_to_dboard(self, &(self->ini_board[i + LEN*j]),\
										 i + 1, j + 1);
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
