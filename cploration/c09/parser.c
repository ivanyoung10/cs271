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
	unsigned int instr_num = 0;
	unsigned int line_num = 0;
	
	add_predefined_symbols();
	while (fgets(line, sizeof(line), file)){
		line_num++;
		if (instr_num > MAX_INSTRUCTIONS) {
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
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
				strcpy(line, extract_label(line, label));
				if (!(isalpha(*label))){
					exit_program(EXIT_INVALID_LABEL, line_num, line);
				}
				if (symtable_find(label) != NULL){
					exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
				}
				symtable_insert(label, instr_num);
				continue;

			}
			else {
			inst_type = 'C';
			}
			printf("%u: %c  %s\n", instr_num, inst_type, line);
			instr_num++;
			
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


void add_predefined_symbols(){
	for (int i=0; i<23; i++){
		struct predefined_symbol symbols;
		symbols = predefined_symbols[i];
		symtable_insert(symbols.name, symbols.address);
	}
}

bool parse_A_instruction(const char *line, struct a_instruction *instr) {
	char * s;
	s = (char*) malloc(strlen(line));
	strcpy(s, line+1);
	char * (s_end) = NULL;
	long result = strtol(s, &s_end, 10);
	if (s == s_end){
		operand.label = (char*) malloc(strlen(line));
	}
}
