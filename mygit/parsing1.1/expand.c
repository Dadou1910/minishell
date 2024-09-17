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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
/*
int is_valid_env_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

int is_env_variable(t_token *token)
{
    int i;

    i = 1;
    if (token && token->value[0] == '$' && token->value[1] != '\0') {
        while (token->value[i]) {
            if (!is_valid_env_char(token->value[i])) {
                return (0);
            }
            i++;
        }
        return (1);
    }
    return (0);
}

char *expand_env_variable(t_token *token)
{
    const char *var_name;
    const char *var_value;

    if (is_env_variable(token))
    {
        var_name = token->value + 1;
        var_value = getenv(var_name);
        if (var_value)
            return (ft_strdup(var_value));
        else
            return (ft_strdup(""));
    }
    return (ft_strdup(token->value));
}
*/