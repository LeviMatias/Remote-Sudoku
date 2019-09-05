
const char square_separator[LINE_LENGTH] = "U===========U===========U===========U\n";
const char common_separator[LINE_LENGTH] = "U---+---+---U---+---+---U---+---+---U\n";
const char number_line[LINE_LENGTH] = {"U 0 | 0 | 0 U 0 | 0 | 0 U 0 | 0 | 0 U\n"}

const void _sudoku_make_printboard(sudoku_t* self){
	for (int i = 0; i < 19; i++){
		if ( i % 2  == 1){ //odd
			strncopy(self->graphic_board[LINE_LENGTH*i], &number_line[0], LINE_LENGTH);
		} else { // even
			if (i % 6 == 0){//its inside the square
				strncopy(self->graphic_board[LINE_LENGTH*i], &square_separator[0], LINE_LENGTH);
			}else{
				strncopy(self->graphic_board[LINE_LENGTH*i], &common_separator[0], LINE_LENGTH);
			}
		}
	}
}

const void _sudoku_add_value_to_printboard(sudoku_t* self, char* value, int x, int y){
	strncopy(self->graphic_board[(x - 1) * 4 + 2][y * 2], value, 1);
}

int sudoku_init_from_file(sudoku_t* self){
	FILE* fd = fopen("board.txt", 'r');
	if (fd == NULL){
		//error!
		return -1;
	}
	_sudoku_make_printboard(self);

	char c = fgetc(fd);
	int x = 0;
	while (!feof(fd)){
		if isdigit(c){
			strncopy(self->start_board[x % COLUMNS_AND_ROWS][(int)(x / COLUMNS_AND_ROWS)], &c, 1);
			strncopy(self->current_board[x % COLUMNS_AND_ROWS][(int)(x / COLUMNS_AND_ROWS)], &c, 1);
			_sudoku_add_value_to_printboard(self, &c, (x % COLUMNS_AND_ROWS]) + 1, (x / COLUMNS_AND_ROWS) + 1);
			x++;
		}
	}

	fclose(fd);
	return 0;
}

sudoku_message_t* sudoku_place_value(sudoku_t* self, char* value, int* x, int* y){
	if (strcmp(self->start_board[x][y]) == 0){ //trying to place on unmodifiable cell
		self->msg.text = &PUT_FAIL;
		self->msg.size = sizeof(PUT_FAIL);
		return self->msg;
	} else {
		strncopy(self->current_board[(*x - 1)][(*y - 1)], value, 1);
		_sudoku_add_value_to_printboard(self, self->start_board[i][j], *x, *y);
		return sudoku_print_board(self);
	}
}

sudoku_message_t sudoku_print_board(sudoku_t* self){
	self->msg.text = self->graphic_board;
	self->msg.size = BOARD_PRINT_SIZE;
	return self->msg;
}

sudoku_message_t sudoku_reset(sudoku_t* self){
	for (i=0; i < COLUMNS_AND_ROWS, i++){
		strncopy(self->current_board[i], self->start_board[i], COLUMNS_AND_ROWS);
		for (int j =0; j < COLUMNS_AND_ROWS; j++){
			_sudoku_add_value_to_printboard(self, self->start_board[i][j], i + 1, j + 1);
		}
	}
	return sudoku_print_board(self);
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