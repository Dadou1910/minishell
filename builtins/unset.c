/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:40 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 18:31:57 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_unset(char **envp, const char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			return (0);
		i++;
	}
	return (-1);
}

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	return (count);
}

char	**unset(char **envp, const char *var)
{
	int		count;
	char	**new_env;
	int		i;
	int		j;

	count = 0;
	if (check_unset(envp, var) == -1)
		return (envp);
	count = count_env_vars(envp);
	new_env = malloc(sizeof(char *) * count);
	i = 0;
	j = 0;
	if ((!new_env))
		malloc_help();
	while (i < count)
	{
		if (ft_strncmp((envp)[i], var, ft_strlen(var)) != 0)
		{
			new_env[j++] = ft_strdup((envp)[i]);
		}
		i++;
	}
	new_env[j] = NULL;
	freetab(envp);
	return (new_env);
}
