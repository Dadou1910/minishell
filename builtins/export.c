/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 18:28:14 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	check_export(char *exported, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = exported_len(exported);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(exported, envp[i], len) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	get_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**export_1(char *exported, char **envp, int al_here)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * (get_env_size(envp) + 1));
	if ((!res))
		malloc_help();
	while (envp[i])
	{
		if (i == al_here)
			res[i] = ft_strdup(exported);
		else
			res[i] = ft_strdup(envp[i]);
		i++;
	}
	res[i] = NULL;
	freetab(envp);
	return (res);
}

char	**export_2(char *exported, char **envp)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * (get_env_size(envp) + 2));
	if ((!res))
		malloc_help();
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		i++;
	}
	res[i] = ft_strdup(exported);
	i++;
	res[i] = NULL;
	freetab(envp);
	return (res);
}

char	**ft_export(t_command *cmd, int i)
{
	char	**res;
	int		al_here;

	al_here = check_export(cmd->args[i], cmd->table->envp);
	if (al_here == -1)
		return (cmd->table->envp);
	if (al_here != 0)
		res = export_1(cmd->args[i], cmd->table->envp, al_here);
	else
		res = export_2(cmd->args[i], cmd->table->envp);
	return (res);
}
