/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:21:42 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/26 03:46:27 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "include/libft.h"
#include "include/pipex.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int open(const char *path, int oflag, ...);
// ssize_t read(int fildes, void *buf, size_t nbyte);

__attribute__((destructor))
static void destructor() {
    system("leaks -q pipex");
}

void  error(void)
{
  puts("error");
  exit(1);
}

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


int main(int argc, char **argv, char **envp)
{
  int   fd[2];
  pid_t pid;
  char  **arg_c1, **arg_c2;
  char  *command;
  int   st;


  // TODO: error ハンドリング

  int infile = open(argv[1], O_RDONLY);
  if (infile < 0)
    error();

  int outfile = open(argv[4], O_WRONLY | O_APPEND);
  if (outfile < 0)
    error();

  int ret1 = pipe(fd);
  if (ret1 < 0)
    error();

  arg_c1 = ft_split(argv[2], ' ');
  arg_c2 = ft_split(argv[3], ' ');
  /*for (int i = 0; i < 2; i++)
    printf("%s\n", arg_c1[i]);*/

  char **path= get_path(envp);
  /*for (int i = 0; dir[i] != NULL; i++)
    printf("%s\n", dir[i]);*/

  pid = fork();
  if (pid == 0)
  {
    close(fd[0]);
    dup2(infile, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    for (int i = 0; path[i] != NULL; i++)
    {
      // sprintf(path, "%s/%s", dir[i], arg_c1[0]);
      command = get_command(path, i,  arg_c1[0]);
      execve(command, arg_c1, NULL);
    }
    error();
  }
  pid = fork();
  if (pid == 0)
  {
    close(fd[1]); // まさに重要！
    dup2(fd[0], STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    for(int i = 0; path[i] != NULL; i++)
    {
      // sprintf(path, "%s/%s", dir[i], arg_c2[0]);
      command = get_command(path, i, arg_c2[0]);
      execve(command, arg_c2, NULL);
    }
    error();
  }
  close(fd[0]);
  close(fd[1]);
  wait(&st);
  wait(&st);
  for (int i = 0; arg_c1[i] != NULL; i++)
    free(arg_c1[i]);
  free(arg_c1);
  for (int i = 0; arg_c2[i] != NULL; i++)
    free(arg_c2[i]);
  free(arg_c2);
  for(int i = 0; path[i] != NULL; i++)
    free(path[i]);
  free(path);
  return 0;
}
