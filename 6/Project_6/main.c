/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] $Ivan Young$
 * [TERM] FALL $2024$
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[])
{		
	int num_instructions;
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
			struct instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(struct instruction));

			num_instructions = parse(fin, instructions);
			parse(fin, instructions);
			fclose(fin);
			assemble(argv[1], instructions, num_instructions);
			free(instructions);
		}
	}
			
}


