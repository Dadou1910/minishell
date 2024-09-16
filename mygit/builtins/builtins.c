/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:03:09 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 01:56:57 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_pwd(void)
{
	char	*cwd;

	cwd = malloc(1024);
	if (cwd == NULL)
	{
		perror("Erreur de malloc");
		return ;
	}
	if (getcwd(cwd, 1024) != NULL)
	{
		write(1, cwd, strlen(cwd));
	}
	free(cwd);
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	is_builtin(char *line, char **envp)
{
	if (ft_strncmp(line, "cd", 2) == 0)
	{
		check_cd(line, envp);
		return (0);
	}
	else if (ft_strcmp(line, "env") == 0)
	{
		ft_env(envp);
		return (0);
	}
	else if (ft_strcmp(line, "pwd") == 0)
	{
		ft_pwd();
		return (0);
	}
	return (-1);
}
