/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] $Ivan Young$
 * [TERM] FALL $2024$
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"

int counter = 0;
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
	char label[MAX_LABEL_LENGTH];
	
	int i = 0;
	while (fgets(line, sizeof(line), file)){
		strip(line);
		if (!(*line)){
			continue;
		}
		else {
			if (is_Atype(line)){
				i++;
				//inst_type = 'A';
			}
			else if (is_label(line) == true){
				//inst_type = 'L';
				*label = *extract_label(line, label);
				symtable_insert(label, i);
				//printf("%c  %s\n", inst_type, label);
				continue;

			}
			else {
				i++;
			//inst_type = 'C';
			}
			//printf("%c  %s\n", inst_type, line);
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
	if (*ptr == '(' && ptr[strlen(ptr) - 1] == ')') {
		return true;
	}
	else {
		return false;
	}
}

char *extract_label(const char *line, char *label) {
	int i = 0;
	char line_new[*line + 1];
	for (const char *line2 = line; *line2; ++line2) {
		if (*line2 == '(') {
			continue;
			
		}
		else if (*line2 == ')') {
			continue;
		}
		else {
			line_new[i++] = *line2;
		}
	}
	line_new[i] = '\0';
	strcpy(label, line_new);
	return label;
}