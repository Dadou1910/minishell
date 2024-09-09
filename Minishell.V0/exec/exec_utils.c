/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 10:50:08 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[i][0])
		i++;
	return (i);
}

char	*real_line(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(str)));
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	free(str);
	res[i] = '\0';
	return (res);
}

int	count_pipe(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '|')
			count++;
		i++;
	}
	return (count + 1);
}

void	check_(char **line, int count, char **envp)
{
	pid_t	pid;
	char	**tab;

	pid = fork();
	if (pid < 0)
	{
		perror("Erreur lors de fork");
	}
	else if (pid == 0)
	{
		tab = ft_split(line[0], ' ');
		if (ft_strcmp(line[0], "pipex") == 0)
		{
			pipex(line, count, envp);
			freetab(tab);
			freetab(line);
			exit(EXIT_SUCCESS);
		}
		freetab(line);
		if (execve(path(tab[0], envp), &tab[0], envp) < 0)
		{
			freetab(tab);
			printf("zsh: command not found: %s\n", tab[0]);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, NULL, 0);
}
