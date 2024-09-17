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
/*
#include "../includes/minishell.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



// Function to classify a token
t_TYPE classify_token(char *token, int *is_first_command)
{
    if (strcmp(token, ">") == 0)
        return RIN;
    else if (strcmp(token, ">>") == 0)
        return DRIN;
    else if (strcmp(token, "<") == 0)
        return ROUT;
    else if (strcmp(token, "<<") == 0)
        return DROUT;
    else if (strcmp(token, "|") == 0)
    {
        *is_first_command = 1;  // Reset for the next command
        return PIPE;
    }
    else if (*is_first_command)  // If it's the first non-redirection token, it's a command
    {
        *is_first_command = 0;
        return ARG;
    }
    else
        return FD;
}

int	open_fct_check(char *file, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(file, O_RDONLY);
	else if (i == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (i == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

// Function to create a token
t_token *create_token(char *value, t_TYPE type) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->value = ft_strdup(value);
    new_token->type = type;
    new_token->next = NULL;
    new_token->prev = NULL;
    return new_token;
}

// Function to append a token to the list
void append_token(t_token **head, t_token *new_token) {
    t_token *current = *head;

    if (*head == NULL)
    {
        *head = new_token;
        return;
    }
    // Traverse to the end of the list
    while (current->next != NULL)
        current = current->next;
    // Link the new token to the previous token
    current->next = new_token;
    new_token->prev = current;
}

// Function to open files for redirection
int open_file_for_redirection(char *filename, t_TYPE type) {
    int fd = -1;

    if (type == RIN)      // '>'
        fd = open_fct_check(filename, 1);
    else if (type == DRIN) // '>>'
        fd = open_fct_check(filename, 2);
    else if (type == ROUT) // '<'
        fd = open_fct_check(filename, 0);
    //else if (type == DROUT)
    //    fd = handle_heredoc();
    // IMPLEMENT SPECIAL CONDITION FOR HEREDOC '<<' <---------------------------------------------------
    if (fd == -1)
        perror("Error opening file");
    return fd;
}

//---------------------------> int handle_heredoc()

// Function to handle input redirection
int handle_input_redirection(t_command *cmd, t_token *current)
{
    if (current->prev && current->prev->type == ROUT)
    {
        if (current->type == FD)
        {
            if (cmd->fd_in != STDIN_FILENO)
                close(cmd->fd_in);
            cmd->fd_in = open_file_for_redirection(current->value, ROUT);
            if (cmd->fd_in == -1)
            {
                perror("Error opening input file");
                return 1; 
            }
        }
    }
    return 0;
}

// Function to handle output redirection
int handle_output_redirection(t_command *cmd, t_token *current)
{
    if (current->prev && (current->prev->type == RIN || current->prev->type == DRIN))
    {
        if (current->type == FD)
        {
            if (cmd->fd_out != STDOUT_FILENO)
                close(cmd->fd_out);
            cmd->fd_out = open_file_for_redirection(current->value, current->prev->type);
            if (cmd->fd_out == -1)
            {
                perror("Error opening output file");
                return (1);
            }
        }
    }
    return 0;
}


// Function to process redirections
int process_redirections(t_command *cmd, t_token *tokens)
{
    t_token *current;
    
    current = tokens;
    while (current)
    {
        if (handle_input_redirection(cmd, current))
            return 1;
        if (handle_output_redirection(cmd, current))
            return 1;
        current = current->next;
    }
    if (cmd->fd_in != STDIN_FILENO)
        close(cmd->fd_in);
    return 0;
}

// Function to tokenize the input using ft_split and build a linked list of tokens
t_token *parse_input(char *input)
{
    t_token *head;
    char **tokens;
    int i;
    t_TYPE type;
    int is_first_command;// Used to track whether we are processing the first command

    head = NULL;
    type = NULL;
    tokens = ft_split(input, ' ');
    i = 0;
    is_first_command = 1;
    while (tokens[i])
    {
        type = classify_token(tokens[i], &is_first_command);
        append_token(&head, create_token(tokens[i], type));
        // After the first command is classified, set flag to 0 for subsequent tokens
        if (type == ARG)
            is_first_command = 0;
        if (type == PIPE)
            is_first_command = 1;
        i++;
    }
    freetab(tokens);
    return head;
}*/