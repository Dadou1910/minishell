/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:30:22 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 18:32:03 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	helper_is_builtins(t_command *cmd, int *i)
{
	while (cmd->args[*i])
	{
		cmd->table->envp = ft_export(cmd, *i);
		(*i)++;
	}
}

void	deals_unset(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strrchr(cmd->args[i], '=') == 0)
			cmd->table->envp = unset(cmd->table->envp, cmd->args[i]);
		i++;
	}
}
