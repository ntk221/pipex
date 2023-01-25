#include "include/pipex.h"
#include <stddef.h>
#include <stdlib.h>
#include "include/libft.h"

char  *get_command(char **path, int i, char *cmd)
{
  char  *tmp;
  char  *command;

  if (path[i])
  {
    tmp = ft_strjoin(path[i], "/");
    command = ft_strjoin(tmp, cmd);
    free(tmp);
    if (access(command, 0) == 0)
      return (command);
    free(command);
  }
  return (NULL);
}

#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    char **path = get_path(envp);
    for(int i = 0; path[i] != NULL; i++)
    {
        char *command = get_command(path, i, "cat");
        printf("%s\n", command);
    }
}