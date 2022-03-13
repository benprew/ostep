#include <stdlib.h> // EXIT_*
#include <stdio.h> // fputs/puts
#include <unistd.h> // fork
#include <sys/wait.h> // wait


int main(int argc, char *argv[]) {
  int rc;

  rc = fork();
  if (rc == 0) {
    puts("execl");
    execl("/bin/ls", "/bin/ls", NULL);
  }
  wait(NULL);

  rc = fork();
  if (rc == 0) {
    puts("execvp");
    char *args[]={"/bin/ls", NULL};
    execvp(args[0], args);
  }
  wait(NULL);

  rc = fork();
  if (rc == 0) {
    puts("execlp");
    execlp("ls", "ls", NULL);
  }
  wait(NULL);
}
