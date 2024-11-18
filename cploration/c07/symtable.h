/****************************************
 * C-ploration 7 for CS 271
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

//constants
#define SYMBOL_TABLE_SIZE 1000

//typedefs
typedef int16_t hack_addr;

//structs
typedef struct Symbol {
    char *name;
    hack_addr addr;
};

int hash(char *str);
struct Symbol *symtable_find(char *key);
void symtable_insert(char *key, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();

