/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] $Ivan Young$
 * [TERM] FALL $2024$
 * 
 ****************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>


#define NUM_PREDEFINED_SYMBOLS 23

//enums
enum symbol_id {
    SYM_SP = 0,
    SYM_LCL = 1,
    SYM_ARG = 2,
    SYM_THIS = 3,
    SYM_THAT = 4,
    SYM_R0 = 0,
    SYM_R1 = 1, 
    SYM_R2 = 2, 
    SYM_R3 = 3,
    SYM_R4 = 4,
    SYM_R5 = 5,
    SYM_R6 = 6,
    SYM_R7 = 7,
    SYM_R8 = 8,
    SYM_R9 = 9,
    SYM_R10 = 10,
    SYM_R11 = 11,
    SYM_R12 = 12,
    SYM_R13 = 13,
    SYM_R14 = 14,
    SYM_R15 = 15,
    SYM_SCREEN = 16384,
    SYM_KBD = 24576
};

typedef enum {
    JMP_INVALID = -1,
    JMP_NULL = 0,
    JMP_JGT = 1,
    JMP_JEQ = 2,
    JMP_JGE = 3,
    JMP_JLT = 4,
    JMP_JNE = 5,
    JMP_JLE = 6,
    JMP_JMP = 7,

} jump_id;

typedef enum {
    DEST_INVALID = -1,
    DEST_NULL = 0,
    DEST_M = 1,
    DEST_D = 2,
    DEST_MD = 3,
    DEST_A = 4,
    DEST_AM = 5,
    DEST_AD = 6,
    DEST_AMD = 7,

} dest_id;

typedef enum {
    COMP_INVALID = -1,
    COMP_0 = 42,
    COMP_1 = 63,
    COMP_2 = 58,
    COMP_3 = 12,
    COMP_4 = 48,
    COMP_5 = 13,
    COMP_6 = 49,
    COMP_7 = 15,
    COMP_8 = 51,
    COMP_9 = 31,
    COMP_10 = 55,
    COMP_11 = 14,
    COMP_12 = 50,
    COMP_13 = 2,
    COMP_14 = 19,
    COMP_15 = 7,
    COMP_16 = 0,
    COMP_17 = 21,
    COMP_18 = 48, 
    COMP_19 = 49, 
    COMP_20 = 51,
    COMP_21 = 55,
    COMP_22 = 50,
    COMP_23 = 2,
    COMP_24 = 19,
    COMP_25 = 7,
    COMP_26 = 0, 
    COMP_27 = 21,


} comp_id;

//structs

typedef struct predefined_symbol {
    char name[20];
    int16_t address;
} predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"R0", SYM_R0}, 
    {"R1", SYM_R1}, 
    {"R2", SYM_R2},
    {"R3", SYM_R3},
    {"R4", SYM_R4},
    {"R5", SYM_R5},
    {"R6", SYM_R6},
    {"R7", SYM_R7},
    {"R8", SYM_R8},
    {"R9", SYM_R9},
    {"R10", SYM_R10},
    {"R11", SYM_R11},
    {"R12", SYM_R12},
    {"R13", SYM_R13},
    {"R14", SYM_R14},
    {"R15", SYM_R15},
    {"SP", SYM_SP},
    {"LCL", SYM_LCL},
    {"ARG", SYM_ARG},
    {"THIS", SYM_THIS},
    {"THAT", SYM_THAT},
    {"SCREEN", SYM_SCREEN},
    {"KBD", SYM_KBD}

};

//functions

static inline jump_id str_to_jumpid(const char *s) {
    jump_id id = JMP_INVALID;
    if (s == NULL) {
        id = JMP_NULL;
    } else if (strcmp(s, "JGT") == 0) {
        id = JMP_JGT;
    } else if (strcmp(s, "JEQ") == 0) {
        id = JMP_JEQ;
    } else if (strcmp(s, "JGE") == 0) {
        id = JMP_JGE;
    }  else if (strcmp(s, "JLT") == 0) {
        id = JMP_JLT;
    }  else if (strcmp(s, "JNE") == 0) {
        id = JMP_JNE;
    }  else if (strcmp(s, "JLE") == 0) {
        id = JMP_JLE;
    }  else if (strcmp(s, "JMP") == 0) {
        id = JMP_JMP;
    }
    return id;
}

static inline dest_id str_to_destid(const char *s) {
    dest_id id = DEST_INVALID;
    if (s == NULL) {
        id = DEST_NULL;
    } else if (strcmp(s, "M") == 0) {
        id = DEST_M;
    } else if (strcmp(s, "D") == 0) {
        id = DEST_D;
    } else if (strcmp(s, "MD") == 0) {
        id = DEST_MD;
    } else if (strcmp(s, "A") == 0) {
        id = DEST_A;
    } else if (strcmp(s, "AM") == 0) {
        id = DEST_AM;
    } else if (strcmp(s, "AD") == 0) {
        id = DEST_AD;
    } else if (strcmp(s, "AMD") == 0 ) {
        id = DEST_AMD;
    }
    return id;
}

static inline comp_id str_to_compid(const char *s, int *a) {
    comp_id id = COMP_INVALID;
    if (!strcmp(s, "0")) {
        *a = 0;
        id = COMP_0;
    } else if (!strcmp(s, "1")) {
        *a = 0;
        id = COMP_1;
    } else if (!strcmp(s, "-1")) {
        *a = 0;
        id = COMP_2;
    } else if (!strcmp(s, "D")) {
        *a = 0;
        id = COMP_3;
    } else if (!strcmp(s, "A")) {
        *a = 0;
        id = COMP_4;
    } else if (!strcmp(s, "!D")) {
        *a = 0;
        id = COMP_5;
    } else if (!strcmp(s, "!A")) {
        *a = 0;
        id = COMP_6;
    } else if (!strcmp(s, "-D")) {
        *a = 0;
        id = COMP_7;
    } else if (!strcmp(s, "-A")) {
        *a = 0;
        id = COMP_8;
    } else if (!strcmp(s, "D+1")) {
        *a = 0;
        id = COMP_9;
    } else if (!strcmp(s, "A+1")) {
        *a = 0;
        id = COMP_10;
    } else if (!strcmp(s, "D-1")) {
        *a = 0;
        id = COMP_11;
    } else if (!strcmp(s, "A-1")) {
        *a = 0;
        id = COMP_12;
    } else if (!strcmp(s, "D+A")) {
        *a = 0;
        id = COMP_13;
    } else if (!strcmp(s, "D-A")) {
        *a = 0;
        id = COMP_14;
    } else if (!strcmp(s, "A-D")) {
        *a = 0;
        id = COMP_15;
    } else if (!strcmp(s, "D&A")) {
        *a = 0;
        id = COMP_16;
    } else if (!strcmp(s, "D|A")) {
        *a = 0;
        id = COMP_17;
    } else if (!strcmp(s, "M")) {
        *a = 1;
        id = COMP_18;
    } else if (!strcmp(s, "!M")) {
        *a = 1;
        id = COMP_19;
    } else if (!strcmp(s, "-M")) {
        *a = 1;
        id = COMP_20;
    } else if (!strcmp(s, "M+1")) {
        *a = 1;
        id = COMP_21;
    } else if (!strcmp(s, "M-1")) {
        *a = 1;
        id = COMP_22;
    } else if (!strcmp(s, "D+M")) {
        *a = 1;
        id = COMP_23;
    } else if (!strcmp(s, "D-M")) {
        *a = 1;
        id = COMP_24;
    } else if (!strcmp(s, "M-D")) {
        *a = 1;
        id = COMP_25;
    } else if (!strcmp(s, "D&M")) {
        *a = 1;
        id = COMP_26;
    } else if (!strcmp(s, "D|M")) {
        *a = 1;
        id = COMP_27;
    }
    // maybe return a?
    return id;
}

