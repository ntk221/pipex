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

int get_arg2(char *c, char *arg[], char *sym)
{
    int i = 0;
    arg[i] = strtok(c, sym);
    while(arg[i] != NULL)
    {
        i++;
        arg[i] = strtok(NULL, sym);
    }
    return i;
}

int main(int argc, char **argv)
{
  int   fd[2];
  pid_t pid;
  char  *arg_c1[32], *arg_c2[32];
  int   st;


  // TODO: error ハンドリング
  int ret1 = pipe(fd);
  if (ret1 < 0)
  {
      perror("pipe");
      exit(1);
  }

  get_arg2(argv[2], arg_c1, " ");
  get_arg2(argv[3], arg_c2, " ");
  /*for(int i = 0; arg_c2[i] != NULL; i++)
    printf("%s\n", arg_c2[i]);*/

  pid = fork();
  if (pid == 0)
  {
    int infile = open(argv[1], O_RDONLY);
    dup2(infile, 0);
    close(infile);
    dup2(fd[1], STDOUT_FILENO);
    execv(arg_c1[0], arg_c1);
    perror("error");
    exit(99);
  }
  pid = fork();
  if (pid == 0)
  {
    int outfile = open(argv[4], O_WRONLY);
    dup2(outfile, fd[1]);
    dup2(fd[0], STDIN_FILENO);
    execv(arg_c2[0], arg_c2);
    perror("error");
    exit(99);
  }
  close(fd[0]);
  close(fd[1]);
  wait(&st);
  wait(&st);
  return 0;
}
