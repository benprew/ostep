#include <stdlib.h> // EXIT_*
#include <stdio.h> // fputs/puts
#include <unistd.h> // fork
#include <sys/wait.h> // wait

int with_wait() {
  int rc = fork();
  if (rc < 0) {
    fputs("fork failed", stderr);
    return EXIT_FAILURE;
  } else if (rc == 0) {
    puts("ww hello");
    exit(1);
  } else {
    wait(NULL);
    puts("ww goodbye.");
  }
  return EXIT_SUCCESS;
}

int no_wait() {
  int rc = fork();
  if (rc < 0) {
    fputs("fork failed", stderr);
    return EXIT_FAILURE;
  } else if (rc == 0) {
    puts("nw hello");
    exit(1);
  } else {
    sleep(2);
    puts("nw goodbye.");
  }
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (with_wait() != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  return no_wait();
}
