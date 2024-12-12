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
int parse(FILE * file, struct instruction *instructions){
	
	struct instruction instr;
	char line[MAX_LINE_LENGTH];
	char inst_type;
	unsigned int instr_num = 0;
	unsigned int line_num = 0;
	char tmp_line[MAX_LINE_LENGTH];
	
	
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
				if (!parse_A_instruction(line, &instr.a)){
					exit_program(EXIT_INVALID_A_INSTR, line_num, line);
				}
				instr.inst = A;
				if(instr.a.is_addr) {
					printf("A: %d\n", instr.a.address);
				}
				else {
					printf("A: %s\n", instr.a.label);
				}

			}
			else if (is_label(line)){
				char label[MAX_LABEL_LENGTH] = {0};
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
			else if (is_Ctype(line)) {
				inst_type = 'C';
				instr.inst = C;
				strcpy(tmp_line, line);
				parse_C_instruction(tmp_line, &instr.c);

				if (instr.c.dest == -1) {
					exit_program(EXIT_INVALID_C_DEST, line_num, line);
				}
				if (instr.c.comp == -1) {
					exit_program(EXIT_INVALID_C_COMP, line_num, line);
				}
				if (instr.c.jump == -1) {
					exit_program(EXIT_INVALID_C_JUMP, line_num, line);
				}

				instr.inst = C;
				printf("C: d=%d, c=%d, j=%d\n", instr.c.dest, instr.c.comp, instr.c.jump);
			}
			else {
				inst_type = ' ';
			}
			instructions[instr_num++] = instr;
		}
	}
	return instr_num;
}

bool is_Atype(const char *line) {
	if (*line == '@') {
		return true;
	}
	else {
		return false;
	}
}

bool is_Ctype(const char *line) {
	if (!(is_Atype(line)) && !(is_label(line))) {
        return true;
    }
    return false;
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
	s = (char *) malloc(strlen(line));
	strcpy(s, line+1);
	char * (s_end) = NULL;
	long result = strtol(s, &s_end, 10);
	if (s == s_end){
		instr->label = (char*) malloc(strlen(line));
		strcpy(instr->label, s);
		instr->is_addr = false;
	}
	else if (*s_end != 0) {
		return false;
	}
	else {
		instr->address = result;
		instr->is_addr = true;

	}
	return true;
}

void parse_C_instruction(char *line, struct c_instruction *instr) {
	char dest_del[2] = "=";
	char jump_del[2] = ";";
	int a = 0;
	char *temp_value = NULL;
	char *comp = NULL;
	char *jump = NULL;
	char *dest = NULL;

	temp_value = strtok(line, jump_del);
	jump = strtok(NULL, "");

	dest = strtok(temp_value, dest_del);
	comp = strtok(NULL, "");

	if (comp == NULL){
		comp = dest;
		dest = NULL;
	}

	instr->comp = str_to_compid(comp, &a);
	instr->dest = str_to_destid(dest);
	instr->jump = str_to_jumpid(jump);
	instr-> a= 1 ? a : 0;
}

void assemble(const char * file_name, struct instruction* instructions, int num_instructions){
	char * ext;
	int i = 0;
	ext = strcat(file_name, ".hack");
	FILE * fin = fopen(ext, "r");

	while (i != num_instructions){

	}
}

opcode instruction_to_opcode(struct c_instruction instr) {
	opcode op = 0;
	op |= (7 << 13);

	op |= (instr.a << 12);
	op |= (instr.comp << 6);
	op |= (instr.dest << 3);
	op |= (instr.jump << 0);

	return op;
}
