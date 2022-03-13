#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <unistd.h> // fork
#include <sys/wait.h> // wait

int main(int argc, char *argv[]) {
  int v = 100;
  printf("start v: %d\n",v);
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    return EXIT_FAILURE;
  } else if (rc == 0) {
    v = 200;
    printf("v in child: %d\n", v);
  } else {
    v = 125;
    printf("v in parent: %d\n", v);
    wait(NULL);
  }
  return EXIT_SUCCESS;
}
