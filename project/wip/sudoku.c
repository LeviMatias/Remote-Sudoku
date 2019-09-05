
const char square_separator[LINE_LENGTH] = "U===========U===========U===========U\n";
const char common_separator[LINE_LENGTH] = "U---+---+---U---+---+---U---+---+---U\n";
const char number_line[LINE_LENGTH] = {"U 0 | 0 | 0 U 0 | 0 | 0 U 0 | 0 | 0 U\n"}

const void sudoku_make_printboard(sudoku_t* self){
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


sudoku_message_t* sudoku_place_value(sudoku_t* self, char* value, char* x, char* y){
	if (strcmp(self->start_board[x][y]) == 0){ //trying to place on unmodifiable cell
		self->msg.text = &PUT_FAIL;
		self->msg.size = sizeof(PUT_FAIL);
		return self->msg;
	} else {
		strncopy(self->current_board[x][y], value, 1);
		return sudoku_print_board(self);
	}
}

sudoku_message_t sudoku_print_board(sudoku_t* self){
	for (int i = 0; i < 19; i++){
		if ( i % 2  == 1){ //odd
			for (int j = 0; j < COLUMNS_AND_ROWS; j++){
				// we position the cursor at each number position and fill with the value in the matrix
				strncopy(self->graphic_board[LINE_LENGTH*i + 2 + 4*j], self->current_board[(i-1)/2][j], 1);
			}
		}
	}
	self->msg.text = self->graphic_board;
	self->msg.size = BOARD_PRINT_SIZE;
	return self->msg;
}

sudoku_message_t sudoku_reset(sudoku_t* self){
	char zeroes[COLUMNS_AND_ROWS] = "000000000"
	for (i=0; i< COLUMNS_AND_ROWS, i++){
		strncopy(self->current_board[x][y], zeroes, COLUMNS_AND_ROWS);
	}
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