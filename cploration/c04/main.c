/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 * 
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[])
{		

	if (argv[] == 1){
		FILE *fin = fopen( argv[1], "r")
		if (*fin == NULL){
			perror("Unable to open file!");
			exit(EXIT_FAILURE);
		}
		else {
			fin* = parse()
			fclose(fin*)
		}
	}

	else{
		printf("Usage: %s [filename]"\n, argv[0]);
		exit(EXIT_FAILURE);
	}	
}


