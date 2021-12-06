#include "parser.h"
#include "symtable.h"

void parse(FILE * file) {
  instruction instr;
  char line[MAX_LINE_LENGTH] = {0};
  unsigned int line_num=0;
  unsigned int instr_num=0;
  add_predefined_symbols();
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
      if (!parse_A_instruction(line, &instr.instr.a)){
    	exit_program(EXIT_INVALID_A_INSTR, line_num, line);
      }
      instr.type = Atype;
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
      char tmp_line[MAX_LINE_LENGTH];
      strcpy(tmp_line, line);
      parse_C_instruction(tmp_line, &instr.instr.c);
      if(instr.instr.c.dest==-1){
        exit_program(EXIT_INVALID_C_DEST, line_num, line);
      }
      if(instr.instr.c.comp==-1){
        exit_program(EXIT_INVALID_C_COMP, line_num, line);
      }
      if(instr.instr.c.jump==-1){
        exit_program(EXIST_INVALID_C_JUMP, line_num, line);
      }
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

void add_predefined_symbols(){
  int i;
  predefined_symbol temp = {};
  for(i = 0; i<NUM_PREDEFINED_SYMBOLS; i++){
    temp=predefined_symbols[i];
    symtable_insert(temp.name, temp.address);
  }
}

bool parse_A_instruction(const char *line, a_instruction *instr){
  char* s=(char*)malloc(strlen(line));
  strcpy(s,line+1);
  char *s_end= NULL;
  long result = strtol(s, &s_end, 10);
  if(0==strcmp(s,s_end)){
    instr->value.label=(char*)malloc(strlen(line));
    strcpy(instr->value.label,s);
    instr->is_addr=false;
  }
  else if(*s_end != 0){
    return false;
  }
  else{
    instr->value.address=result;
    instr->is_addr=true;
  }
  return true;
}

void parse_C_instruction(char *line, c_instruction *instr){
  char *jump;
  jump = strtok(line, ";");
  instr->jump=str_to_jumpid(jump);
  char *comp;
  comp = strtok(line, "=");
  instr->dest=str_to_destid(line);
  if (comp == NULL) {
    instr->a=0;
    instr->comp=COMP_0;
  }
  else{
    int *temp=0;
    instr->comp=str_to_compid(line, temp);
    instr->a=temp;
  } 
}