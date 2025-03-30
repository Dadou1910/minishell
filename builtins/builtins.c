/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:11:17 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 18:29:46 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtins(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (0);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (0);
	else
		return (-1);
	return (-42);
}

int	is_builtins(t_command *cmd)
{
	int	i;

	i = 1;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (echo(cmd));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit_shell(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd(cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd(cmd->args));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env(cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0 && cmd->args[1] != NULL)
		return (deals_unset(cmd), 0);
	else if (ft_strcmp(cmd->args[0], "export") == 0 && cmd->args[1])
	{
		helper_is_builtins(cmd, &i);
		return (1);
	}
	return (-1);
}

int	exported_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	is_alnul_export(char *str, int i)
{
	int	j;

	j = 0;
	if (str[j] == '=')
		return (-1);
	while (j <= i)
	{
		if (ft_isalnum(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}
