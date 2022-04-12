#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  char *data = malloc(100);

  data[100] = 0;

  free(data);

  return 0;
}

// ><> valgrind --leak-check=yes ./a.out
// ==2263365== Memcheck, a memory error detector
// ==2263365== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==2263365== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
// ==2263365== Command: ./a.out
// ==2263365==
// ==2263365== Invalid write of size 1
// ==2263365==    at 0x109192: main (malloc-5.c:7)
// ==2263365==  Address 0x4e9c0a4 is 0 bytes after a block of size 100 alloc'd
// ==2263365==    at 0x4A40045: malloc (vg_replace_malloc.c:381)
// ==2263365==    by 0x109185: main (malloc-5.c:5)
// ==2263365==
// ==2263365==
// ==2263365== HEAP SUMMARY:
// ==2263365==     in use at exit: 0 bytes in 0 blocks
// ==2263365==   total heap usage: 1 allocs, 1 frees, 100 bytes allocated
// ==2263365==
// ==2263365== All heap blocks were freed -- no leaks are possible
// ==2263365==
// ==2263365== For lists of detected and suppressed errors, rerun with: -s
// ==2263365== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
