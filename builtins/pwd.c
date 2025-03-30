/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:50 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 10:28:16 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(t_command *cmd)
{
	char	cwd[1024];
	int		output_fd;

	if (cmd->fd_out == -2)
		output_fd = STDOUT_FILENO;
	else
		output_fd = cmd->fd_out;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(output_fd, cwd, ft_strlen(cwd));
		write(output_fd, "\n", 1);
	}
	else
		return (-42);
	return (0);
}
