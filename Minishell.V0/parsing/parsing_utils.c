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

// initialize struct
// t_command *create_command(void)
// {
//     t_command *cmd;

//     cmd = malloc(sizeof(t_command));
//     if (!cmd)
//         return (NULL);
//     cmd->args = malloc(sizeof(char *) * 1024);
//     if (!cmd->args)
//         return (NULL);
//     cmd->redir_type = 0;
//     cmd->pipe_in = 0;
//     cmd->pipe_out = 0;
//     cmd->pids = malloc(sizeof(int) * 1024);
//     if (!cmd->pids)
//         return (NULL);
//     cmd->p = malloc(sizeof(int) * 2);
//     if (!cmd->p)
//         return (NULL);
//     cmd->pprev = -1;
//     cmd->pipe_count = 0;
//     cmd->redir = NULL;
//     cmd->next = NULL;
//     return (cmd);
// }

// checks if pipe before and/or after this block
// void set_pipe_flags(t_command *current, t_command *new_cmd, char **tokens, int *i)
// {
//     if (current)
//         new_cmd->pipe_in = 1;
//     if (tokens[*i] && ft_strcmp(tokens[*i], "|") == 0)
//     {
//         new_cmd->pipe_out = 1;
//         (*i)++;
//     }
// }


//handles < > >>
int find_fd_in(t_command *cmd)
{
    int i;
    int fd;

    i = 1;
    while (cmd->args[i])
    {
        if (ft_strcmp(cmd->args[i], "<") == 0)
        {
            if (cmd->fd_in != -1)
                close(cmd->fd_in);
            fd = open_fct_check(cmd->args[i + 1], 0);
            if (fd == -1)
            {
                perror("Error opening input file");
                return (1);
            }
            cmd->fd_in = fd;
            i++;
        }
        i++;
    }
    return (0);
}

int find_fd_out(t_command *cmd)
{
    int i;
    int fd;

    i = 1;
    while(cmd->args[i])
    {
        if (ft_strcmp(cmd->args[i], ">") == 0)
        {
            if (cmd->fd_out != -1)
                close(cmd->fd_out);
            fd = open_fct_check(cmd->args[i + 1], 1);
            if (fd == -1)
            {
                perror("Error opening output file");
                return (1);
            }
            cmd->fd_out = fd;
            i++;
        }
        else if (ft_strcmp(cmd->args[i], ">>") == 0)
        {
            if (cmd->fd_out != -1)
                close(cmd->fd_out);
            fd = open_fct_check(cmd->args[i + 1], 2);
        
            if (fd == -1)
            {
                perror("Error opening output file");
                return (1);
            }
            cmd->fd_out = fd;
            i++;
        }
        i++;
    }
    return (0);
}

void    change_args_for_exec(t_command *cmd)
{
    t_command   *head;
    char        **new_args;
    int         args;
    int         i;
    int         j;

    head = cmd;
    while(cmd)
    {
        i = 0;
        while (cmd->args[i][0] != '|' && cmd->args[i][0] != '<' && cmd->args[i][0] != '>')
            i++;
        new_args = malloc(sizeof(char *) * (i + 1));
        if (!new_args)
            return (perror("Error with malloc"));
        j = 0;
        while (j++ < i)
        {
            new_args[j] = cmd->args[j];
        }
        new_args[j] = NULL;
        freetab(cmd->args);
        cmd->args = new_args;
        cmd = cmd->next;
    }
}

void free_t_command(t_command *cmd)
{
    t_command *temp;

    while (cmd)
    {
        temp = cmd->next;
        freetab(cmd->args);
        free(cmd);
        cmd = temp;
    }
}

t_command   *fill_t_command(char *input)
{
    t_command   *cmd;
    t_command   *head;

    cmd = tokenize_input(input);
    if (!cmd)
        return (NULL);
    head = cmd;
    if (find_fd_in(cmd))
    {
        free_t_command(cmd);
        return (NULL);
    }
    if (find_fd_out(cmd))
    {
        free_t_command(cmd);
        return (NULL);
    }
    change_args_for_exec(cmd);
    return (head);
}
// int handle_redirection(t_command *cmd, char **tokens, int *i)
// {
//     int fd;

//     if (strcmp(tokens[*i], "<") == 0)
//     {
//         if (fd = open_fct_check(tokens[++(*i)], 0))
//             cmd->filein = fd;
//         return (1);
//     }
//     else if (strcmp(tokens[*i], ">") == 0)
//     {
//         if (fd = open_fct_check(tokens[++(*i)], 1))
//             cmd->fileout = fd;
//         cmd->redir_type = 1;
//         return (1);
//     }
//     else if (strcmp(tokens[*i], ">>") == 0)
//     {
//         if (fd = open_fct_check(tokens[++(*i)], 2))
//             cmd->fileout = fd;
//         cmd->redir_type = 2;
//         return (1);
//     }
//     else if (strcmp(tokens[*i], "<<") == 0)
//     {
//         if (fd = open_fct_check(tokens[++(*i)], 0))
//             cmd->fileout = fd;
//         return (1);
//     }
//     return (0);
// }


// initializes commmand and args in struct
// void handle_command_and_args(t_command *cmd, char **tokens, int *i, int *arg_idx)
// {
//     cmd->args[(*arg_idx)++] = ft_strdup(tokens[*i]);
// }

//creates a block (between pipes)
// void process_command_block(t_command *cmd, char **tokens, int *i)
// {
//     int arg_idx = 0;

//     while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0)
//     {
//         if (handle_redirection(cmd, tokens, i) == 1)
//         {
//             (*i)++;
//             continue;
//         }
//         handle_command_and_args(cmd, tokens, i, &arg_idx);
//         (*i)++;
//     }
//     cmd->args[arg_idx] = NULL;
// }



// creates a linked list of struct where each struct is for
// one block of code between pipes
// t_command *parse_pipeline_commands(char **tokens)
// {
//     t_command *head = NULL;
//     t_command *current = NULL;
//     t_command *new_cmd = NULL;
//     int i = 0;

//     while (tokens[i])
//     {
//         new_cmd = create_command();
//         if (!new_cmd)
//             ft_error("malloc");
//         process_command_block(new_cmd, tokens, &i);
//         set_pipe_flags(current, new_cmd, tokens, &i);
        
//         if (!head)
//             head = new_cmd;
//         else
//             current->next = new_cmd;
//         current = new_cmd;
//     }
//     return (head);
// }

// t_command *parse_and_tokenize(char *line) 
// {
//     char **tokens;
//     t_command *command_list;

//     if (!line || !*line)
//         return (NULL);
//     tokens = tokenize_input(line);
//     if (!tokens)
//         return (NULL);
//     command_list = parse_pipeline_commands(tokens);
//     freetab(tokens);
//     return command_list;
// }

