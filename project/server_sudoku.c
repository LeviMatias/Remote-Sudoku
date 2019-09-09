#include "server_sudoku.h"

const char square_separator[] = "U===========U===========U===========U\n";
const char common_separator[] = "U---+---+---U---+---+---U---+---+---U\n";
const char number_line[] = "U   |   |   U   |   |   U   |   |   U\n";

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

void _sudoku_add_value_to_dboard(sudoku_t* self, uint8_t* value, int x, int y){
	//for internal use
	char v = *value + '0';//to char
	if (v == '0'){
		v = ' ';
	}
	int pos = (1 + 2*(x - 1))*LEN2 + 2 + (y - 1)*4;
	memcpy(&(self->draw_board[pos]), &v, sizeof(char));
}

int _sudoku_line_check(uint8_t* start_pos, int multiplier){
	//for internal use, returns -1 if not ok, 0 if has 0
	//and 1 if full and ok
	int check[LEN] = {0};
	int has_zero = LEN;
	for (int  i=0; i < LEN; i++){
		int pos = i * multiplier;
		int value = start_pos[pos];
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

int _sudoku_square_check(uint8_t* square_start_pos){
	//for internal use, returns -1 if not ok, 0 if has 0
	// and 1 if full and ok
	int check[LEN] = {0};
	int has_zero = LEN;
	for (int  i=0; i < LEN; i++){
		int pos = i%3 + ( (int)(i/3) ) * LEN;
		int value = square_start_pos[pos];
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

common_message_t* _sudoku_print_msg(sudoku_t* self, char* print, size_t size){
	//for internal use
	memcpy(self->msg->text, print, size);
	self->msg->size = size;
	return (self->msg);
}

int sudoku_init(sudoku_t* self, common_message_t *msg){
	FILE* fd = fopen("board.txt", "r");
	if (fd == NULL){
		//error!
		return -1;
	}
	_sudoku_make_dboard(self);

	int num = 0;
	int r = fscanf(fd, "%d", &num);
	int y = 0; //to position on board
	while (!feof(fd) && r != -1){
		if (r > 0){
			if (num > LEN || num < 1){
				num = 0;//out of bounds set it blank
			}
			int x = (int)(y/LEN);
			int position = (y % LEN) + LEN * x;
			memcpy(&(self->ini_board[position]), &num, 1);
			memcpy(&(self->main_board[position]), &num, 1);
			_sudoku_add_value_to_dboard(self, (uint8_t*)&num, x+1, (y%LEN)+1);
			y++;
		}
		r = fscanf(fd, "%d", &num);
	}
	fclose(fd);
	self->msg = msg;
	return 0;
}

common_message_t* sudoku_print_board(sudoku_t* self, char* cmd){
	return _sudoku_print_msg(self, self->draw_board, BOARD_PRINT_SIZE);
}

common_message_t* sudoku_verify(sudoku_t* self, char* cmd){
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

	if (verification == -1){
		return _sudoku_print_msg(self, VERIFY_ERR, sizeof(VERIFY_ERR));
	} else {
		return _sudoku_print_msg(self, VERIFY_OK, sizeof(VERIFY_OK));
	}
}

common_message_t* sudoku_place_value(sudoku_t* self, char* cmd){
	uint8_t value = cmd[2];//rename
	int x = cmd[0];
	int y = cmd[1];
	int position = (y - 1) + LEN*(x - 1);
	if (self->ini_board[position] != 0){ 
	//trying to place on unmodifiable cell
		return _sudoku_print_msg(self, PUT_FAIL, sizeof(PUT_FAIL));
	} else {
		memcpy(&(self->main_board[position]), &value, 1);
		_sudoku_add_value_to_dboard(self, &(self->main_board[position]), x, y);
		return sudoku_print_board(self, cmd);
	}
}

common_message_t* sudoku_reset(sudoku_t* self, char* cmd){
	memcpy(&(self->main_board[0]), &(self->ini_board[0]), LEN*LEN);
	for (int i=0; i < LEN; i++){
		for (int j =0; j < LEN; j++){
			_sudoku_add_value_to_dboard(self, &(self->ini_board[j + LEN*i]),\
										 i + 1, j + 1);
		}
	}
	return sudoku_print_board(self, cmd);
}

