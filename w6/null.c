#include <stdio.h>

int main(int argc, char* argv[]) {
  int *p;

  printf("%d\n", *p);
}

// ><> valgrind --leak-check=yes ./a.out
// ==2259144== Memcheck, a memory error detector
// ==2259144== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==2259144== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
// ==2259144== Command: ./a.out
// ==2259144==
// ==2259144== Use of uninitialised value of size 8
// ==2259144==    at 0x109160: main (null.c:6)
// ==2259144==
// ==2259144== Invalid read of size 4
// ==2259144==    at 0x109160: main (null.c:6)
// ==2259144==  Address 0x1 is not stack'd, malloc'd or (recently) free'd
// ==2259144==
// ==2259144==
// ==2259144== Process terminating with default action of signal 11 (SIGSEGV)
// ==2259144==  Access not within mapped region at address 0x1
// ==2259144==    at 0x109160: main (null.c:6)
// ==2259144==  If you believe this happened as a result of a stack
// ==2259144==  overflow in your program's main thread (unlikely but
// ==2259144==  possible), you can try to increase the size of the
// ==2259144==  main thread stack using the --main-stacksize= flag.
// ==2259144==  The main thread stack size used in this run was 8388608.
// ==2259144==
// ==2259144== HEAP SUMMARY:
// ==2259144==     in use at exit: 0 bytes in 0 blocks
// ==2259144==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
// ==2259144==
// ==2259144== All heap blocks were freed -- no leaks are possible
// ==2259144==
// ==2259144== Use --track-origins=yes to see where uninitialised values come from
// ==2259144== For lists of detected and suppressed errors, rerun with: -s
// ==2259144== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
