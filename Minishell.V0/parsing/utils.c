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

void    initialize_t_command(t_command *cmd)
{
    cmd->args = NULL;
    cmd->fd_in = -1;
    cmd->fd_out = -1;
    cmd->pids = NULL;
    cmd->p = NULL;
    cmd->pprev = -1;
    cmd->pipe_count = 0;
    cmd->next = NULL;
}

int	open_fct_check(char *file, int i)
{
	int	filein;

	filein = 0;
	if (i == 0)
		filein = open(file, O_RDONLY);
	else if (i == 1)
		filein = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		filein = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (filein);
}

void    free_t_command(t_command *cmd)
{
    t_command *temp;

    while (cmd)
    {
        temp = cmd->next;
        freetab(cmd->args);
        free(cmd);
        cmd = temp;
    }
}

void    new_t_command(t_command *cmd)
{
    t_command   *new_cmd;
    new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
    {
        perror("Error allocating memory for new command");
        return(1);
    }
    initialize_t_command(new_cmd);
    cmd->next = new_cmd;
}