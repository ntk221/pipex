/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 02:48:21 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/26 05:31:13 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipex {
	int		fd[2];
	char	**arg_c1;
	char	**arg_c2;
	char	**path;
	int		st;
	int		infile;
	int		outfile;
}	t_pipex;

char	**get_path(char **envp);
char	*get_command(char **path, int i, char *cmd);
void	free_all(char **arg_c1, char **arg_c2, char **path);
void	die(char *reason);

#endif