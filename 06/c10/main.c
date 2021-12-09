#include "parser.h"
#include "error.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[]){
  if (argc != 2) {
    // incorrect number of arguments
    exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);        
  }  
  instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
  FILE *fin = fopen( argv[1], "r" );
  if(fin == NULL){ 
    exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
  }
  int num_instructions;
  num_instructions = parse(fin, instructions);
  fclose(fin);
  free(instructions);
}
