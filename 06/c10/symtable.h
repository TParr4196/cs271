#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

#define SYMBOL_TABLE_SIZE 100

typedef int16_t hack_addr;
struct Symbol {
  char* name;
  hack_addr addr;
} Symbol;
struct Symbol* hashArray[SYMBOL_TABLE_SIZE];
int hash(char *str);
struct Symbol *symtable_find(char * key);
void symtable_insert(char* key, hack_addr addr);
void display_table();

#endif