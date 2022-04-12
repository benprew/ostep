#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int *data = malloc(sizeof(int));

  data[0] = 1;

  data = realloc(data, sizeof(int) * 2);

  data[1] = 2;

  data = realloc(data, sizeof(int) * 10);

  for (int i = 2; i< 10; i++) {
    data[i] = i + 1;
  }

  for (int i = 0; i < 10; i++) {
    printf("%d ", data[i]);
  }
  puts("\n");

  free(data);

  return 0;
}

// ><> valgrind ./a.out
// ==2270244== Memcheck, a memory error detector
// ==2270244== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==2270244== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
// ==2270244== Command: ./a.out
// ==2270244==
// 1 2 3 4 5 6 7 8 9 10
//
// ==2270244==
// ==2270244== HEAP SUMMARY:
// ==2270244==     in use at exit: 0 bytes in 0 blocks
// ==2270244==   total heap usage: 4 allocs, 4 frees, 1,076 bytes allocated
// ==2270244==
// ==2270244== All heap blocks were freed -- no leaks are possible
// ==2270244==
// ==2270244== For lists of detected and suppressed errors, rerun with: -s
// ==2270244== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
