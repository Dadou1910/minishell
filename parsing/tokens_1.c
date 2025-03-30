/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 09:55:31 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_token_arguments(char **tokens, t_command *cmd, int *j)
{
	int	i;

	i = 0;
	while (tokens[*j] && ft_strcmp(tokens[*j], "|"))
	{
		cmd->sargs[i] = ft_strdup(tokens[*j]);
		if (!cmd->sargs[i])
		{
			perror("Error duplicating token");
			exit(1);
		}
		i++;
		(*j)++;
	}
	cmd->sargs[i] = NULL;
}

int	expand_tokens(char **tokens, t_command *cmd, t_state *state, int j)
{
	int		i;

	i = 0;
	state->cmd = cmd;
	while (tokens[j] && ft_strcmp(tokens[j], "|"))
	{
		state->i = 0;
		if (ft_strchr(tokens[j], '$') || ft_strchr(tokens[j], '\"')
			|| ft_strchr(tokens[j], '\''))
		{
			if (ft_strchr(tokens[j], '\"') || ft_strchr(tokens[j], '\''))
				handle_quotes_and_expand(tokens[j], state);
			else
				process_char_helper(tokens[j], state);
			copy_quotes_to_arg(cmd, &i, state);
		}
		else
			cmd->args[i] = ft_strdup(cmd->sargs[i]);
		i++;
		j++;
	}
	cmd->args[i] = NULL;
	return (0);
}

int	process_tokens(char **tokens, t_command *cmd, int *j, int fd_in)
{
	t_state	*state;
	int		ret;
	int		i;

	i = *j;
	ret = 0;
	state = initialize_t_state();
	process_token_arguments(tokens, cmd, j);
	cmd->fd_in = fd_in;
	find_fd_out(cmd);
	expand_tokens(tokens, cmd, state, i);
	free(state);
	return (ret);
}

int	split_and_process_tokens(t_command *cmd, char **tokens, t_table *table,
			int *fd_ins)
{
	int			j;
	int			k;
	int			ret;
	t_command	*tmp;

	k = 0;
	j = 0;
	ret = 0;
	tmp = cmd;
	while (tokens[j])
	{
		ret = process_tokens(tokens, tmp, &j, fd_ins[k++]);
		if (ret == -1)
			return (-1);
		if (tokens[j] && ft_strcmp(tokens[j], "|") == 0)
		{
			new_t_command(tmp, table);
			tmp = tmp->next;
			j++;
		}
	}
	return (ret);
}

t_command	*tokenize_input(char *input, char **envp, int return_value)
{
	char		**tokens;
	int			*tab_fds_in;
	t_table		*table;
	t_command	*cmd;
	t_command	*head;

	if (!input)
		return (NULL);
	tab_fds_in = get_in_fds(input, envp);
	if (!tab_fds_in)
		return (NULL);
	table = initialize_t_main(input, envp, &return_value);
	cmd = initialize_t_command(table);
	if (!cmd)
	{
		perror("Error allocating memory");
		return (NULL);
	}
	head = cmd;
	tokens = ft_split(input, ' ');
	if (split_and_process_tokens(cmd, tokens, table, tab_fds_in) == -1)
		return (NULL);
	free(tab_fds_in);
	freetab(tokens);
	return (head);
}
