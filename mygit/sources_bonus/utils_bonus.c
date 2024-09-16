/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:20:53 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 01:12:46 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	check_cmd_bonus(int argc, char **argv, char **envp, int i)
{
	char	*str;
	char	**command;

	while (argv[i] && i < argc - 1)
	{
		if ((i < argc - 1) && ft_strcmp(argv[i], "/bin/") == 0)
			bin_check(argv[i]);
		else
		{
			command = ft_split(argv[i], ' ');
			if (command == NULL)
				ft_error("malloc");
			str = path(command[0], envp);
			if (str == NULL || argv[i][0] == '.' || argv[i][0] == '\0')
			{
				(free(str), freetab(command));
				command_not_found(argv[i]);
			}
			(free(str), freetab(command));
		}
		i++;
	}
}

void	check_argv_bonus(int argc, char **argv, char **envp)
{
	int	i;

	i = 2;
	if (argc < 5 || argc > 1026)
	{
		write(1, "Argv error\n", 11);
		exit(EXIT_FAILURE);
	}
	while (argv[i])
	{
		if (!argv[i])
		{
			write(1, "Argv error\n", 11);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (!envp[0])
	{
		if (check_envp(argc, argv) == 0)
			return ;
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
		i++;
	check_cmd_bonus(argc, argv, envp, i);
}

char	*ft_ligne(char *str)
{
	char	*res;
	int		i;
	int		j;
	size_t	len;

	i = 3;
	j = 0;
	len = strlen(str);
	if (len < 4)
	{
		return (NULL);
	}
	res = (char *)malloc(sizeof(char) * (len - 2));
	if (res == NULL)
	{
		return (NULL);
	}
	while (str[i] && str[i] != '\n')
	{
		res[j] = str[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}
