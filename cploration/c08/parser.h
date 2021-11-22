#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH-2
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;
char *strip(char *s);
void parse(FILE * file);
bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
char *extract_label(const char *line, char* label);
typedef enum instr_type {
  Invalid=-1,
  Atype,
  Ctype,
} instr_type;
typedef struct c_instruction {
  opcode a:1;
  opcode comp:6;
  hack_addr dest:3;
  opcode jump:3;
} c_instruction;
typedef struct a_instruction {
  union value {
    hack_addr address;
    char* label;
  } value;
  bool is_addr:1;
} a_instruction;
typedef struct instruction{
  union instr {
    a_instruction a;
    c_instruction c;
  } instr;
  instr_type type;
} instruction;

#endif