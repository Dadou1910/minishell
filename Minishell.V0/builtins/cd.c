/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:20:10 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 01:56:32 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char *line)
{
	if (access((const char *)line, F_OK | R_OK) != 0)
	{
		write(1, "cd: no such file or directory: '", 32);
		write(1, line, strlen(line));
		write(1, "'\n", 2);
		return ;
	}
	if (chdir((const char *)line) != 0)
	{
		perror("chdir() erreur");
		return ;
	}
}

void	ft_cd_wave(const char *path)
{
	const char	*home_directory;

	if (path == NULL || strlen(path) == 0)
	{
		ft_putendl_fd("Erreur : chemin invalide.\n", 2);
		return ;
	}
	if (strcmp(path, "~") == 0)
	{
		home_directory = getenv("HOME");
		if (home_directory == NULL)
			return ;
		if (chdir(home_directory) != 0)
			return ;
	}
}

void	check_cd(char *line, char **envp)
{
	char	**tab;
	char	*str;

	(void)envp;
	tab = ft_split(line, ' ');
	if (ft_strcmp(tab[1], "~") == 0)
	{
		ft_cd_wave(tab[1]);
	}
	else
	{
		str = ft_strjoin(tab[1], "/");
		ft_cd(str);
	}
	free(line);
}
