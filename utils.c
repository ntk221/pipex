/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 04:35:15 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/26 05:29:30 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"
#include <stdlib.h>
#include <stdio.h>

void	die(char *reason)
{
	perror(reason);
	exit(1);
}

void	free_all(char **arg_c1, char **arg_c2, char **path)
{
	int	i;

	i = 0;
	while (arg_c1[i] != NULL)
		free(arg_c1[i++]);
	free(arg_c1);
	i = 0;
	while (arg_c2[i] != NULL)
		free(arg_c2[i++]);
	free(arg_c2);
	while (path[i] != NULL)
		free(path[i++]);
	free(path);
}
