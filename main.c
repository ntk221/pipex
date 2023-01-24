/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:21:42 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/25 02:28:30 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
// #include "include/get_next_line.h"
#include "include/libft.h"

// int open(const char *path, int oflag, ...);
// ssize_t read(int fildes, void *buf, size_t nbyte);

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void  error(void)
{
  puts("error");
  exit(1);
}

int main(int argc, char **argv)
{
  int   fd[2];
  pid_t pid;
  char  **arg_c1, **arg_c2;
  int   st;

  // TODO: error ハンドリング

  int infile = open(argv[1], O_RDONLY);
  if (infile < 0)
    error();

  int outfile = open(argv[4], O_WRONLY);
  if (outfile < 0)
    error();

  int ret1 = pipe(fd);
  if (ret1 < 0)
    error();

  arg_c1 = ft_split(argv[2], ' ');
  arg_c2 = ft_split(argv[3], ' ');
  /*for(int i = 0; arg_c2[i] != NULL; i++)
    printf("%s\n", arg_c2[i]);*/

  pid = fork();
  if (pid == 0)
  {
    dup2(infile, 0);
    // close(infile);
    dup2(fd[1], STDOUT_FILENO);
    execv(arg_c1[0], arg_c1);
    perror("error");
    exit(99);
  }
  pid = fork();
  if (pid == 0)
  {
    int outfile = open(argv[4], O_WRONLY);
    dup2(4, fd[1]); // ?????
    //close(fd[1]);
    //close(STDOUT_FILENO);
    dup2(fd[0], STDIN_FILENO);
    // close(fd[1]);
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
