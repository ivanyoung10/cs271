/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $Ivan Young$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[]){
	if (argc == 2){
		 FILE *fin = fopen(argv[1], "r");
		if (fin != NULL){
			parse(fin);
		}
		else{
			perror("Unable to open file!");
			exit(EXIT_FAILURE);
		}
		fclose(fin);
	}
	else{
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	}
}	

	


