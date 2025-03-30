/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:39:45 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/15 14:14:59 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_command	*allocate_command_struct(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	return (cmd);
}

void	allocate_command_arrays(t_command *cmd)
{
	cmd->sargs = malloc(sizeof(char *) * 1024);
	cmd->args = malloc(sizeof(char *) * 1024);
	cmd->token_quotes = malloc(sizeof(char *) * 1024);
	cmd->result = malloc(sizeof(char) * 4096);
	if (!cmd->sargs || !cmd->token_quotes || !cmd->result || !cmd->args)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ft_bzero(cmd->sargs, 1024);
	ft_bzero(cmd->token_quotes, 1024);
	ft_bzero(cmd->result, 1024);
}

void	initialize_command_defaults(t_command *cmd, t_table *table)
{
	cmd->result[0] = '\0';
	ft_bzero(cmd->token_quotes, 1024);
	cmd->fd_in = -2;
	cmd->here_doc = -2;
	cmd->lim = NULL;
	cmd->fd_out = -2;
	cmd->pprev = -2;
	cmd->table = table;
	cmd->next = NULL;
}

t_command	*initialize_t_command(t_table *table)
{
	t_command	*cmd;

	cmd = allocate_command_struct();
	allocate_command_arrays(cmd);
	initialize_command_defaults(cmd, table);
	return (cmd);
}
