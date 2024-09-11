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

static int count_tokens(char *input)
{
    int count = 0;
    int i = 0;

    while (input[i])
    {
        if (input[i] == ' ')
        {
            i++;
            continue;
        }
        if (input[i] == '|' || input[i] == '>' || input[i] == '<')
        {
            count++;
            if (input[i] == '>' && input[i + 1] == '>')
                i++;
            i++;
            continue;
        }
        count++;
        while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '>' && input[i] != '<')
            i++;
    }
    return count;
}

static char *extract_token(char *input, int *i)
{
    int start = *i;
    int length = 0;

    if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
    {
        length = 1;
        if (input[*i] == '>' && input[*i + 1] == '>')
            length = 2;
        *i += length;
        return (ft_substr(input, start, length));
    }
    while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
    {
        (*i)++;
        length++;
    }
    return (ft_substr(input, start, length));
}

char **tokenize_input(char *input)
{
    char **tokens;
    int token_count;
    int i = 0;
    int token_index = 0;

    if (!input)
        return (NULL);
    token_count = count_tokens(input);
    tokens = malloc(sizeof(char *) * (token_count + 1));
    if (!tokens)
        return (NULL);
    while (input[i])
    {
        if (input[i] == ' ')
        {
            i++;
            continue;
        }
        tokens[token_index++] = extract_token(input, &i);
    }
    tokens[token_index] = NULL;
    return tokens;
}

