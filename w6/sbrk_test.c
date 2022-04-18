#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main( int argc, char *argv[] )  {
  int x = 3;
  printf("code:%p heap:%p stack:%p sbrk:%p\n", (void*) main, (void*) malloc(1), (void *)&x, sbrk(0));
  sbrk(sizeof(int) * 10000);
  char *p = malloc(1);
  printf("code:%p heap:%p stack:%p sbrk:%p\n", (void*) main, (void*) malloc(1), (void *)&x, sbrk(0));

  return 0;
}
