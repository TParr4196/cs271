#include "parser.c"

int main(int argc, const char *argv[]) {
if (argc<2) {
    printf("%d",argc);
    printf("Usage: %s [filename]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  FILE *fin = fopen( argv[1], "r" );
  if (fin==NULL) {
    perror("Unable to open file!");
    exit(EXIT_FAILURE);
  }
  parse(fin);
  fclose(fin);
}