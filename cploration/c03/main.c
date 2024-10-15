/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] Ivan Young
 * [TERM] FALL 2024
 * 
 ****************************************/
 
 # include <stdio.h>
 # include <string.h>
 # include <stdlib.h>

 #define MAX_LINE_LENGTH 200

int main(int argc, const char *argv[])
{	
	if (argc != 2) {
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else {
		FILE *fin = fopen(argv[1], "r");
		if (fin == NULL) {
			perror("Unable to open file!");
			exit(EXIT_FAILURE);
		}
		else {
			char out_file[] = "";
			strcpy(out_file, *argv);
			strcat(out_file, ".echo");
			FILE *fout = fopen(out_file, "w+");

			char line[MAX_LINE_LENGTH] = {0};
			unsigned int line_num = 0;
			while (fgets(line, sizeof(line), fin)) {
				line_num++;
				printf("[%04d] %s", line_num, line);
				fprintf(fout, "%s", line);
			}

			fclose(fin);
			fclose(fout);

		}
	}
}
