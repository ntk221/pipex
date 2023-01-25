/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:21:42 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/26 04:50:16 by kazuki           ###   ########.fr       */
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

__attribute__((destructor))
static void destructor() {
    system("leaks -q pipex");
}

void	do_child_1(int *fd, int infile, char **path, char **arg_c1);
void	do_child_2(int *fd, int outfile, char **path, char **arg_c2);

int main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		st;
	int		infile;
	int		outfile;


	// TODO: error ハンドリング
	if (argc != 0)

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		die("open");
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (outfile < 0)
		die("open");
	if (pipe(p.fd)< 0)
		die("pipe");
	p.arg_c1 = ft_split(argv[2], ' ');
	p.arg_c2 = ft_split(argv[3], ' ');
	p.path = get_path(envp);
	if (fork() == 0)
		do_child_1(p.fd, infile, p.path, p.arg_c1);
	if (fork() == 0)
		do_child_2(p.fd, outfile, p.path, p.arg_c2);
	close(p.fd[0]);
	close(p.fd[1]);
	wait(&st);
	wait(&st);
	free_all(p.arg_c1, p.arg_c2, p.path);
	return (0);
}

void	do_child_2(int *fd, int outfile, char **path, char **arg_c2)
{
	char	*command;

	close(fd[1]); // まさに重要！
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	for(int i = 0; path[i] != NULL; i++)
	{
		// sprintf(path, "%s/%s", dir[i], arg_c2[0]);
		command = get_command(path, i, arg_c2[0]);
		execve(command, arg_c2, NULL);
	}
	die("execve");
}

void	do_child_1(int *fd, int infile, char **path, char **arg_c1)
{
	char *command;
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	for (int i = 0; path[i] != NULL; i++)
	{
		// sprintf(path, "%s/%s", dir[i], arg_c1[0]);
		command = get_command(path, i,  arg_c1[0]);
		execve(command, arg_c1, NULL);
	}
	die("execve");
}
