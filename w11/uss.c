#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

char* itoa(long val, int base){
  static char buf[64] = {0};
  int i = 62;
  for(; val && i ; --i, val /= base)
    buf[i] = "0123456789abcdef"[val % base];
  return &buf[i+1];
}

int main(int argc, char* argv[])
{
  int fn_size = 256;
  char filename[fn_size];
  if (argc == 2) {
    snprintf(filename, fn_size, "/proc/%s/pagemap", argv[1]);
  } else {
    printf("Usage: uss <PID>\n");
  }

  int fd = open(filename, O_WRONLY);
  if (fd == -1) {
    perror("open\n");
    exit(EXIT_FAILURE);
  }

  long pmap;
  int sz;
  int i = 0;

  while (true) {
    i++;
    sz = pread(fd, &pmap, sizeof(long), i * 8);
    if (sz < sizeof(long)) {
      printf("Error reading from %s\n", filename);
      break;
    }
    printf("pmap: %lX\n", pmap);
  }

  //  printf("binary: %s\n",itoa(pmap,2));

  return 0;
}
