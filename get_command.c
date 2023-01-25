/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 05:27:47 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/26 05:28:02 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"
#include <stddef.h>
#include <stdlib.h>
#include "include/libft.h"

char	*get_command(char **path, int i, char *cmd)
{
	char	*tmp;
	char	*command;

	if (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK && X_OK) == 0)
			return (command);
		free(command);
	}
	return (NULL);
}

/*#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    char **path = get_path(envp);
    for(int i = 0; path[i] != NULL; i++)
    {
        char *command = get_command(path, i, "cat");
        printf("%s\n", command);
    }
}
*/
