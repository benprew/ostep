#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  char *data = malloc(100);

  printf("data[13]=%d\n",data[13]);

  free(data);

  return 0;
}

// ><> valgrind  ./a.out
// ==2264461== Memcheck, a memory error detector
// ==2264461== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==2264461== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
// ==2264461== Command: ./a.out
// ==2264461==
// ==2264461== Conditional jump or move depends on uninitialised value(s)
// ==2264461==    at 0x4CE6CA6: __vfprintf_internal (vfprintf-internal.c:1646)
// ==2264461==    by 0x4CD158E: printf (printf.c:33)
// ==2264461==    by 0x1091CD: main (malloc-6.c:7)
// ==2264461==
// ==2264461== Use of uninitialised value of size 8
// ==2264461==    at 0x4CCB16B: _itoa_word (_itoa.c:179)
// ==2264461==    by 0x4CE6964: __vfprintf_internal (vfprintf-internal.c:1646)
// ==2264461==    by 0x4CD158E: printf (printf.c:33)
// ==2264461==    by 0x1091CD: main (malloc-6.c:7)
// ==2264461==
// ==2264461== Conditional jump or move depends on uninitialised value(s)
// ==2264461==    at 0x4CCB17C: _itoa_word (_itoa.c:179)
// ==2264461==    by 0x4CE6964: __vfprintf_internal (vfprintf-internal.c:1646)
// ==2264461==    by 0x4CD158E: printf (printf.c:33)
// ==2264461==    by 0x1091CD: main (malloc-6.c:7)
// ==2264461==
// ==2264461== Conditional jump or move depends on uninitialised value(s)
// ==2264461==    at 0x4CE75E3: __vfprintf_internal (vfprintf-internal.c:1646)
// ==2264461==    by 0x4CD158E: printf (printf.c:33)
// ==2264461==    by 0x1091CD: main (malloc-6.c:7)
// ==2264461==
// ==2264461== Conditional jump or move depends on uninitialised value(s)
// ==2264461==    at 0x4CE6A87: __vfprintf_internal (vfprintf-internal.c:1646)
// ==2264461==    by 0x4CD158E: printf (printf.c:33)
// ==2264461==    by 0x1091CD: main (malloc-6.c:7)
// ==2264461==
// data[13]=0
// ==2264461==
// ==2264461== HEAP SUMMARY:
// ==2264461==     in use at exit: 0 bytes in 0 blocks
// ==2264461==   total heap usage: 2 allocs, 2 frees, 1,124 bytes allocated
// ==2264461==
// ==2264461== All heap blocks were freed -- no leaks are possible
// ==2264461==
// ==2264461== Use --track-origins=yes to see where uninitialised values come from
// ==2264461== For lists of detected and suppressed errors, rerun with: -s
// ==2264461== ERROR SUMMARY: 5 errors from 5 contexts (suppressed: 0 from 0)
