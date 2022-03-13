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
    printf("child wait: %d\n", wait(NULL));
  } else {
    printf("parent wait: %d\n", wait(NULL));
  }
  return EXIT_SUCCESS;
}
