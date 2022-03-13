#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <unistd.h> // fork
#include <sys/wait.h> // wait

int main(int argc, char *argv[]) {
  FILE* fh = fopen("test.txt", "a");
  if (!fh) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }

  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    fputs("Here in the child", fh);
  } else {
    wait(NULL);
    fputs("in parent.", fh);
  }

  fclose(fh);

  return EXIT_SUCCESS;
}
