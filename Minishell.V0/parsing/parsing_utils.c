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

#include <stdlib.h>

//initialize struct
t_command *create_command(void)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = malloc(sizeof(char *) * 1024);
    if (!cmd->args)
        return (NULL);
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->redir_type = 0;
    cmd->pipe_in = 0;
    cmd->pipe_out = 0;
    cmd->pids = malloc(sizeof(int) * 1024);
    if (!cmd->pids)
        return (NULL);
    cmd->p = malloc(sizeof(int) * 2);
    if (!cmd->p)
        return (NULL);
    cmd->pprev = -1;
    cmd->next = NULL;
    return (cmd);
}

//handles < > >>
int handle_redirection(t_command *cmd, char **tokens, int *i)
{
    if (ft_strcmp(tokens[*i], ">") == 0)
    {
        cmd->redir_type = 1;
        cmd->outfile = ft_strdup(tokens[++(*i)]);
        return (1);
    }
    else if (ft_strcmp(tokens[*i], ">>") == 0)
    {
        cmd->redir_type = 2;
        cmd->outfile = ft_strdup(tokens[++(*i)]);
        return (1);
    }
    else if (ft_strcmp(tokens[*i], "<") == 0)
    {
        cmd->infile = ft_strdup(tokens[++(*i)]);
        return (1);
    }
    return (0);
}

//initializes commmand and args in struct
void handle_command_and_args(t_command *cmd, char **tokens, int *i, int *arg_idx)
{
    cmd->args[(*arg_idx)++] = ft_strdup(tokens[*i]);
}

//checks if pipe before and/or after this block
void set_pipe_flags(t_command *current, t_command *new_cmd, char **tokens, int *i)
{
    if (current)
        new_cmd->pipe_in = 1;
    if (tokens[*i] && ft_strcmp(tokens[*i], "|") == 0)
    {
        new_cmd->pipe_out = 1;
        (*i)++;
    }
}

//creates a block (between pipes)
void process_command_block(t_command *cmd, char **tokens, int *i)
{
    int arg_idx = 0;

    while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0)
    {
        if (handle_redirection(cmd, tokens, i))
            continue;
        handle_command_and_args(cmd, tokens, i, &arg_idx);
        (*i)++;
    }
    cmd->args[arg_idx] = NULL;
}

//creates a linked list of struct where each struct is for
//one block of code between pipes
t_command *parse_pipeline_commands(char **tokens)
{
    t_command *head = NULL;
    t_command *current = NULL;
    t_command *new_cmd = NULL;
    int i = 0;

    while (tokens[i])
    {
        new_cmd = create_command();
        if (!new_cmd)
            ft_error("malloc");
        process_command_block(new_cmd, tokens, &i);
        set_pipe_flags(current, new_cmd, tokens, &i);
        if (!head)
            head = new_cmd;
        else
            current->next = new_cmd;
        current = new_cmd;
    }
    return (head);
}

