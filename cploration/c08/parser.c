#include "parser.h"
#include "symtable.h"

void parse(FILE * file) {
  char line[MAX_LINE_LENGTH] = {0};
  unsigned int line_num=0;
  unsigned int instr_num=0;
  while (fgets(line, sizeof(line), file)) {
    line_num++;
    if(instr_num>MAX_INSTRUCTIONS){
      exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
    }
    strip(line);
    if (!*line) continue;
    char inst_type = ' ';
    if(is_Atype(line)){
      inst_type='A';
    }
    if(is_label(line)){
      inst_type='L';
      char temp[strlen(line)-2];
      extract_label(line, temp);
      if(!isalpha(temp[0])){
        exit_program(EXIT_INVALID_LABEL, line_num, line);
      }
      if(symtable_find(temp)!=NULL){
        exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
      }
      symtable_insert(temp, instr_num);
      continue;
    }
    if(is_Ctype(line)){
      inst_type='C';
    }
    if(inst_type != ' '){
      printf("%c  %s \n",inst_type,line);
    }
    if(inst_type == ' ') {
      printf("%s \n", line);
    }
    instr_num++;
  }
}

char *strip(char *s){
  char s_new[strlen(s)+1];
  if (*s=='/' && *(s+1)=='/'){
    s_new[0]='\0';
    strcpy(s, s_new);
    return s;
  }
  int i=0;
  for (char *s2 = s; *s2; s2++) { 

    if (!isspace(*s2)){
      s_new[i++] = *s2;
    }
  s_new[i]='\0';
  }
  strcpy(s, s_new);
  return s;
}

bool is_Atype(const char *line){
  if(line[0]=='@'){
    return true;
  }
  return false;
}

bool is_label(const char *line){
  if(line[0] != '('){
    return false;
  }
  if(line[strlen(line)-2] != ')'){
    return false;
  }
  return true;
}

bool is_Ctype(const char *line){
  return !(is_Atype(line) || is_label(line));
}

char *extract_label(const char *line, char* label){
  int i;
  for(i = 0; i<strlen(line)-3; i++){
    label[i]=line[i+1];
  }
  label[i]='\0';
  return label;
}