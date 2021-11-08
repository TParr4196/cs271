/** WARMUP **/
// declare a string with value
#include <stdio.h>
#include <string.h>
#define MAX_LIMIT 100
int main(void){
  char hello[] = "Hello";
  char welcome[MAX_LIMIT];
  // declare an empty string
  strcpy(welcome, hello);
  strcat(welcome, " ");
  char name[MAX_LIMIT];

  // prompt user
  printf("What is your name?");

  // read in a string from user and save in variable
  // [^\n] means to discard the newline character
  scanf("%[^\n]s", name);
  strcat(welcome, name);
  strcat(welcome, "!");

  // print out "hello <name>"
  printf(welcome);

  /** Exercise 2 **/
  printf("\n");
  printf("Your name is %d characters long", strlen(name));

  /** Exercise 3 **/
  printf("\n");
  char prof[8] = {'P','a','t','r','i','c','k','\0'};
  if (strcmp(name,prof)<0) {
    printf("%s is before %s", name, prof);
  }else if (strcmp(name,prof)>0) {
    printf("%s is after %s", prof, name);
  }else{
    printf("%s is %s", name, prof);
  }
}
