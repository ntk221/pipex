/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 04:35:15 by kazuki            #+#    #+#             */
/*   Updated: 2023/01/26 04:38:22 by kazuki           ###   ########.fr       */
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
	for (int i = 0; arg_c1[i] != NULL; i++)
		free(arg_c1[i]);
	free(arg_c1);
	for (int i = 0; arg_c2[i] != NULL; i++)
		free(arg_c2[i]);
	free(arg_c2);
	for(int i = 0; path[i] != NULL; i++)
		free(path[i]);
	free(path);
}
