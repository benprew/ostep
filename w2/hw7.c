#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <unistd.h> // fork
#include <sys/wait.h> // wait

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    return EXIT_FAILURE;
  } else if (rc == 0) {
    fclose(stdout);
    puts("child print");
  } else {
    wait(NULL);
    puts("print in parent");
  }
  return EXIT_SUCCESS;
}
