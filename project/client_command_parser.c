#include "client_command_parser.h"
const char PUT_STRUCTURE[][4] = {"put\0","X\0","in\0","X\0","X\0"};

void _cmd_order_buffer(char* buffer){
	int aux = buffer[1];
	buffer[ROW_IS_IN] = buffer[2];
	buffer[COLUMN_IS_IN] = buffer[3]; 
	buffer[VALUE_IS_IN] = aux;
}

int cmd_exit(char* buffer, size_t* buffer_size,\
			char* cmd_code, char* input){
	return EXIT_CODE;
}

int cmd_parse_single(char* buffer, size_t* buffer_size,\
					char* cmd_code,char* input){
	buffer[0] = toupper(*cmd_code);
	*buffer_size = 1;
	return 0;
}

int cmd_parse_coordinates(char *buffer, size_t *buffer_size,\
							 char* cmd_code, char *input){
	int s = cmd_parse_single(buffer, buffer_size, cmd_code, input);
	int i = 1;
	char* saveptr = NULL;
	char* cmd = strtok_r(input, DELIM_WORDS, &saveptr);
	while (cmd != NULL && (strcmp(PUT_STRUCTURE[i],"X\0") == 0 \
						|| strcmp(cmd,PUT_STRUCTURE[i]) == 0)){ 
		if (strcmp(PUT_STRUCTURE[i],"X\0") == 0){
			char* mixed_text;
			long int numl = strtol(cmd, &mixed_text ,10);
			if (mixed_text == cmd || *mixed_text != '\0'){
				return -1;
			} else if (numl > UPPER_BOUND || numl < LOWER_BOUND){
				if (*buffer_size > 2){ //this means we already got the value
					fprintf(stderr,\
					 "Error en los índices. Rango soportado: [1,9]\n");
				} else {
					fprintf(stderr,\
					 "Error en el valor ingresado. Rango soportado: [1,9]\n");
				}
				return -1;
			} else {
				uint8_t num = numl;
				buffer[*buffer_size] = num;
				(*buffer_size)++;
			}
		} else if (strcmp(cmd,PUT_STRUCTURE[i]) != 0){
			return - 1;
		}
		cmd = strtok_r(NULL, DELIM_WORDS, &saveptr);
		i++;
	}
	if (*buffer_size != PUT_LENGTH){
		return -1;
	}
	_cmd_order_buffer(buffer);
	return s;
}
