/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_ressources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 09:38:48 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_increment(t_state *state, t_indices *indices)
{
		state->n[0]++;
		indices->i++;
		indices->j++;
		state->i++;
		state->env_var = ft_strdup("");
}

int	handle_special_cases(const char *input, t_state *state, t_indices *indices)
{
	if ((input[indices->j] == '$' && input[indices->i] == '\"')
		|| (input[indices->j] == '$' && input[indices->i] == '\''))
	{
		ft_increment(state, indices);
		return (1);
	}
	if (input[indices->j] == '$' && (input[indices->i] >= '0'
			&& input[indices->i] <= '9'))
	{
		state->n[0] += 2;
		indices->i += 2;
		indices->j += 2;
		state->i += 2;
		state->env_var = ft_strdup("");
		return (1);
	}
	if (input[indices->i] == '?')
	{
		state->env_var = get_exit_code(1, state);
		state->i++;
		state->n[0] += 2;
		return (1);
	}
	return (0);
}

int	handle_empty_or_double_dollar(const char *input, t_state *state)
{
	if ((input[0] == '$' && !input[1]) || (input[0] == '$' && input[1] == '$'))
	{
		state->env_var = ft_strdup("$\0");
		state->i++;
		state->n[0]++;
		return (1);
	}
	return (0);
}

void	handle_variable_name(const char *input, char *var_name,
			t_indices *indices,
		t_state *state)
{
	int		verif;

	verif = 0;
	while (input[indices->i] && (ft_isalnum(input[indices->i])
			|| input[indices->i] == '_'))
	{
		var_name[indices->j] = input[indices->i];
		indices->i++;
		indices->j++;
		verif = 1;
	}
	state->i += indices->j;
	if (verif)
		state->n[0] += indices->i;
	var_name[indices->j] = '\0';
}

char	*make_expand(const char *input, t_state *state)
{
	t_indices	indices;
	char		var_name[1024];

	indices.i = 1;
	indices.j = 0;
	state->env_var = NULL;
	if (handle_special_cases(input, state, &indices))
		return (state->env_var);
	if (handle_empty_or_double_dollar(input, state))
		return (state->env_var);
	handle_variable_name(input, var_name, &indices, state);
	if (expand_env_variable(var_name, state, indices.i))
		return (state->env_var);
	handle_remaining_chars(input, &indices, state);
	state->n[0]++;
	return (state->env_var);
}
