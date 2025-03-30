/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:27:01 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 10:57:20 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freetab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	if (tab[i])
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
	}
	if (tab)
		free(tab);
	tab = NULL;
}

void	free_cmd(t_command *cmd)
{
	t_command	*head;

	head = cmd;
	while (cmd)
	{
		head = cmd;
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		if (cmd->fd_out >= 0 && cmd->next == NULL)
			close(cmd->fd_out);
		if (cmd->pprev >= 0)
			close(cmd->pprev);
		if (cmd->args)
			freetab(cmd->args);
		if (cmd->sargs)
			freetab(cmd->sargs);
		if (cmd->token_quotes)
			freetab(cmd->token_quotes);
		if (cmd->result)
			free(cmd->result);
		cmd = cmd->next;
		free(head);
	}
}

void	free_table(t_table *table)
{
	if (table->envp != NULL)
		freetab(table->envp);
	free(table->pids);
	free(table);
}
