#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int *data = malloc(100);

  int *p = data + 13;

  free(p);

  return 0;
}
// gcc -g malloc-7.c
// malloc-7.c: In function ‘main’:
// malloc-7.c:9:3: warning: ‘free’ called on pointer ‘data’ with nonzero offset 52 [-Wfree-nonheap-object]
// 9 |   free(p);
//   |   ^~~~~~~
// malloc-7.c:5:15: note: returned from ‘malloc’
// 5 |   int *data = malloc(100);
//   |               ^~~~~~~~~~~
//
// Compilation finished at Mon Apr 11 23:15:25
