/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] $Ivan Young$
 * [TERM] FALL $2024$
 * 
 ****************************************/

#ifndef __PARSER_H__
#define __PARSER_H__

//libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "hack.h"

// typedefs
typedef int16_t hack_addr;
typedef int16_t opcode;

// max constants
#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

// enums
enum instr_type {
    Invalid = -1,
    A = 0,
    C = 1,

};

//structs 

typedef struct c_instruction {
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;
};

typedef struct a_instruction {
    union {
        hack_addr address;
        char *label;
    };
    bool is_addr;
};

typedef struct instruction {
    union {
        struct a_instruction a;
        struct c_instruction c;
    };
    enum instr_type inst;
};

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char *);

bool is_label(const char *);

bool is_Ctype(const char *);

char *extract_label(const char *line, char* label);

void add_predefined_symbols();

bool parse_A_instruction(const char *line, struct a_instruction *instr);

#endif