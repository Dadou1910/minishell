/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:27:44 by jeannelefev       #+#    #+#             */
/*   Updated: 2024/09/03 17:59:52 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	check_envp(int argc, char **argv)
{
	int	i;

	i = 2;
	if (ft_strcmp(argv[1], "here_doc") == 0)
		i++;
	while (argv[i] && i < argc - 1)
	{
		if (argv[i][0] == '\0')
			command_not_found(argv[i]);
		if ((i < argc - 1) && ft_strncmp(argv[i], "/bin/", 5) == 0)
			bin_check(argv[i]);
		else
		{
			write(1, "Envp error\n", 11);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}

void	bin_check(char *cmd)
{
	if (access(cmd, X_OK | F_OK) == 0)
		return ;
}

void	check_cmd(char *cmd, char **envp)
{
	char	*str;
	char	**command;

	if (ft_strncmp(cmd, "/bin/", 5) == 0)
	{
		bin_check(cmd);
	}
	else
	{
		command = ft_split(cmd, ' ');
		if (command == NULL)
			ft_error("malloc");
		str = path(command[0], envp);
		if (str == NULL || cmd[0] == '.' || cmd[0] == '\0')
		{
			(free(str), freetab(command));
			command_not_found(cmd);
		}
		(free(str), freetab(command));
	}
}
