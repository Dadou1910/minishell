/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:55 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 10:22:39 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

int	env(t_command *cmd)
{
	int	i;
	int	output_fd;

	if (cmd->fd_out == -2)
		output_fd = STDOUT_FILENO;
	else
		output_fd = cmd->fd_out;
	i = 0;
	if (!cmd->table || !cmd->table->envp || !cmd->table->envp[0])
		return (-42);
	while (cmd->table->envp[i] && cmd->table->envp[i][0] != '\0')
	{
		write(output_fd, cmd->table->envp[i], ft_strlen(cmd->table->envp[i]));
		write(output_fd, "\n", 1);
		i++;
	}
	return (0);
}
