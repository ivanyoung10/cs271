/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 * 
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	
	char s_new[*s + 1];
	int i = 0;
	for (char *s2 = s; *s2; s2++) {
		if (*s2 == '/' && *(s2+1) == '/'){
			break;
		}
		else if (!(isspace(*s2))) {
			s_new[i++] = *s2;
		}
	}
	s_new[i] = '\0';
	strcpy(s, s_new);
    return s;	
}


/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	
	char line[MAX_LINE_LENGTH];
	char inst_type;
	
	while (fgets(line, sizeof(line), file)){
		strip(line);
		if (!(*line)){
			continue;
		}
		else {
			if (is_Atype(line)){
				inst_type = 'A';
			}
			else if (is_label(line) == true){
				inst_type = 'L';
			}
			else {
			inst_type = 'C';
			}
			printf("%c  %s\n", inst_type, line);
		}
	}
	
}

bool is_Atype(const char *line) {
	if (*line == '@') {
		return true;
	}
	else {
		return false;
	}
}

bool is_label(const char *ptr) {
	if (*ptr == '(') {
		return true;
	}
	else {
		return false;
	}
}