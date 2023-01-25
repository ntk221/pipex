/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:21:59 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/26 04:49:52 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/libft.h"

char	*ft_getenv(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	**get_path(char **envp)
{
	char	*env;
	char	**path;

	env = ft_getenv(envp);
	dir = ft_split(env, ':');
	return (path);
}

/*int main(int argc, char **argv, char **envp)
{
    char **dir;
    dir = get_path(envp);
    for (int i = 0; dir[i] != NULL; i++)
        printf("%s\n", dir[i]);
}*/
