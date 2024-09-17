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

// static char *extract_token(char *input, int *i)
// {
//     int start = *i;
//     int length = 0;

//     if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
//     {
//         length = 1;
//         if (input[*i] == '>' && input[*i + 1] == '>')
//             length = 2;
//         *i += length;
//         return (ft_substr(input, start, length));
//     }
//     while (input[*i] && input[*i] != ' ')
//     {
//         (*i)++;
//         length++;
//     }
//     return (ft_substr(input, start, length));
// }

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

void process_tokens(char **tokens, t_command *cmd, int *j)
{
    int i = 0;

    cmd->args = malloc(sizeof(char *) * 1024);
    if (!cmd->args)
    {
        perror("Error allocating memory for args");
        exit(1);
    }

    while (tokens[*j] && ft_strcmp(tokens[*j], "|"))
    {
        cmd->args[i] = ft_strdup(tokens[*j]);
        if (!cmd->args[i])
        {
            perror("Error duplicating token");
            exit(1);
        }
        i++;
        (*j)++;
    }
    cmd->args[i] = NULL;
}

t_command *tokenize_input(char *input)
{
    char        **tokens;
    t_command   *cmd;
    t_command   *head;
    int j = 0;

    if (!input)
        return NULL;
    cmd = malloc(sizeof(t_command));
    if (!cmd)
    {
        perror("Error allocating memory");
        return NULL;
    }
    initialize_t_command(cmd);
    head = cmd;
    tokens = ft_split(input, ' ');
    while (tokens[j])
    {
        process_tokens(tokens, cmd, &j);
        if (tokens[j] && ft_strcmp(tokens[j], "|") == 0)
        {
            new_t_command(cmd);
            cmd = cmd->next;
            j++;
        }
    }
    j = 0;
    freetab(tokens);
    return (head);
}