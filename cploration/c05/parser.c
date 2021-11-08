#include "parser.h"

void parse(FILE * file) {
  char line[MAX_LINE_LENGTH] = {0};
  while (fgets(line, sizeof(line), file)) {
    strip(line);
    if (!*line) continue;
    char inst_type = ' ';
    if(is_Atype(line)){
      inst_type='A';
    }
    if(is_label(line)){
      inst_type='L';
    }
    if(is_Ctype(line)){
      inst_type='C';
    }
    if(inst_type != ' '){
      printf("%c  %s",inst_type,line);
    }
    else{
      printf("%s", line);
    }
  }
}

char *strip(char *s){
  char s_new[strlen(s)+1];
  int i=0;
  for (char *s2 = s; *s2; s2++) { 
    if (*s2=='/' && *(s+1)=='/'){
      break;
    }
    else if (*s2!=' '){
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
