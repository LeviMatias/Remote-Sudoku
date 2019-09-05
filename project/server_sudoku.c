#include "server_sudoku.h"

const char square_separator[LINE_LENGTH] = "U===========U===========U===========U\n";
const char common_separator[LINE_LENGTH] = "U---+---+---U---+---+---U---+---+---U\n";
const char number_line[LINE_LENGTH] = "U 0 | 0 | 0 U 0 | 0 | 0 U 0 | 0 | 0 U\n";

void _sudoku_make_printboard(sudoku_t* self){
	for (int i = 0; i < 19; i++){
		if ( i % 2  == 1){ //odd
			strncpy(&(self->graphic_board[LINE_LENGTH*i]), &number_line[0], LINE_LENGTH);
		} else { // even
			if (i % 6 == 0){//its inside the square
				strncpy(&(self->graphic_board[LINE_LENGTH*i]), &square_separator[0], LINE_LENGTH);
			}else{
				strncpy(&(self->graphic_board[LINE_LENGTH*i]), &common_separator[0], LINE_LENGTH);
			}
		}
	}
}

void _sudoku_add_value_to_printboard(sudoku_t* self, char* value, int x, int y){
	strncpy((&(self->graphic_board[y*LINE_LENGTH]) + 2 + (x - 1)*4), value, 1);
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
			strncpy(&(self->start_board[x % COLUMNS_AND_ROWS][(int)(x / COLUMNS_AND_ROWS)]), &c, 1);
			strncpy(&(self->current_board[x % COLUMNS_AND_ROWS][(int)(x / COLUMNS_AND_ROWS)]), &c, 1);
			_sudoku_add_value_to_printboard(self, &c, (x % COLUMNS_AND_ROWS) + 1, (int)(x / COLUMNS_AND_ROWS) + 1);
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

sudoku_message_t* sudoku_place_value(sudoku_t* self, char* cmd){
	char* value = (&cmd[3]);
	int x =(cmd[1]);
	int y = (cmd[2]);
	if (strcmp(&(self->start_board[x][y]), "0") != 0){ //trying to place on unmodifiable cell
		self->msg.text = &(PUT_FAIL[0]);
		self->msg.size = sizeof(PUT_FAIL);
		return &(self->msg);
	} else {
		strncpy(&(self->current_board[(x - 1)][(y - 1)]), value, 1);
		_sudoku_add_value_to_printboard(self, &(self->current_board[(x - 1)][(y - 1)]), x, y);
		return sudoku_print(self, cmd);
	}
}

sudoku_message_t* sudoku_reset(sudoku_t* self, char* cmd){
	for (int i=0; i < COLUMNS_AND_ROWS; i++){
		strncpy(self->current_board[i], self->start_board[i], COLUMNS_AND_ROWS);
		for (int j =0; j < COLUMNS_AND_ROWS; j++){
			_sudoku_add_value_to_printboard(self, &(self->start_board[i][j]), i + 1, j + 1);
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