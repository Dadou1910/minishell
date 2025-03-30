/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_fds2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 11:16:05 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_redir(t_redir *rd, char **tokens, int *fds, char *str)
{
	rd->tokens = tokens;
	rd->fds = fds;
	rd->str = str;
	rd->idx = 0;
	rd->pipe_idx = 0;
	rd->fd = -2;
}

int	handle_redirection(t_redir *rd, char **envp)
{
	if (ft_strcmp(rd->tokens[rd->idx], "|") == 0)
		rd->pipe_idx++;
	if (ft_strcmp(rd->tokens[rd->idx], "<<") == 0)
	{
		if (rd->fds[rd->pipe_idx] != -2)
			close(rd->fds[rd->pipe_idx]);
		rd->fds[rd->pipe_idx] = here_doc(rd, envp);
	}
	else if (ft_strcmp(rd->tokens[rd->idx], "<") == 0)
	{
		if (rd->fds[rd->pipe_idx] != -2)
			close(rd->fds[rd->pipe_idx]);
		rd->fds[rd->pipe_idx]
			= handle_file_redirection(rd->tokens[rd->idx + 1]);
		if (rd->fds[rd->pipe_idx] == -3)
			return (-3);
		rd->idx++;
	}
	return (rd->idx);
}

int	*process_tokens_fd(char **tokens, int *fds, char *str, char **envp)
{
	t_redir	rd;
	int		result;

	init_redir(&rd, tokens, fds, str);
	while (rd.tokens[rd.idx])
	{
		result = handle_redirection(&rd, envp);
		if (result == -3)
			return (free(str), free(fds), NULL);
		rd.idx = result + 1;
	}
	return (fds);
}
