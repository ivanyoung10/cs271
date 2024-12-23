/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] $Ivan Young$
 * [TERM] FALL $2024$
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"

int main(int argc, const char *argv[])
{		

	if (argc != 2){
		//incorrect number of arguments
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
	}
	else {
		FILE *fin = fopen(argv[1], "r");
		if (fin == NULL) {
			exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
		}
		else {
			parse(fin);
			fclose(fin);
		}
	}
			
}


