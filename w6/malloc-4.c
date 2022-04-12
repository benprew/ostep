#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int *p = calloc(1, 4);

  if (p == NULL)
    printf("p is null\n");

  printf("%d\n", *p);

  return 0;
}
// ><> valgrind --leak-check=yes ./a.out
// ==2261298== Memcheck, a memory error detector
// ==2261298== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==2261298== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
// ==2261298== Command: ./a.out
// ==2261298==
// 0
// ==2261298==
// ==2261298== HEAP SUMMARY:
// ==2261298==     in use at exit: 4 bytes in 1 blocks
// ==2261298==   total heap usage: 2 allocs, 1 frees, 1,028 bytes allocated
// ==2261298==
// ==2261298== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
// ==2261298==    at 0x4A44BFD: calloc (vg_replace_malloc.c:1328)
// ==2261298==    by 0x1091AA: main (malloc.c:5)
// ==2261298==
// ==2261298== LEAK SUMMARY:
// ==2261298==    definitely lost: 4 bytes in 1 blocks
// ==2261298==    indirectly lost: 0 bytes in 0 blocks
// ==2261298==      possibly lost: 0 bytes in 0 blocks
// ==2261298==    still reachable: 0 bytes in 0 blocks
// ==2261298==         suppressed: 0 bytes in 0 blocks
// ==2261298==
// ==2261298== For lists of detected and suppressed errors, rerun with: -s
// ==2261298== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
