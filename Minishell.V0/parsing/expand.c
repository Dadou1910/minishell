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


char *check_quotes(const char *input)
{
    int single_quote_open = 0;
    int double_quote_open = 0;
    int i;

    i = 0;
    while (input[i++])
    {
        if (input[i] == '\'' && !double_quote_open)
            single_quote_open = !single_quote_open;
        else if (input[i] == '"' && !single_quote_open)
            double_quote_open = !double_quote_open;
    }
    if (!single_quote_open && double_quote_open)
        return ("\'");
    else if (single_quote_open && double_quote_open)
        return ("'\"");
    else if (single_quote_open && !double_quote_open)
        return ("\"");
    else if (!single_quote_open && !double_quote_open)
        return ("0");
}

char *expand_env_var_1(const char *input, t_state *state)
{
    char *env = NULL;

    if (!strncmp(&input[state->i + 1], "PATH", 4))
    {
        env = getenv("PATH");
        state->i += 4;
    }
    else if (!strncmp(&input[state->i + 1], "HOME", 4))
    {
        env = getenv("HOME");
        state->i += 4;
    }
    else if (!strncmp(&input[state->i + 1], "PWD", 3))
    {
        env = getenv("PWD");
        state->i += 3;
    }
    else if (!strncmp(&input[state->i + 1], "OLDPWD", 6))
    {
        env = getenv("OLDPWD");
        state->i += 6;
    }
    return (env);
}

char *expand_env_var_2(const char *input, t_state *state)
{
    char *env = NULL;

    if (!strncmp(&input[state->i + 1], "SHLVL", 5))
    {
        env = getenv("SHLVL");
        state->i += 5;
    }
    else if (!strncmp(&input[state->i + 1], "_", 1))
    {
        env = getenv("_");
        state->i += 1;
    }
    else if (!strncmp(&input[state->i + 1], "USER", 4))
    {
        env = getenv("USER");
        state->i += 4;
    }
    else if (!strncmp(&input[state->i + 1], "TERM", 4))
    {
        env = getenv("TERM");
        state->i += 4;
    }
    return (env);
}

void process_char(const char *input, char *result, t_state *state)
{
    char *env;
    
    env = NULL;
    if (input[state->i] == 0)
        return;

    if (input[state->i] == '\'' && !state->dq_open)
        state->sq_open = !state->sq_open;

    else if (input[state->i] == '"' && !state->sq_open)
        state->dq_open = !state->dq_open;

    else if (input[state->i] == '$' && !state->sq_open)
    {
        env = expand_env_var_1(input, state);
        if (!env)
            env = expand_env_var_2(input, state);
        if (env)
            strcat(result, env);
    }
    else
        strncat(result, &input[state->i], 1);

    state->i++;
    process_char(input, result, state);
}


char    *retrieve_char_env(char *env_var)
{
    if (ft_strcmp(env_var, "PATH") == 0)
        return (getenv("PATH"));
    if (ft_strcmp(env_var, "HOME") == 0)
        return (getenv("HOME"));
    if (ft_strcmp(env_var, "PWD") == 0)
        return (getenv("PWD"));
    if (ft_strcmp(env_var, "OLDPWD") == 0)
        return (getenv("OLDPWD"));
    if (ft_strcmp(env_var, "SHLVL") == 0)
        return (getenv("SHLVL"));
    if (ft_strcmp(env_var, "_") == 0)
        return (getenv("_"));
    if (ft_strcmp(env_var, "USER") == 0)
        return (getenv("USER"));
    if (ft_strcmp(env_var, "TERM") == 0)
        return (getenv("TERM"));

}

int retrieve_exit_status(char *env_var, t_command *cmd, int exit_status)
{
    if (ft_strcmp(env_var, "?") == 0)
        return (exit_status);
}