#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// 3. Next, create a little program that uses a certain amount of memory, called
// memory-user.c. This program should take one command-line argument: the number
// of megabytes of memory it will use.  When run, it should allocate an array, and
// constantly stream through the array, touching each entry. The program should do
// this indefinitely, or, perhaps, for a certain amount of time also specified at
// the command line.
//
// 4. Now, while running your memory-user program, also (in a different terminal
// window, but on the same machine) run the free tool. How do the memory usage
// totals change when your program is running? How about when you kill the
// memory-user program?Do the numbers match your expectations? Try this for
// different amounts of memory usage. What happens when you use really large
// amounts of memory?

const int MIB = 1048576;

int main( int argc, char *argv[] )  {
  int size_mb = 100;
  if (argc > 1)
    sscanf(argv[1], "%d", &size_mb);

  unsigned int len = size_mb * MIB;
  char *arr = malloc(len);

  printf("argc=%d len=%d pid=%d\n", argc, len, getpid());

  for (;;) {
    for (int i = 0; i < len; i++) {
      arr[i] = 1;
    }
    sleep(5);
  }
}
