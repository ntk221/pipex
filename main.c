#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "include/get_next_line.h"

// int open(const char *path, int oflag, ...);
// ssize_t read(int fildes, void *buf, size_t nbyte);

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
  int   fd[2];
  pid_t pid;

  int ret1 = pipe(fd);
  if (ret1 < 0)
  {
      perror("pipe");
      exit(1);
  }

  pid = fork();
  if (pid == 0)
  {
    int infile = open("file1", O_RDONLY);
    char *argv[] = {"cat", NULL};
    dup2(infile, 0);
    close(infile);
    execv("/bin/cat", argv);
    perror("/bin/cat");
    exit(99);
  }
  else
  {
    waitpid(pid, NULL, 0);
    puts("success!");
    exit(10);
  }
  return 0;
}
