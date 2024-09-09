/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:32:54 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/03 17:59:56 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	check_path_in_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == NULL)
		return (-1);
	return (i);
}

void	execute_bin(char *cmd)
{
	char	**commande;
	char	*pathoche;

	commande = ft_split(cmd, ' ');
	if (!commande)
		ft_error("execute");
	pathoche = commande[0];
	if (execve(pathoche, commande, NULL) == -1)
	{
		free(pathoche);
		freetab(commande);
		ft_error("cmd error");
	}
}

void	execute(char *cmd, char **envp)
{
	char	**commande;
	char	*pathoche;

	if ((ft_strncmp(cmd, "/bin/", 5) == 0))
		execute_bin(cmd);
	else
	{
		commande = ft_split(cmd, ' ');
		if (!commande)
			ft_error("execute");
		pathoche = path(commande[0], envp);
		if (!pathoche)
		{
			freetab(commande);
			ft_error("execute");
		}
		if (execve(pathoche, commande, envp) == -1)
		{
			free(pathoche);
			freetab(commande);
			ft_error("cmd error");
		}
	}
}

char	*path(char *cmd, char **envp)
{
	char	**total_path;
	char	*join_path;
	char	*path;
	int		i;

	i = check_path_in_env(envp);
	if (i == -1)
		return (NULL);
	total_path = ft_split(envp[i] + 5, ':');
	if (!total_path)
		ft_error("malloc");
	i = -1;
	while (total_path[++i])
	{
		join_path = ft_strjoin(total_path[i], "/");
		if (!join_path)
			(freetab(total_path), ft_error("malloc"));
		path = ft_strjoin(join_path, cmd);
		if (free(join_path), !path)
			(freetab(total_path), ft_error("malloc"));
		if (access(path, F_OK) == 0)
			return (freetab(total_path), path);
		free(path);
	}
	return (freetab(total_path), NULL);
}
