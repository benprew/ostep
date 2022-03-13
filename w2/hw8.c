#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <uni std.h> // fork
#include <sys/wait.h> // wait

/*

I was reading this SO post[1] and it discusses the guarantee that read() and
write() should be atomic up to the size of PIPE_BUF, but when I ran my program I
would get output like:

> parent message: bye, felicia
=> read child start
bye, felic==> write child
ia
==> writing: hello
hello
> print in parent

But then I realized it was because I am calling write with a single character.
Beacuse I am issuing multiple writes for the string "bye, felicia", there is not
guarantee that the entire string will be printed at once.

Also, most of the pipe code was taken from the pipe man page example.

[1] https://unix.stackexchange.com/questions/91058/file-descriptor-and-fork

*/


int main(int argc, char *argv[]) {
  int pipefd[2];
  pid_t cpid;
  char buf;

  if (pipe(pipefd) == -1) {
    perror("pipe");
    return EXIT_FAILURE;
  }
  cpid = fork();
  if (cpid < 0) {
    perror("fork failed");
    return EXIT_FAILURE;
  } else if (cpid == 0) {
    puts("=> read child start");
    while (read(pipefd[0], &buf, 1) > 0) {
      write(STDOUT_FILENO, &buf, 1);
    }
    puts("=> read child done");
    close(pipefd[0]);
    close(pipefd[1]); // close unused write end
    return EXIT_SUCCESS;
  }

  cpid = fork();
  if (cpid < 0) {
    perror("fork failed");
    return EXIT_FAILURE;
  } else if (cpid == 0) {
    char msg[] = "hello\n";
    puts("==> write child");
    printf("==> writing: %s", msg);
    write(pipefd[1], msg, 7);
    close(pipefd[1]);
    return EXIT_SUCCESS;
  }

  char msg[] = "bye, felicia\n";
  printf("> parent message: %s", msg);
  write(pipefd[1], msg, 14);
  close(pipefd[0]);
  close(pipefd[1]);
  wait(NULL);
  puts("> print in parent");
  return EXIT_SUCCESS;
}
