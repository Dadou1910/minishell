/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 09:56:14 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	malloc_help(void)
{
	perror("malloc failed");
	exit(0);
}

void	malloc_error(char **input)
{
	if (!input)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
}

void	init_str_helper(int *i, int *j, t_state *state)
{
	*i = 0;
	*j = state->n[0];
	state->i = 0;
}

char	*helper_quotes(char *arg, char c, t_state *state)
{
	char	*str;
	int		i;
	int		j;

	init_str_helper(&i, &j, state);
	if (arg[j] != '$')
		j++;
	str = malloc(1024);
	if ((!str))
		malloc_help();
	while ((arg[j] != c && arg[j]))
	{
		str[i++] = arg[j++];
		if ((!state->dq_open && !state->sq_open && arg[j] == '\'')
			|| (!state->sq_open && !state->dq_open && arg[j] == '\"'))
			break ;
	}
	str[i] = '\0';
	state->n[0]++;
	return (str);
}

char	*copy_quotes_to_arg(t_command *cmd, int *i, t_state *state)
{
	int	j;

	j = 0;
	if (!state->n[1])
	{
		cmd->args[*i] = ft_strdup("");
		return (cmd->args[*i]);
	}
	cmd->args[*i] = malloc(sizeof(char) * 4096);
	if (!cmd->args[*i])
	{
		perror("Error allocating memory for cmd->args[*i]");
		exit(1);
	}
	cmd->args[*i][0] = '\0';
	j = 0;
	while (cmd->token_quotes && cmd->token_quotes[j])
	{
		ft_strlcat(cmd->args[*i], cmd->token_quotes[j], 4096);
		ft_bzero(cmd->token_quotes[j], ft_strlen(cmd->token_quotes[j]));
		j++;
	}
	return (cmd->args[*i]);
}
